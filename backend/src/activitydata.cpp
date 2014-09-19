#ifndef OS_LINUX
#include <Windows.h>
#pragma comment(lib, "ICTCLAS50.lib")
#endif

#include <atomic>
#include "activitydata.hpp"
#include "glog/logging.h"
#include "thread_util.hpp"
#include "ICTCLAS50.h"

using namespace std;
using namespace sae::io;
using namespace indexing;

void ExchangeCity(ActivityCity &m1, ActivityCity &m2){
    string midstr;
    double middou;
    midstr = m1.name;
    middou = m1.count;
    m1.name = m2.name;
    m1.count = m2.count;
    m2.name = midstr;
    m2.count = middou;
} 


// ActivityData::ActivityData(char const * prefix) {

//     LOG(INFO) << "loading dict...";
//     ICTCLAS_Init();

//     LOG(INFO) << "loading activity graph...";
//     g.reset(MappedGraph::Open(prefix));
//     int activity_type = g->VertexTypeIdOf("Activity");
//     LOG(INFO) << "calculating average length...";
//     auto calc_avg_len = [&]() {
//         double avgLen = 0;
//         int count = 0;
//         for (auto ai = g->Vertices(); ai->Alive(); ai->Next()) {
//             if (ai->TypeId() == activity_type) {
//                 count++;
//                 auto w = parse<Activity>(ai->Data());
//                 for (unsigned i = 0; i < w.name.length(); i++)
//                     if (w.name[i] == ' ' && i != w.name.length() - 1)
//                         avgLen++;
//                 avgLen++;
//             }
//         }
//         LOG(INFO) << "count: " << count << ", avgLen: " << avgLen;
//         return avgLen / count;
//     };
// 	double avgLen = calc_avg_len();

//     LOG(INFO) << "building index...";
//     const int shards = thread::hardware_concurrency();
//     activity_index_shards.resize(shards);

// 	auto offset = g->VerticesOfType("Activity")->GlobalId();
// 	auto total = g->VertexCountOfType("Activity");
// 	auto shard_size = total / shards;
//     ICTCLAS_SetPOSmap(2);
// 	atomic<int> processed(0);
// 	auto index_builder = [&](int shard_id) {
//         auto ai = g->Vertices();
//         auto start = offset + shard_id * shard_size;
//         auto end = offset + (shard_id + 1) * shard_size;
//         LOG(INFO) << "shard " << shard_id << " processing range: " << start << " to " << end;
//         for (auto i = start; i < end && ai->Alive(); ai->MoveTo(i)) {
//             if (ai->TypeId() == activity_type){
//                 auto w = parse<Activity>(ai->Data());
//                 string text = w.name;
//                 const char* sentence = text.c_str();
//                 unsigned int nPaLen=strlen(sentence); 
//                 char* sRst=0; 
//                 sRst=(char *)malloc(nPaLen*6); 
//                 int nRstLen=0;
//                 nRstLen = ICTCLAS_ParagraphProcess(sentence,nPaLen,sRst,CODE_TYPE_UNKNOWN,0);
//                 TokenStream* stream(ArnetAnalyzer::tokenStream(sRst));
//                 activity_index_shards[shard_id].addSingle(ai->GlobalId(), 0, stream, avgLen);
//             }
//             // counter
//             i++;
//             if ((i - start) % 10000 == 0) {
//                 processed += 10000;
//                 LOG(INFO) << "[" << shard_id << "] progress: " << processed.load() << "/" << total << "\t" << (double)(processed.load()) / total;
//             }
//         }
//         LOG(INFO) << "[" << shard_id << "] finished!";
// 	};
//     dispatch_thread_group(index_builder, shards);
//     LOG(INFO) << "activity index built!";
// }

ActivityData::ActivityData(char const * prefix){

    LOG(INFO) << "loading activity graph...";
    g.reset(MappedGraph::Open(prefix));
    int activity_type = g->VertexTypeIdOf("Activity");
    
    LOG(INFO) << "start to build index";
    for (auto ai = g->Vertices(); ai->Alive(); ai->Next()) {
        if (ai->TypeId() == activity_type) {
            auto w = parse<Activity>(ai->Data());
            double *feature = new double[w.feature.size()];
            for(int i = 0; i < w.feature.size(); i++)
                feature[i] = w.feature[i];
            feature_index.Insert(feature, feature, ai->GlobalId());
            activity_index[w.name] = ai->GlobalId();
        }
    }
    LOG(INFO) << "activity index built!";

    model = loadVector("myvector.txt");
    LOG(INFO) << "vector load done!";
}

ActivityData::~ActivityData() {
    //ICTCLAS_Exit();
}

double ActivityData::dist(string &query1, string &query2){
    int id1 = model.Vocab[query1];
    int id2 = model.Vocab[query2];
    vector<double> vec1 = model.getVector(id1);
    vector<double> vec2 = model.getVector(id2);
    return 1 - Dot(vec1, vec2);
}

// SearchResult ActivityData::search_activities(const string& query, int limit) const {
//     const char* sentence = query.c_str();
//     unsigned int nPaLen=strlen(sentence); 
//     char* sRst=0; 
//     sRst=(char *)malloc(nPaLen*6); 
//     int nRstLen=0;
//     nRstLen = ICTCLAS_ParagraphProcess(sentence,nPaLen,sRst,CODE_TYPE_UNKNOWN,0);
//     LOG(INFO) << sRst;
//     vector<SearchResult> results(activity_index_shards.size());
//     auto index_searcher = [&](int shard_id) {
//         Searcher basic_searcher(activity_index_shards[shard_id]);
//         TokenStream* stream(ArnetAnalyzer::tokenStream(sRst));
//         auto result = basic_searcher.search(stream);
//         std::sort(result.begin(), result.end());
//         results[shard_id] = move(result);
//     };
//     dispatch_thread_group(index_searcher, results.size());
    
//     // merge the results.
//     // TODO: improve this merge algorithm.
//     for (int i = results.size() - 1; i > 0; i--) {
//         int dst = i / 2;
//         auto dsize = results[dst].size();
//         results[dst].insert(results[dst].end(), results[i].begin(), results[i].end());
//         std::inplace_merge(results[dst].begin(), results[dst].begin() + dsize, results[dst].end());
//         results[i].clear();
//         if (results[dst].size() > limit)
//             results[dst].resize(limit);
//     }
//     return results[0];
// }

RSearchResult ActivityData::search_activities(const string& query, int limit) {
    RSearchResult res;
    int id = model.Vocab[query];
    if(id == 0)
        return res;
    vector<double> vec = model.getVector(id);
    double *feature = new double[vec.size()];
    for(int i = 0; i < vec.size(); i++)
        feature[i] = vec[i];
    int *res_list = feature_index.KNNSearch(feature, limit);
    for(int i = 0; i < limit; i++)
        res.push_back(res_list[i]);
    return res;
}

bool ActivityData::Isinteresting(std::map<string, int>& vertical, string& type){
    if(vertical.size() < 1)
        return false;
    map<string, int> bgdist = bgsum[type];
    vector<string> keys;
    vector<double> values, expect;
    double sum = 0, bgsum = 0;
    for(map<string, int>::iterator it = vertical.begin(); it != vertical.end(); it++)
    {
        keys.push_back(it->first);
        values.push_back(it->second);
        sum += it->second;
        bgsum += bgdist[it->first];
    }
    for(vector<string>::iterator it = keys.begin(); it != keys.end(); it++)
        expect.push_back(double(bgdist[*it]) * sum / bgsum);
    return false;
}

vector<ActivityCity> ActivityData::search_city(double lLat, double lLng, double rLat, double rLng){
    vector<ActivityCity> resultmap;
    resultmap.resize(5, {"", -1});
    for (auto ai = g->Vertices(); ai->Alive(); ai->Next()) {
        int activity_type = g->VertexTypeIdOf("Activity");
        if (ai->TypeId() == activity_type) {
            auto w = parse<Activity>(ai->Data());
            int count = 0;
            for(vector<Instance>::iterator it = w.instances.begin(); it != w.instances.end(); it++)
                if(it->lantitude > lLat && it->lantitude < rLat && it->longtitude > lLng && it->longtitude < rLng)
                    count++;
            ActivityCity mid = {w.name, count};
            for(int i = 0; i <resultmap.size(); i++){
                if(resultmap[i].count < mid.count)
                    ExchangeCity(resultmap[i], mid);
            }
        }
    }
}

map<string, vector<ActivityCity>> ActivityData::search_city_activity(){
    map<string, vector<ActivityCity>> result;
    vector<ActivityCity> beijing = search_city(39.6612714, 116.01193430000001, 40.2164962, 116.7829835);
    vector<ActivityCity> shanghai = search_city(30.7798012, 120.83970669999997, 31.6688967, 122.1137989);
    vector<ActivityCity> guangzhou = search_city(22.6961015, 112.7224731, 23.555094, 113.73321529999998);
    for(vector<ActivityCity>::iterator it = beijing.begin(); it != beijing.end(); it++)
        cout<<"bj:"<<it->name<<endl;
    for(vector<ActivityCity>::iterator it = shanghai.begin(); it != shanghai.end(); it++)
        cout<<"sh:"<<it->name<<endl;
    for(vector<ActivityCity>::iterator it = guangzhou.begin(); it != guangzhou.end(); it++)
        cout<<"gz:"<<it->name<<endl;
    return result;
}