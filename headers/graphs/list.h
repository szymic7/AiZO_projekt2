#ifndef AIZO_PROJEKT2_LIST_H
#define AIZO_PROJEKT2_LIST_H

#include "edge.h"

class List {

    Edge *firstEdge;

public:
    List(Edge *first = nullptr);
    void addEdge(Edge *edge); // przed wywolaniem trzeba utworzyc wskaznik na edge
};

#endif //AIZO_PROJEKT2_LIST_H
