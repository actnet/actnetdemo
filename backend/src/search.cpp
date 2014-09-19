#include <chrono>
#include <algorithm>
#include <sstream>
#include <vector>

#include "indexing/search.hpp"
#include "search.hpp"
#include "interface.pb.h"
#include "expert_searcher.hpp"
#include "group_searcher.hpp"
#include "user_searcher.hpp"

using namespace std;
using namespace demoserver;
using namespace indexing;
using namespace std::chrono;
using namespace sae::io;

struct SearchServiceImpl : public SearchService {
    SearchServiceImpl(std::unique_ptr<AMinerData>&& adata, std::unique_ptr<PMinerData>&& pdata, std::unique_ptr<WeiboData>&& wdata, std::unique_ptr<ActivityData>&& actdata);
    SearchServiceImpl(std::unique_ptr<ActivityData>&& actdata);
    ~SearchServiceImpl() {}

    //aminer services
    bool PubSearch(const std::string&, std::string&);
    bool PubSearchByAuthor(const std::string&, std::string&);
    bool AuthorSearch(const std::string&, std::string&);
    bool AuthorSearchById(const string& input, string& output);
    bool InfluenceSearchByAuthor(const string& input, string& output);
    bool JConfSearch(const string& input, string& output);

    //pminer services
    bool PatentSearch(const std::string&, std::string&);
    bool PatentSearchByInventor(const std::string&, std::string&);
    bool PatentSearchByGroup(const std::string&, std::string&);
    bool GroupSearch(const std::string&, std::string&);
    bool GroupSearchById(const std::string&, std::string&);
    bool InventorSearch(const std::string&, std::string&);
    bool InventorSearchById(const std::string&, std::string&);
    bool InfluenceSearchByGroup(const string& input, string& output);

    //weibo services
    bool WeiboSearch(const std::string&, std::string&);
    bool UserSearch(const std::string&, std::string&);
    bool WeiboSearchByUser(const string& input, string& output);
    bool InfluenceSearchByUser(const string& input, string& output);
    bool UserSearchById(const string& input, string& output);

     //acrivity services
    bool ActivitySearchByName(const std::string&, std::string&);
    bool ActivitySearchSimilar(const std::string&, std::string&);
    bool ActivitySearchCity(const std::string&, std::string&);
    bool ActivitySearchUser(const std::string&, std::string&);
    bool ListSearchByActivity(const std::string&, std::string&);
    bool WeiboSearchByActivity(const std::string&, std::string&);
    bool CenterSearchByActivity(const std::string&, std::string&);
    bool ActivitySearchAllByName(const std::string&, std::string&);


    void attachTo(zrpc::RpcServer* server) {
        LOG(INFO) << "Binding  services...";
        auto b = zrpc::make_binder(*this);

        //aminer services
        server->addMethod("PubSearch", b(&SearchServiceImpl::PubSearch));
        server->addMethod("PubSearchByAuthor", b(&SearchServiceImpl::PubSearchByAuthor));
        server->addMethod("AuthorSearch", b(&SearchServiceImpl::AuthorSearch));
        server->addMethod("AuthorSearchById", b(&SearchServiceImpl::AuthorSearchById));
        server->addMethod("InfluenceSearchByAuthor", b(&SearchServiceImpl::InfluenceSearchByAuthor));
        server->addMethod("JConfSearch", b(&SearchServiceImpl::JConfSearch));

        //pminer services
        server->addMethod("PatentSearch", b(&SearchServiceImpl::PatentSearch));
        server->addMethod("PatentSearchByGroup", b(&SearchServiceImpl::PatentSearchByGroup));
        server->addMethod("PatentSearchByInventor", b(&SearchServiceImpl::PatentSearchByInventor));
        server->addMethod("GroupSearch", b(&SearchServiceImpl::GroupSearch));
        server->addMethod("GroupSearchById", b(&SearchServiceImpl::GroupSearchById));
        server->addMethod("InventorSearch", b(&SearchServiceImpl::InventorSearch));
        server->addMethod("InventorSearchById", b(&SearchServiceImpl::InventorSearchById));
        server->addMethod("InfluenceSearchByGroup", b(&SearchServiceImpl::InfluenceSearchByGroup));

        //weibo services
        server->addMethod("UserSearch", b(&SearchServiceImpl::UserSearch));
        server->addMethod("UserSearchById", b(&SearchServiceImpl::UserSearchById));
        server->addMethod("WeiboSearch", b(&SearchServiceImpl::WeiboSearch));
        server->addMethod("WeiboSearchByUser", b(&SearchServiceImpl::WeiboSearchByUser));
        server->addMethod("InfluenceSearchByUser", b(&SearchServiceImpl::InfluenceSearchByUser));

        //acrivity services
        server->addMethod("ActivitySearchByName", b(&SearchServiceImpl::ActivitySearchByName));
        server->addMethod("ActivitySearchSimilar", b(&SearchServiceImpl::ActivitySearchSimilar));
        server->addMethod("ActivitySearchCity", b(&SearchServiceImpl::ActivitySearchCity));
        server->addMethod("ActivitySearchUser", b(&SearchServiceImpl::ActivitySearchUser));
        server->addMethod("WeiboSearchByActivity", b(&SearchServiceImpl::WeiboSearchByActivity));
        server->addMethod("CenterSearchByActivity", b(&SearchServiceImpl::CenterSearchByActivity));
        server->addMethod("ListSearchByActivity", b(&SearchServiceImpl::ListSearchByActivity));
        server->addMethod("ActivitySearchAllByName", b(&SearchServiceImpl::ActivitySearchAllByName));


        LOG(INFO) << "Services have been set up.";
    };

private:
    std::unique_ptr<AMinerData> aminer;
    std::unique_ptr<PMinerData> pminer;
    std::unique_ptr<WeiboData> weibo;
    std::unique_ptr<ActivityData> activity;
};

namespace {
    string join(const string& sep, const vector<string>& values) {
        std::stringstream ss;
        for(size_t i = 0; i < values.size(); ++i)
        {
            if(i != 0)
                ss << sep;
            ss << values[i];
        }
        return ss.str();
    }

    void fill_entity_by_author(DetailedEntity* de, const Author& author) {
        de->set_title(author.names[0]);
        de->set_original_id(author.id);
        string s = author.position;
        if (author.affiliation.size() > 0) {
            s += ", " + author.affiliation;
        }
        de->set_description(s);
        de->set_imgurl(author.imgurl);
        de->set_topics(join(",", author.topics));
        auto stat = de->add_stat();
        stat->set_type("h-index");
        stat->set_value(author.h_index);
        stat = de->add_stat();
        stat->set_type("citations");
        stat->set_value(author.citation_number);
        stat = de->add_stat();
        stat->set_type("publications");
        stat->set_value(author.publication_number);
    }

    void fill_entity_by_publication(DetailedEntity* de, const Publication& pub) {
        de->set_original_id(pub.id);
        de->set_title(pub.title);
        de->set_description(pub.abstract);
        de->set_topics(join(",", pub.topics));
        auto stat = de->add_stat();
        stat->set_type("year");
        stat->set_value(pub.year);
        stat = de->add_stat();
        stat->set_type("jconf");
        stat->set_value(pub.jconf);
        stat = de->add_stat();
        stat->set_type("citation");
        stat->set_value(pub.citation_number);
    }
}

SearchServiceImpl::SearchServiceImpl(std::unique_ptr<AMinerData>&& adata, std::unique_ptr<PMinerData>&& pdata, std::unique_ptr<WeiboData>&& wdata, std::unique_ptr<ActivityData>&& actdata)
    : aminer(std::move(adata)), pminer(std::move(pdata)), weibo(std::move(wdata)), activity(std::move(actdata)) {
}

SearchServiceImpl::SearchServiceImpl(std::unique_ptr<ActivityData>&& actdata)
    :activity(std::move(actdata)){
}

bool SearchServiceImpl::AuthorSearchById(const string& input, string& output) {
    EntityDetailRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    auto vi = aminer->g->Vertices();
    string query = "";
    int count = 0;
    for (auto& aid : request.id()) {
        vi->MoveTo(aid);
        if (vi->TypeName() == "Author") {
            auto a = parse<Author>(vi->Data());
            DetailedEntity *de = response.add_entity();
            de->set_id(aid);
            fill_entity_by_author(de, a);
            query += to_string(aid) + "\t";
            count ++;
        }
    }
    response.set_query(query);
    response.set_total_count(count);
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::AuthorSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();

    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;
    auto result = ExpertSearcher(*aminer).search(query);
    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = aminer->get<Author>(i.docId);
        de->set_id(i.docId);
        fill_entity_by_author(de, p);
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::JConfSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();
    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;

    auto result = JConfSearcher(*aminer).search(query);
    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = aminer->get<JConf>(i.docId);
        de->set_id(i.docId);
        de->set_title(p.name);
    }
    return response.SerializeToString(&output);
}

// TODO merge into PubSearch
bool SearchServiceImpl::PubSearchByAuthor(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    response.set_query(request.query());

    auto aid = stoi(request.query());
    auto vit = aminer->g->Vertices();
    vit->MoveTo(aid);
    int count = 0;
    for (auto eit = vit->OutEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "Publish") {
            auto vi = aminer->g->Vertices();
            vi->MoveTo(eit->TargetId());
            auto pub = parse<Publication>(vi->Data());
            DetailedEntity *de = response.add_entity();
            de->set_id(eit->TargetId());
            fill_entity_by_publication(de, pub);

            auto re = de->add_related_entity();
            re->set_type("Author");
            for (auto ei = vi->InEdges(); ei->Alive(); ei->Next()) {
                if (ei->TypeName() == "Publish") {
                    re->add_id(ei->SourceId());
                }
            }

            count ++;
        }
    }

    response.set_total_count(count);

    return response.SerializeToString(&output);
}

bool SearchServiceImpl::PubSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();

    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;

    auto result = aminer->search_publications(query);

    if (result.size() > 5000)
        result.resize(5000);

    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto vi = aminer->g->Vertices();
        vi->MoveTo(i.docId);
        auto p = parse<Publication>(vi->Data());
        de->set_id(i.docId);
        fill_entity_by_publication(de, p);

        auto re = de->add_related_entity();
        re->set_type("Author");
        for (auto ei = vi->InEdges(); ei->Alive(); ei->Next()) {
            if (ei->TypeName() == "Publish") {
                re->add_id(ei->SourceId());
            }
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::InfluenceSearchByAuthor(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    InfluenceSearchResponse response;

    auto aid = stoi(request.query());
    response.set_entity_id(aid);

    auto vit = aminer->g->Vertices();
    vit->MoveTo(aid);
    for (auto eit = vit->OutEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "Influence") {
            auto ai = parse<AuthorInfluence>(eit->Data());
            Influence *inf = response.add_influence();
            inf->set_id(eit->TargetId());
            inf->set_topic(ai.topic);
            inf->set_score(ai.score);
        }
    }
    for (auto eit = vit->InEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "Influence") {
            auto ai = parse<AuthorInfluence>(eit->Data());
            Influence *inf = response.add_influenced_by();
            inf->set_id(eit->SourceId());
            inf->set_topic(ai.topic);
            inf->set_score(ai.score);
        }
    }

    return response.SerializeToString(&output);
}

bool SearchServiceImpl::PatentSearchByGroup(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    response.set_query(request.query());

    auto gid = stoi(request.query());
    auto vit = pminer->g->Vertices();
    vit->MoveTo(gid);
    int count = 0;
    for (auto eit = vit->InEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "PatentGroup") {
            auto vi = pminer->g->Vertices();
            vi->MoveTo(eit->SourceId());
            auto pat = parse<Patent>(vi->Data());
            DetailedEntity *de = response.add_entity();
            de->set_id(eit->TargetId());
            de->set_url(to_string(pat.pn));
            de->set_title(pat.title);
            auto stat = de->add_stat();
            stat->set_type("year");
            stat->set_value(pat.year);
            if (pat.inventors.size() > 0) {
                string inventors = pat.inventors[0];
                for (int i = 1; i < pat.inventors.size(); i++)
                    inventors += ", " + pat.inventors[i];
                de->set_description(inventors);
            }
            count ++;
        }
    }

    response.set_total_count(count);

    return response.SerializeToString(&output);
}

bool SearchServiceImpl::PatentSearchByInventor(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    response.set_query(request.query());

    auto iid = stoi(request.query());
    auto vit = pminer->g->Vertices();
    vit->MoveTo(iid);
    int count = 0;
    for (auto eit = vit->OutEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "PatentInventor") {
            auto vi = pminer->g->Vertices();
            vi->MoveTo(eit->TargetId());
            auto pat = parse<Patent>(vi->Data());
            DetailedEntity *de = response.add_entity();
            de->set_id(eit->TargetId());
            de->set_url(to_string(pat.pn));
            de->set_title(pat.title);
            auto stat = de->add_stat();
            stat->set_type("year");
            stat->set_value(pat.year);

            auto re = de->add_related_entity();
            re->set_type("Inventor");
            for (auto ei = vi->InEdges(); ei->Alive(); ei->Next()) {
                if (ei->TypeName() == "PatentInventor") {
                    re->add_id(ei->SourceId());
                }
            }

            count ++;
        }
    }

    response.set_total_count(count);

    return response.SerializeToString(&output);
}

bool SearchServiceImpl::PatentSearch(const string& input, string& output) {

    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();

    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;

    auto result = pminer->search_patents(query);

    if (result.size() > 5000)
        result.resize(5000);

    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = pminer->get<Patent>(i.docId);
        de->set_id(i.docId);
        de->set_url(to_string(p.pn));
        de->set_title(p.title);
        de->set_original_id(p.id);
        auto stat = de->add_stat();
        stat->set_type("year");
        stat->set_value(p.year);

        auto re = de->add_related_entity();
        re->set_type("Inventor");
        auto vi = pminer->g->Vertices();
        vi->MoveTo(i.docId);
        for (auto ei = vi->InEdges(); ei->Alive(); ei->Next()) {
            if (ei->TypeName() == "PatentInventor") {
                re->add_id(ei->SourceId());
            }
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::GroupSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();

    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;

    auto result = GroupSearcher(*pminer).search(query);
    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = pminer->get<Group>(i.docId);
        de->set_id(i.docId);
        de->set_title(p.name);
        de->set_imgurl(p.imgurl);
        auto stat = de->add_stat();
        stat->set_type("Patents");
        stat->set_value(p.patCount);
        de->set_original_id(p.id);
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::GroupSearchById(const string& input, string& output) {
    EntityDetailRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    string query = "";
    int count = 0;
    auto vi = pminer->g->Vertices();
    for (auto& gid : request.id()) {
        vi->MoveTo(gid);
        if (vi->TypeName() == "Group") {
            DetailedEntity *de = response.add_entity();
            auto p = parse<Group>(vi->Data());
            de->set_id(gid);
            de->set_title(p.name);
            de->set_imgurl(p.imgurl);
            auto stat = de->add_stat();
            stat->set_type("Patents");
            stat->set_value(p.patCount);
            de->set_original_id(p.id);
            query += to_string(gid) + "\t";
            count ++;
        }
    }
    response.set_query(query);
    response.set_total_count(count);
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::InventorSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();
    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;

    auto result = InventorSearcher(*pminer).search(query);
    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = pminer->get<Inventor>(i.docId);
        de->set_id(i.docId);
        de->set_title(p.name);
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::InventorSearchById(const string& input, string& output) {
    EntityDetailRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    string query = "";
    int count = 0;
    auto vi = pminer->g->Vertices();
    for (auto& gid : request.id()) {
        vi->MoveTo(gid);
        if (vi->TypeName() == "Inventor") {
            DetailedEntity *de = response.add_entity();
            auto p = parse<Inventor>(vi->Data());
            de->set_id(gid);
            de->set_title(p.name);
            query += to_string(gid) + "\t";
            count ++;
        }
    }
    response.set_query(query);
    response.set_total_count(count);
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::InfluenceSearchByGroup(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    InfluenceSearchResponse response;

    auto gid = stoi(request.query());
    response.set_entity_id(gid);

    auto vit = pminer->g->Vertices();
    vit->MoveTo(gid);
    for (auto eit = vit->OutEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "GroupInfluence") {
            auto gi = parse<GroupInfluence>(eit->Data());
            Influence *inf = response.add_influence();
            inf->set_id(eit->TargetId());
            inf->set_topic(gi.topic);
            inf->set_score(gi.score);
        }
    }
    for (auto eit = vit->InEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "GroupInfluence") {
            auto gi = parse<GroupInfluence>(eit->Data());
            Influence *inf = response.add_influenced_by();
            inf->set_id(eit->SourceId());
            inf->set_topic(gi.topic);
            inf->set_score(gi.score);
        }
    }

    return response.SerializeToString(&output);
}


bool SearchServiceImpl::WeiboSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();

    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;
    auto result = weibo->search_weibos(query);

    if (result.size() > 5000)
        result.resize(5000);
    EntitySearchResponse response;
    response.set_total_count(result.size());
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = weibo->get<Weibo>(i.docId);
        de->set_title(p.text);
        de->set_id(i.docId);
        auto stat = de->add_stat();
        stat->set_type("Reposts");
        stat->set_value(p.reposts_count);
        stat = de->add_stat();
        stat->set_type("Comments");
        stat->set_value(p.comments_count);
        de->set_description(p.created_at);

        auto re = de->add_related_entity();
        re->set_type("Author");
        auto vi = weibo->g->Vertices();
        vi->MoveTo(i.docId);
        for (auto ei = vi->InEdges(); ei->Alive(); ei->Next()) {
            if (ei->TypeName() == "UserWeibo") {
                re->add_id(ei->SourceId());
            }
        }
    }
    return response.SerializeToString(&output);
}


bool SearchServiceImpl::UserSearch(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);
    string query = request.query();

    int offset = request.has_offset() ? request.offset() : 0;
    int count = request.has_count() ? request.count() : 50;

    auto result = UserSearcher(*weibo).search(query);
    EntitySearchResponse response;
    response.set_total_count(count);
    response.set_query(query);
    for (int ri = offset; ri < result.size() && ri - offset < count; ri++) {
        auto i = result[ri];
        DetailedEntity *de = response.add_entity();
        auto p = weibo->get<User>(i.docId);
        de->set_id(i.docId);
        de->set_title(p.name);
        de->set_description(p.description);
        de->set_imgurl(p.profile_image_url);
        auto stat = de->add_stat();
        stat->set_type("Followers");
        stat->set_value(p.followers_count);
        // p.id is too long for int
        de->set_url(p.id);
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::InfluenceSearchByUser(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    InfluenceSearchResponse response;

    auto uid = stoi(request.query());
    response.set_entity_id(uid);

    auto vit = weibo->g->Vertices();
    vit->MoveTo(uid);
    for (auto eit = vit->OutEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "UserInfluence") {
            auto ui = parse<UserInfluence>(eit->Data());
            Influence *inf = response.add_influence();
            inf->set_id(eit->TargetId());
            inf->set_topic(-1);
            inf->set_score(ui.weight);
        }
    }
    for (auto eit = vit->InEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "UserInfluence") {
            auto ui = parse<UserInfluence>(eit->Data());
            Influence *inf = response.add_influenced_by();
            inf->set_id(eit->SourceId());
            inf->set_topic(-1);
            inf->set_score(ui.weight);
        }
    }

    return response.SerializeToString(&output);
}


bool SearchServiceImpl::WeiboSearchByUser(const string& input, string& output) {
    EntitySearchRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    response.set_query(request.query());

    auto uid = stoi(request.query());
    auto vit = weibo->g->Vertices();
    vit->MoveTo(uid);
    int count = 0;
    for (auto eit = vit->OutEdges(); eit->Alive(); eit->Next()) {
        if (eit->TypeName() == "UserWeibo") {
            auto vi = weibo->g->Vertices();
            vi->MoveTo(eit->TargetId());
            auto weibo = parse<Weibo>(vi->Data());
            DetailedEntity *de = response.add_entity();
            de->set_title(weibo.text);
            de->set_id(eit->TargetId());
            auto stat = de->add_stat();
            stat->set_type("Reposts");
            stat->set_value(weibo.reposts_count);
            stat = de->add_stat();
            stat->set_type("Comments");
            stat->set_value(weibo.comments_count);
            de->set_description(weibo.created_at);

            count ++;
        }
    }
    response.set_total_count(count);

    return response.SerializeToString(&output);
}

bool SearchServiceImpl::UserSearchById(const string& input, string& output) {
    EntityDetailRequest request;
    request.ParseFromString(input);

    EntitySearchResponse response;
    string query = "";
    response.set_query(query);

    int count = 0;
    auto vi = weibo->g->Vertices();
    for (auto& uid : request.id()) {
        vi->MoveTo(uid);
        if (vi->TypeName() == "User") {
            DetailedEntity *de = response.add_entity();
            auto p = parse<User>(vi->Data());
            de->set_id(uid);
            de->set_title(p.name);
            de->set_description(p.description);
            de->set_imgurl(p.profile_image_url);
            auto stat = de->add_stat();
            stat->set_type("Followers");
            stat->set_value(p.followers_count);
            de->set_url(p.id);
            count ++;
        }
    }
    response.set_total_count(count);
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::ActivitySearchByName(const string& input, string& output) {

    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    LOG(INFO) << "size:"<<result.size();
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        ActivityEntity *de = response.add_activities();
        /*name*/
        de->set_name(p.name);
        /*text*/
        de->set_verb(p.text.Verb);
        de->set_object(p.text.Object);
        /*spatial*/
        int instance_count = 0;
        for(vector<Instance>::iterator it = p.instances.begin(); 
            it != p.instances.end() && instance_count < 1000; it++)
        {
            ActivityPoint *pos = de->add_points();
            pos->set_lat(it->lantitude);
            pos->set_lng(it->longtitude);

            // ActivityPOI *poi = de->add_pois();
            // poi->set_id(it->microblogid);
            // poi->set_name("");
            // poi->set_type("");
            // poi->set_city("");
            // poi->set_lat(it->lantitude);
            // poi->set_lng(it->longtitude);

            de->add_timestamps(it->timestamp);
            instance_count++;
        }
        //poi
        instance_count = 0;
        for(vector<string>::iterator it = p.pois.begin(); 
            it != p.pois.end() && instance_count < 1000; it++)
        {
            ActivityPOI *poi = de->add_pois();
            poi->set_id("");
            poi->set_name("");
            poi->set_type(*it);
            poi->set_city("");
            poi->set_lat(0);
            poi->set_lng(0);
        }
        //next
        auto vi = activity->g->Vertices();
        vi->MoveTo(i);
        int edge_type = activity->g->EdgeTypeIdOf("Next");
        int next_count = 0;
        for(auto ei = vi->OutEdges(); ei->Alive() && next_count < 100; ei->Next()){
            if(ei->TypeId() == edge_type){
                ActivityNext *next = de->add_nextpoints();
                //next->set_name(parse<Activity>(ei->Target()->Data()).name);
                next->set_name(parse<Next>(ei->Data()).name);
                next->set_duration(parse<Next>(ei->Data()).dur);
                next_count++;
            }
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::ActivitySearchSimilar(const string& input, string& output) {

    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    LOG(INFO) << "size:"<<result.size();
    for (int ri = 1; ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        if(p.name == query)
            continue;
        double sum = 0, pos = 0;
        for( ; sum < p.instances.size(); sum++)
            if(p.instances[sum].sentiment == "pos")
                pos++;
        if(sum == 0)
            sum = 1;
        double per = (double)((int)(pos / sum * 100))/100;
        ActivitySimilar *de = response.add_similars();
        de->set_name(p.name);
        de->set_sim(per);
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::ListSearchByActivity(const string& input, string& output) {

    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    int instance_count = 0;
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        for(vector<Instance>::iterator it = p.instances.begin(); 
            it != p.instances.end() && instance_count < 200; it++)
        {
            ActivityList *de = response.add_actlists();
            de->set_sen(it->sentiment);
            de->set_lat(it->lantitude);
            de->set_lng(it->longtitude);
            instance_count++;
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::CenterSearchByActivity(const string& input, string& output) {

    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    LOG(INFO) << "size:"<<result.size();
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        ActivityCenterList *de = response.add_lists();
        auto vi = activity->g->Vertices();
        vi->MoveTo(i);
        int edge_type = activity->g->EdgeTypeIdOf("CenterEdge");
        for(auto ei = vi->InEdges(); ei->Alive(); ei->Next()){
            if(ei->TypeId() == edge_type){
                auto center = ei->Source();
                for(auto ci = center->OutEdges(); ci->Alive(); ci->Next()){
                    de->add_activities(parse<Activity>(ci->Target()->Data()).name);
                }
            }
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::ActivitySearchCity(const string& input, string& output) {

    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();

    ActivitySearchResponse response;
    activity->search_city_activity();
    response.set_total_count(activity->get_total_count());
    /*for(map<string, vector<string>>::iterator it = p.begin(); it != p.end(); it++)
    {
        ActivitySimilar *de = response.add_cities();
        de->set_name(it->first);
        for(vector<string> at = it->second.begin(); at != it->second.end(); at++)
            de->add_activity(at->name);
    }*/
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::ActivitySearchUser(const string& input, string& output) {
    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    LOG(INFO) << "size:"<<result.size();
    int user_count = 0;
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        ActivityUser *de = response.add_users();
        auto vi = activity->g->Vertices();
        vi->MoveTo(i);
        int edge_type = activity->g->EdgeTypeIdOf("UserEdge");
        for(auto ei = vi->InEdges(); ei->Alive() && user_count < 100; ei->Next()){
            if(ei->TypeId() == edge_type){
                de->add_ids(parse<UUser>(ei->Source()->Data()).userid);
                user_count++;
            }
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::WeiboSearchByActivity(const string& input, string& output) {

    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    LOG(INFO) << "size:"<<result.size();
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        for(vector<Instance>::iterator it = p.instances.begin(); it != p.instances.end(); it++)
        {
            ActivityWeibo *de = response.add_weibos();
            de->set_id(it->microblogid);
            de->set_weibo("");
        }
    }
    return response.SerializeToString(&output);
}

bool SearchServiceImpl::ActivitySearchAllByName(const string& input, string& output) {
    ActivitySearchRequest request;
    request.ParseFromString(input);
    string query = request.name();
    auto result = activity->search_activities(query);
    if (result.size() > 15)
        result.resize(15);
    ActivitySearchResponse response;
    response.set_total_count(activity->get_total_count());
    LOG(INFO) << "size:"<<result.size();
    /*************activity*************/
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        ActivityEntity *de = response.add_activities();
        //name
        de->set_name(p.name);
        //text
        de->set_verb(p.text.Verb);
        de->set_object(p.text.Object);
        //spatial
        int instance_count = 0;
        for(vector<Instance>::iterator it = p.instances.begin(); 
            it != p.instances.end() && instance_count < 1000; it++)
        {
            ActivityPoint *pos = de->add_points();
            pos->set_lat(it->lantitude);
            pos->set_lng(it->longtitude);
            de->add_timestamps(it->timestamp);
            instance_count++;
        }
        //poi
        instance_count = 0;
        for(vector<string>::iterator it = p.pois.begin(); 
            it != p.pois.end() && instance_count < 1000; it++)
        {
            ActivityPOI *poi = de->add_pois();
            poi->set_id("");
            poi->set_name("");
            poi->set_type(*it);
            poi->set_city("");
            poi->set_lat(0);
            poi->set_lng(0);
        }
        //next
        auto vi = activity->g->Vertices();
        vi->MoveTo(i);
        int edge_type = activity->g->EdgeTypeIdOf("Next");
        int next_count = 0;
        for(auto ei = vi->OutEdges(); ei->Alive() && next_count < 50; ei->Next()){
            if(ei->TypeId() == edge_type){
                ActivityNext *next = de->add_nextpoints();
                //next->set_name(parse<Activity>(ei->Target()->Data()).name);
                next->set_name(parse<Next>(ei->Data()).name);
                next->set_duration(parse<Next>(ei->Data()).dur);
                next_count++;
            }
        }
    }
    /*************similar*************/
    for (int ri = 1; ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        if(p.name == query)
            continue;
        ActivitySimilar *de = response.add_similars();
        de->set_name(p.name);
        de->set_sim(0.8);
    }
    /*************sentiment*************/
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        Activity p = activity->get<Activity>(i);
        int instance_count = 0;
        for(vector<Instance>::iterator it = p.instances.begin(); 
            it != p.instances.end() && instance_count < 1000; it++)
        {
            ActivityList *de = response.add_actlists();
            de->set_sen(it->sentiment);
            de->set_lat(it->lantitude);
            de->set_lng(it->longtitude);
            instance_count++;
        }
    }
    /***************user***************/
    for (int ri = 0; ri < 1 && ri < result.size(); ri++)
    {
        auto i = result[ri];
        ActivityUser *de = response.add_users();
        auto vi = activity->g->Vertices();
        vi->MoveTo(i);
        int edge_type = activity->g->EdgeTypeIdOf("UserEdge");
        int user_count = 0;
        for(auto ei = vi->InEdges(); ei->Alive() && user_count < 100; ei->Next()){
            if(ei->TypeId() == edge_type){
                de->add_ids(parse<UUser>(ei->Source()->Data()).userid);
                user_count++;
            }
        }
    }
    return response.SerializeToString(&output);
}



SearchService* SearchService::CreateService(std::unique_ptr<AMinerData>&& adata, std::unique_ptr<PMinerData>&& pdata, std::unique_ptr<WeiboData>&& wdata, std::unique_ptr<ActivityData>&& actdata) {
    return new SearchServiceImpl(std::move(adata), std::move(pdata), std::move(wdata), std::move(actdata));
}

SearchService* SearchService::CreateService(std::unique_ptr<ActivityData>&& actdata) {
    return new SearchServiceImpl(std::move(actdata));
}
