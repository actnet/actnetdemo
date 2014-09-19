#include <chrono>
#include <algorithm>
#include <sstream>
#include <vector>

#include "indexing/search.hpp"
#include "search.hpp"
#include "expert_searcher.hpp"
#include "group_searcher.hpp"
#include "user_searcher.hpp"
#include <string>
#include "zrpc/zrpc.hpp"
#include "activitydata.hpp"

using namespace std;

DEFINE_string(activity, "actdata/activities", "graph prefix of activities");

int main()
{
	auto activity = unique_ptr<ActivityData>(new ActivityData(FLAGS_activity.c_str()));
		cout<<"OK"<<endl;
	string query;
    while(cin>>query){
		auto result = activity->search_activities(query);
		cout<<"size:"<<result.size()<<endl;
	}
}