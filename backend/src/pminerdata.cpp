#include <atomic>
#include "glog/logging.h"
#include "pminerdata.hpp"
#include "thread_util.hpp"
#include "indexing/analyzer.hpp"

using namespace std;
using namespace sae::io;
using namespace indexing;

PMinerData::PMinerData(char const * prefix) {
    LOG(INFO) << "loading pminer graph...";
    g.reset(MappedGraph::Open(prefix));
    int patent_type = g->VertexTypeIdOf("Patent");
    LOG(INFO) << "calculating average length...";
    auto calc_avg_len = [&]() {
        double avgLen = 0;
        int count = 0;
        for (auto ai = g->Vertices(); ai->Alive(); ai->Next()) {
            if (ai->TypeId() == patent_type) {
                count++;
                auto p = parse<Patent>(ai->Data());
                for (unsigned i = 0; i < p.title.length(); i++)
                    if (p.title[i] == ' ' && i != p.title.length() - 1)
                        avgLen++;
                avgLen++;
            }
        }
        LOG(INFO) << "count: " << count << ", avgLen: " << avgLen;
        return avgLen / count;
    };
    double avgLen = 7.55;
    
    LOG(INFO) << "building index...";
    const int shards = thread::hardware_concurrency();
    patent_index_shards.resize(shards);
    
    auto offset = g->VerticesOfType("Patent")->GlobalId();
    auto total = g->VertexCountOfType("Patent");
    auto shard_size = total / shards;
    atomic<int> processed(0);
    auto index_builder = [&](int shard_id) {
        auto ai = g->Vertices();
        auto start = offset + shard_id * shard_size;
        auto end = offset + (shard_id + 1) * shard_size;
        LOG(INFO) << "shard " << shard_id << " processing range: " << start << " to " << end;
        for (auto i = start; i < end && ai->Alive(); ai->MoveTo(i)) {
            if (ai->TypeId() == patent_type){
                auto p = parse<Patent>(ai->Data());
                string text = p.title;
                TokenStream* stream(ArnetAnalyzer::tokenStream(text));
                patent_index_shards[shard_id].addSingle(ai->GlobalId(), 0, stream, avgLen);
            }
            // counter
            i++;
            if ((i - start) % 10000 == 0) {
                processed += 10000;
                LOG(INFO) << "[" << shard_id << "] progress: " << processed.load() << "/" << total << "\t" << (double)(processed.load()) / total;
            }
        }
        LOG(INFO) << "[" << shard_id << "] finished!";
    };
    dispatch_thread_group(index_builder, shards);
    LOG(INFO) << "index built!";
}

PMinerData::~PMinerData() {
    LOG(INFO) << "releasing pminer data...";
}

SearchResult PMinerData::search_patents(const string& query, int limit) const {
    vector<SearchResult> results(patent_index_shards.size());
    auto index_searcher = [&](int shard_id) {
        Searcher basic_searcher(patent_index_shards[shard_id]);
        TokenStream* stream(ArnetAnalyzer::tokenStream(query));
        auto result = basic_searcher.search(stream);
        std::sort(result.begin(), result.end());
        results[shard_id] = move(result);
    };
    dispatch_thread_group(index_searcher, results.size());

    // merge the results.
    // TODO: improve this merge algorithm.
    for (int i = results.size() - 1; i > 0; i--) {
        int dst = i / 2;
        auto dsize = results[dst].size();
        results[dst].insert(results[dst].end(), results[i].begin(), results[i].end());
        std::inplace_merge(results[dst].begin(), results[dst].begin() + dsize, results[dst].end());
        results[i].clear();
        if (results[dst].size() > limit)
            results[dst].resize(limit);
    }

    return results[0];
}
