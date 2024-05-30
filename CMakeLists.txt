cmake_minimum_required(VERSION 3.27)
project(AiZO_projekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(AiZO_projekt2 sources/main/main.cpp
        headers/graphs/graph.h
        sources/graphs/graph.cpp
        sources/graphs/list.cpp
        headers/graphs/list.h
        sources/graphs/edge.cpp
        headers/graphs/edge.h
        sources/algorithms/prim.cpp
        headers/algorithms/prim.h
        sources/algorithms/kruskal.cpp
        headers/algorithms/kruskal.h
        sources/algorithms/dijkstra.cpp
        headers/algorithms/dijkstra.h
        sources/algorithms/bellmanFord.cpp
        headers/algorithms/bellmanFord.h
        sources/algorithms/algorithm.cpp
        headers/algorithms/algorithm.h
        sources/graphs/kruskal/edgeWithStart.cpp
        headers/graphs/kruskal/edgeWithStart.h
        sources/graphs/kruskal/listWithStart.cpp
        headers/graphs/kruskal/listWithStart.h
)
