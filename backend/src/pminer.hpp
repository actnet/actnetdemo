#pragma once
#include <string>
#include <vector>
#include "serialization/serialization.hpp"

using namespace std;

struct Patent {
    int id;
    int pn;
    string title;
    int year;
    vector<string> inventors;
};

struct Inventor {
    string name;
};

struct Company {
    int id;
    string name;
    int patCount;
    string logo;
    string homepage;
    string terms;
    int gcid;
};

struct Group {
    int id;
    string name;
    int patCount;
    string imgurl;
};

struct PatentInventor {
};

struct PatentGroup {
};

struct PatentCompany {
};

struct CompanyGroup {
};

struct GroupInfluence {
    int topic;
    double score;
};

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, Patent> {
                static void run(sae::serialization::OSerializeStream& ostr, const Patent& p) {
                    ostr << p.id << p.pn << p.title << p.year << p.inventors;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Patent> {
                static void run(sae::serialization::ISerializeStream& istr, Patent& p) {
                    istr >> p.id >> p.pn >> p.title >> p.year >> p.inventors;
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, Company> {
                static void run(sae::serialization::OSerializeStream& ostr, const Company& c) {
                    ostr << c.id << c.name << c.patCount << c.logo << c.homepage << c.terms << c.gcid;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Company> {
                static void run(sae::serialization::ISerializeStream& istr, Company& c) {
                    istr >> c.id >> c.name >> c.patCount >> c.logo >> c.homepage >> c.terms >> c.gcid;
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, Inventor> {
                static void run(sae::serialization::OSerializeStream& ostr, const Inventor& i) {
                    ostr << i.name;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Inventor> {
                static void run(sae::serialization::ISerializeStream& istr, Inventor& i) {
                    istr >> i.name;
                }
            };
        }
    }
}

namespace sae {
    namespace serialization {
        namespace custom_serialization_impl {
            template <>
            struct serialize_impl<sae::serialization::OSerializeStream, Group> {
                static void run(sae::serialization::OSerializeStream& ostr,const  Group& g) {
                    ostr << g.id << g.name << g.patCount << g.imgurl;
                }
            };

            template <>
            struct deserialize_impl<sae::serialization::ISerializeStream, Group> {
                static void run(sae::serialization::ISerializeStream& istr, Group& g) {
                    istr >> g.id >> g.name >> g.patCount >> g.imgurl;
                }
            };
        }
    }
}
