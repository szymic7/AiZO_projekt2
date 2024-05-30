#ifndef AIZO_PROJEKT2_LISTWITHSTART_H
#define AIZO_PROJEKT2_LISTWITHSTART_H

#include "../list.h"
#include "edgeWithStart.h"

class ListWithStart : public List {

    EdgeWithStart *firstEdge;

public:

    ListWithStart(EdgeWithStart *edge = nullptr);
    void addEdge(EdgeWithStart *edge);
    EdgeWithStart* getFirstEdge();
    void printList();
    void clear();

};

#endif //AIZO_PROJEKT2_LISTWITHSTART_H
