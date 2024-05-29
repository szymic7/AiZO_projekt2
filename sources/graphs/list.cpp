#include <iostream>
#include "../../headers/graphs/list.h"

using namespace std;

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

void List::addEdgeFront(Edge *edge) {

    // Jesli lista jest pusta
    if(firstEdge == nullptr) firstEdge = edge;

    else {
        edge->setNext(firstEdge);
        firstEdge = edge;
    }

}


Edge *List::getFirstEdge() {
    return firstEdge;
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

void List::printList() {

    // Jesli lista jest pusta
    if(firstEdge == nullptr) return;

    // Wyswietlenie pierwszej krawedzi (bez strzalki poprzedzajacej)
    Edge *edge = firstEdge;
    edge->printEdge();

    // Wyswietlanie kolejnych krawedzi - ze strzalka poprzedzajaca
    while(edge->getNext() != nullptr) {
        cout << " -> ";
        edge = edge->getNext();
        edge->printEdge();
    }

}

void List::clear() {
    Edge *current = firstEdge;
    while (current != nullptr) {
        Edge *temp = current;
        current = current->getNext();
        delete temp;
    }
    firstEdge = nullptr;
}
