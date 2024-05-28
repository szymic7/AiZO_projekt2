
#ifndef AIZO_PROJEKT2_BELLMANFORD_H
#define AIZO_PROJEKT2_BELLMANFORD_H

#include "../graphs/graph.h"
#include "algorithm.h"

class BellmanFord : public Algorithm {

    int start, end;
    List pathList, pathMatrix;
    int pathWeightList, pathWeightMatrix;

public:

    BellmanFord();
    void setStart(int s);
    void setEnd(int e);
    void algorithmList();
    void algorithmMatrix();
    void showPathList();
    void showPathMatrix();

};

#endif //AIZO_PROJEKT2_BELLMANFORD_H
