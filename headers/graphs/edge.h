
#ifndef AIZO_PROJEKT2_EDGE_H
#define AIZO_PROJEKT2_EDGE_H

class Edge {

    int end;
    int weight;
    Edge *nextEdge;

public:
    Edge(int end = -1, int weight = 0);
    void setNext(Edge *next); // przed wywolaniem trzeba utowrzyc wskaznik na next
    int getEnd();
    int getWeight();
    Edge* getNext();
    void printEdge();

};

#endif //AIZO_PROJEKT2_EDGE_H
