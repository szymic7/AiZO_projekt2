#ifndef AIZO_PROJEKT2_EDGEWITHSTART_H
#define AIZO_PROJEKT2_EDGEWITHSTART_H

#include "../edge.h"

class EdgeWithStart : public Edge {

    int start;
    EdgeWithStart *nextEdge;

public:

    EdgeWithStart(int s = -1, int e = -1, int w = 0);
    void setStart(int s);
    void setNext(EdgeWithStart *next);
    int getStart();
    EdgeWithStart* getNext();
    void printEdge();

};

#endif //AIZO_PROJEKT2_EDGEWITHSTART_H
