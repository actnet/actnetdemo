#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include "storage/mgraph.hpp"
#include "serialization/serialization.hpp"
#include "pminer.hpp"
#include "indexing/search.hpp"
#include "indexing/analyzer.hpp"
#include "aminerdata.hpp"

struct PMinerData {
    PMinerData(char const * prefix);

    ~PMinerData();

    template<typename T>
    T get(sae::io::vid_t id) const {
        auto vi = g->Vertices();
        vi->MoveTo(id);
        return parse<T>(vi->Data());
    }

    indexing::SearchResult search_patents(const string& query, int limit = 5000) const;
    indexing::SearchResult search(const string& type, const string& query, int limit = 5000) const {
        if (type == "Patent") {
            return search_patents(query, limit);
        }
        return indexing::SearchResult();
    }

    std::vector<indexing::Index> patent_index_shards;
    std::unique_ptr<sae::io::MappedGraph> g;
};

