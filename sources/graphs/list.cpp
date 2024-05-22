#include "../../headers/graphs/list.h"

List::List(Edge *first) {
    firstEdge = first;
}

void List::addEdge(Edge *pEdge) {

    if (firstEdge == nullptr) {
        firstEdge = pEdge;
        return;
    }

    Edge *lastEdge = firstEdge;  // poczatkowo lastEdge to pierwsza krawedz

    // szukamy ostatniej krawedzi na liscie
    while (lastEdge->getNext() != nullptr) {
        lastEdge = lastEdge->getNext();
    }

    // po znalezieniu osttniej krawedzi
    lastEdge->setNext(pEdge);

}

Edge* List::findEdge(int end) {
    Edge *current = firstEdge;
    while (current != nullptr) {
        if (current->getEnd() == end) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}
