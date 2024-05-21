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
)
