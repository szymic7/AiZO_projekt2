#include <iostream>
#include "../../headers/graphs/edge.h"

using namespace std;

Edge::Edge(int e, int w) {
    //start = -1;
    end = e;
    weight = w;
    nextEdge = nullptr;
}

void Edge::setNext(Edge *next) {
    nextEdge = next;
}

/*void Edge::setStart(int s) {
    start = s;
}*/

Edge* Edge::getNext() {
    return nextEdge; // zwracany wskaznik na kolejna krawedz lub nullptr
}

int Edge::getEnd() {
    return end;
}

int Edge::getWeight() {
    return weight;
}

void Edge::printEdge() {
    cout << "(" << end << ":" << weight << ")";
}