#include "../../headers/graphs/list.h"

List::List(Edge *first) {
    firstEdge = first;
}

void List::addEdge(Edge *pEdge) {

    Edge lastEdge = *firstEdge;  // poczatkowo lastEdge to pierwsza krawedz

    // szukamy ostatniej krawedzi na liscie
    while(lastEdge.getNext() != nullptr) {
        lastEdge = *lastEdge.getNext();
    }

    // po znalezieniu osttniej krawedzi
    lastEdge.setNext(pEdge);

}
