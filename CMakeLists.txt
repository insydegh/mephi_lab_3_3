cmake_minimum_required(VERSION 3.20)
project(graph)

set(CMAKE_CXX_STANDARD 20)
set(GRAPHVIZ_INCLUDE_DIR "C:/Program Files/Graphviz/include/graphviz")
set(GRAPHVIZ_LIB_DIR "C:/Program Files/Graphviz/lib/")


add_executable(graph main.cpp Graph.h UndirectedGraph.h ISorter.h)

include_directories(Sequence)

include_directories("${GRAPHVIZ_INCLUDE_DIR}")

target_link_libraries(graph "C:/Program Files/Graphviz/")