project(proto_benchmark)
cmake_minimum_required(VERSION 3.24)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# abseil requires at least c++14
set(CMAKE_CXX_STANDARD 14)
include_directories(CMAKE_CURRENT_SOURCE_DIR)

find_package(Protobuf REQUIRED)
add_subdirectory(abseil-cpp)
add_subdirectory(benchmark)

add_executable(run main.cpp MyProto.pb.cc)
target_link_libraries(run benchmark::benchmark ${PROTOBUF_LIBRARY} absl::status absl::time)
