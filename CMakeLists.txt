cmake_minimum_required(VERSION 3.10)
project(computational-topology)

# Set some compilation options.
set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 3.3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Graph library
set(GRAPH_SRCS
  graphs/disjoint_set_system.cc
  graphs/planar_graph.cc
  graphs/tutte_embedding.cc
  graphs/graphviz_utils.cc)
add_library(topo-graphs-lib STATIC ${GRAPH_SRCS})
target_include_directories(topo-graphs-lib PUBLIC .)
target_link_libraries(topo-graphs-lib PUBLIC Eigen3::Eigen)
target_compile_options(topo-graphs-lib PRIVATE -Wall)
# Make library reachable by other cmake projects.
export(PACKAGE topo-graphs-lib)
export(TARGETS topo-graphs-lib FILE topo-graphs-libConfig.cmake)

# Unit testing.
enable_testing()
include(GoogleTest)
# -- Graph library.
add_executable(disjoint_set_system_test graphs/disjoint_set_system_test.cc)
target_link_libraries(disjoint_set_system_test topo-graphs-lib gtest_main)
gtest_discover_tests(disjoint_set_system_test)

add_executable(planar_graph_test graphs/planar_graph_test.cc)
target_link_libraries(planar_graph_test topo-graphs-lib gtest_main)
gtest_discover_tests(planar_graph_test)

add_executable(tutte_embedding_test graphs/tutte_embedding_test.cc)
target_link_libraries(tutte_embedding_test topo-graphs-lib gtest_main)
gtest_discover_tests(tutte_embedding_test)
