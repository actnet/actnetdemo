cmake_minimum_required (VERSION 2.8)
project (demoserver)

find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS interface.proto)

include_directories(${SAEDB_PATH})
include_directories(${GRAPH_PATH})
message(${SAEDB_PATH})
include_directories("${PROTOBUF_INCLUDE_DIRS}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

file (GLOB server_SOURCES
    "support_doc_searcher.hpp"
    "aminer.hpp"
    "aminerdata.hpp"
    "expert_searcher.hpp"
    "pminer.hpp"
    "pminerdata.hpp"
    "group_searcher.hpp"
    "weibo.hpp"
    "weibodata.hpp"
    "user_searcher.hpp"
    "search.*"
    "main.cpp"
    "activitydata.cpp"
    "activitydata.hpp"
    "vectorimporter.cpp"
)

add_executable(server ${server_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(server zrpc google-glog gflags ${PROTOBUF_LIBRARY} aminerdata pminerdata weibodata activitydata)

file (GLOB aminerimporter_SOURCES "aminerimporter.cpp" "csvreader.*")
add_executable(aminerimporter ${aminerimporter_SOURCES})
target_link_libraries(aminerimporter mgraph)

file (GLOB pminerimporter_SOURCES "pminerimporter.cpp")
add_executable(pminerimporter ${pminerimporter_SOURCES})
target_link_libraries(pminerimporter mgraph)

file (GLOB weiboimporter_SOURCES "weiboimporter.cpp")
add_executable(weiboimporter ${weiboimporter_SOURCES})
target_link_libraries(weiboimporter mgraph)

add_definitions(-DOS_LINUX)
file (GLOB aminerdata_SOURCES "aminerdata.cpp" "aminerdata.hpp")
add_library(aminerdata ${aminerdata_SOURCES})
target_link_libraries(aminerdata mgraph indexing ArnetAnalyzer ${CMAKE_CURRENT_SOURCE_DIR}/libICTCLAS50.a)
#target_link_libraries(aminerdata mgraph indexing ArnetAnalyzer)

file (GLOB pminerdata_SOURCES "pminerdata.cpp" "pminerdata.hpp")
add_library(pminerdata ${pminerdata_SOURCES})
target_link_libraries(pminerdata mgraph indexing ArnetAnalyzer ${CMAKE_CURRENT_SOURCE_DIR}/libICTCLAS50.a)
#target_link_libraries(pminerdata mgraph indexing ArnetAnalyzer)

file (GLOB weibodata_SOURCES "weibodata.cpp" "weibodata.hpp")
add_library(weibodata ${weibodata_SOURCES})
target_link_libraries(weibodata mgraph indexing ArnetAnalyzer ${CMAKE_CURRENT_SOURCE_DIR}/libICTCLAS50.a)
#target_link_libraries(weibodata mgraph indexing ArnetAnalyzer)

file (GLOB activitydata_SOURCES "activitydata.cpp" "activitydata.hpp")
add_library(activitydata ${activitydata_SOURCES})
target_link_libraries(activitydata mgraph indexing ArnetAnalyzer ${CMAKE_CURRENT_SOURCE_DIR}/libICTCLAS50.a)
#target_link_libraries(activitydata mgraph indexing ArnetAnalyzer)

message(${demoserver_BINARY_DIR})
