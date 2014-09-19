#include <string>
#include "zrpc/zrpc.hpp"
#include "aminerdata.hpp"
#include "pminerdata.hpp"
#include "weibodata.hpp"
#include "activitydata.hpp"

struct SearchService {
	SearchService() {}
	virtual ~SearchService() {}

    static SearchService* CreateService(std::unique_ptr<AMinerData>&& adata, std::unique_ptr<PMinerData>&& pdata, std::unique_ptr<WeiboData>&& wdata, std::unique_ptr<ActivityData>&& actdata);
    static SearchService* CreateService(std::unique_ptr<ActivityData>&& actdata);
	virtual void attachTo(zrpc::RpcServer* server) = 0;
};
