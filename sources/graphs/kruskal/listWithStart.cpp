#include <iostream>
#include "../../../headers/graphs/kruskal/listWithStart.h"

using namespace std;

ListWithStart::ListWithStart(EdgeWithStart *edge) {
    firstEdge = edge;
}


void ListWithStart::addEdge(EdgeWithStart *pEdge) {

    if (firstEdge == nullptr) {
        firstEdge = pEdge;
        return;
    }

    EdgeWithStart *lastEdge = firstEdge;  // poczatkowo lastEdge to pierwsza krawedz

    // szukamy ostatniej krawedzi na liscie
    while (lastEdge->getNext() != nullptr) {
        lastEdge = lastEdge->getNext();
    }

    // po znalezieniu ostatniej krawedzi
    lastEdge->setNext(pEdge);

}


EdgeWithStart *ListWithStart::getFirstEdge() {
    return firstEdge;
}


void ListWithStart::printList() {

    if(firstEdge != nullptr) {

        EdgeWithStart *current = firstEdge;

        while(current != nullptr) {
            current->printEdge();
            current = current->getNext();
        }

    } else {

        cout << endl << "Lista krawedzi jest pusta." << endl;

    }

}


void ListWithStart::clear() {

    EdgeWithStart *current = firstEdge;
    while (current != nullptr) {
        EdgeWithStart *temp = current;
        current = current->getNext();
        delete temp;
    }
    firstEdge = nullptr;

}
