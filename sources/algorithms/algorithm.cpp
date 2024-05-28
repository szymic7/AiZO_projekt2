
#include "../../headers/algorithms/algorithm.h"

Algorithm::Algorithm() {
    graph = nullptr;
}

void Algorithm::setGraph(Graph *g) {
    graph = g;
}

Graph *Algorithm::getGraph() {
    return graph;
}
