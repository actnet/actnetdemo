#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "storage/mgraph.hpp"
#include "serialization/serialization.hpp"
#include "toolkit/activity/activity.hpp"
#include "toolkit/RStarTree/RStarTree.hpp"
#include "indexing/search.hpp"
#include "indexing/analyzer.hpp"
#include "aminerdata.hpp"

#define DIM 100

typedef RTree<int, double, DIM> IndexTree;
typedef vector<int> RSearchResult;

struct ActivityCity{
    string name;
    int count;
};

struct ActivityData {
    ActivityData(char const * prefix);
    ~ActivityData();

    template<typename T>
    T get(sae::io::vid_t id) const {
        auto vi = g->Vertices();
        vi->MoveTo(id);
        return parse<T>(vi->Data());
    }

    RSearchResult search_activities(const std::string& query, int limit = 15);
    // RSearchResult search(const std::string& type, const string& query, int limit = 15) const {
    //     if (type == "Activity") {
    //         return search_activities(query, limit);
    //     }
    //     return indexing::SearchResult();
    // }

    bool Isinteresting(std::map<string, int>& vertical, string& type);
    vector<ActivityCity> search_city(double lLat, double lLng, double rLat, double rLng);
    map<string, vector<ActivityCity>> search_city_activity();
    double dist(string &query1, string &query2);

    int get_total_count(){
        return g->VertexCountOfType("Activity");
    }

    std::vector<indexing::Index> activity_index_shards;
    std::unique_ptr<sae::io::MappedGraph> g;
    std::map<string, std::map<string, int>> bgsum;
    std::map<string, int> activity_index;
    IndexTree feature_index;
    word2vec model;
};

