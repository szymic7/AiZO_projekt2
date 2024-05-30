#include <iostream>
#include "../../../headers/graphs/kruskal/edgeWithStart.h"

using namespace std;

EdgeWithStart::EdgeWithStart(int s, int e, int w) : Edge(e, w) {
    start = s;
    nextEdge = nullptr;
}


void EdgeWithStart::setStart(int s) {
    start = s;
}

void EdgeWithStart::setNext(EdgeWithStart *next) {
    nextEdge = next;
}

int EdgeWithStart::getStart() {
    return start;
}

EdgeWithStart *EdgeWithStart::getNext() {
    return nextEdge;
}

void EdgeWithStart::printEdge() {
    cout << "(" << start << "-" << getEnd() << ": " << getWeight() << ")" << endl;
}