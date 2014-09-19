#include <memory>

#include "gflags/gflags.h"
#include "glog/logging.h"
#include "zrpc/zrpc.hpp"
#include "search.hpp"
#include "aminerdata.hpp"
#include "activitydata.hpp"
#include "pminerdata.hpp"
#include "weibodata.hpp"

DEFINE_int32(port, 40110, "server port");
DEFINE_int32(threads, 20, "server threads");
DEFINE_string(aminer, "aminer", "graph prefix of aminer");
DEFINE_string(pminer, "pminer", "graph prefix of pminer");
DEFINE_string(weibo, "weibo", "graph prefix of weibo");
DEFINE_string(activity, "actdata/activities", "graph prefix of activities");

using namespace std;
using namespace zrpc;

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    LOG(INFO) << "Demo Server Starting...";
    RpcServer* server = RpcServer::CreateServer(FLAGS_port, FLAGS_threads);

    // LOG(INFO) << "Loading aminer data...";
    // auto aminer = unique_ptr<AMinerData>(new AMinerData(FLAGS_aminer.c_str()));
    // LOG(INFO) << "Loading pminer data...";
    // auto pminer = unique_ptr<PMinerData>(new PMinerData(FLAGS_pminer.c_str()));
    // LOG(INFO) << "Loading weibo data...";
    // auto weibo = unique_ptr<WeiboData>(new WeiboData(FLAGS_weibo.c_str()));
    LOG(INFO) << "Loading activity data...";
    auto activity = unique_ptr<ActivityData>(new ActivityData(FLAGS_activity.c_str()));

    LOG(INFO) << "Setting up services...";
    //SearchService* service = SearchService::CreateService(std::move(aminer), std::move(pminer), std::move(weibo), std::move(activity));
    //service->attachTo(server);
    SearchService* service = SearchService::CreateService(std::move(activity));
    service->attachTo(server);

    LOG(INFO) << "Trying to bringing our services up...";
    server->run();

    LOG(INFO) << "Exiting...";
    return 0;
}
