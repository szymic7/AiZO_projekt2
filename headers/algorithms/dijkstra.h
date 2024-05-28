#ifndef AIZO_PROJEKT2_DIJKSTRA_H
#define AIZO_PROJEKT2_DIJKSTRA_H

#include "algorithm.h"
#include "../../headers/graphs/list.h"

class Dijkstra : public Algorithm {

    int start, end;
    List pathList, pathMatrix;
    int pathWeightList, pathWeightMatrix;
    int *d, *p;


public:

    Dijkstra();
    void setStart(int s);
    void setEnd(int e);
    void algorithmList();
    void algorithmMatrix();
    void showPathList();
    void showPathMatrix();

};

#endif //AIZO_PROJEKT2_DIJKSTRA_H
