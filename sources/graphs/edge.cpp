#include "../../headers/graphs/edge.h"

Edge::Edge(int e, int w) {
    end = e;
    weight = w;
    nextEdge = nullptr;
}

void Edge::setNext(Edge *next) {
    nextEdge = next;
}

Edge* Edge::getNext() {
    return nextEdge; // zwracany wskaznik na kolejna krawedz lub nullptr
}