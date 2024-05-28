

#ifndef AIZO_PROJEKT2_ALGORITHM_H
#define AIZO_PROJEKT2_ALGORITHM_H

#include "../graphs/graph.h"

class Algorithm {

    Graph *graph;

public:

    Algorithm();
    void setGraph(Graph* g);
    Graph *getGraph();


};

#endif //AIZO_PROJEKT2_ALGORITHM_H
