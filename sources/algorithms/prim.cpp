#include <vector>
#include <limits>
#include <queue>
#include <set>
#include "../../headers/algorithms/prim.h"

Prim::Prim() : Algorithm() {
    start = -1;
    mstList = nullptr;
    mstMatrix = nullptr;
    mstWeightList = -1;
    mstWeightMatrix = -1;
    p = nullptr;
}


void Prim::setStart(int s) {
    start = s;
}


void Prim::algorithmList() {

    // Wyczyszczenie istniejącej listy MST
    mstList.clear();
    delete[] p;

    int V = getGraph()->getVertices();
    std::vector<bool> inMST(V, false);
    std::vector<int> key(V, std::numeric_limits<int>::max());

    p = new int[V];
    for(int i = 0; i < V; i++) {
        p[i] = -1;
    }

    key[start] = 0;
    mstWeightList = 0;

    auto comp = [&](int left, int right) { return key[left] > key[right]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);
    pq.push(start);


    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        inMST[u] = true;

        for (Edge* edge = getGraph()->getAdjacencyList()[u].getFirstEdge(); edge != nullptr; edge = edge->getNext()) {
            int v = edge->getEnd();
            int weight = edge->getWeight();

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                p[v] = u;
                pq.push(v);
            }
        }
    }

    // Zapisanie krawedzi nalezacych do MST do listy
    for (int v = 0; v < V; v++) {
        if (p[v] != -1) {
            mstWeightList += key[v];
            mstList.addEdge(new Edge(v, key[v]));
        }
    }

}


void Prim::algorithmMatrix() {
    // Wyczyszczenie istniejącej listy MST
    mstMatrix.clear();
    delete[] p;

    int V = getGraph()->getVertices();
    int E = getGraph()->getEdges();
    std::vector<bool> inMST(V, false);
    std::vector<int> key(V, std::numeric_limits<int>::max());

    p = new int[V];
    for(int i = 0; i < V; i++) {
        p[i] = -1;
    }

    key[start] = 0;
    mstWeightMatrix = 0;

    auto comp = [&](int left, int right) { return key[left] > key[right]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);
    pq.push(start);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        inMST[u] = true;

        // Iteracja po krawędziach wychodzących z wierzchołka u
        for (int j = 0; j < E; j++) {
            int weight = getGraph()->getIncidenceMatrix()[u][j];
            if (weight > 0) {
                // Znalezienie wierzchołka v połączonego z u
                int v = -1;
                for (int k = 0; k < V; ++k) {
                    if (getGraph()->getIncidenceMatrix()[k][j] == weight && k != u) {
                        v = k;
                        break;
                    }
                }
                if (v != -1 && !inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    p[v] = u;
                    pq.push(v);
                }
            }
        }
    }

    // Dodanie krawędzi do MST i obliczenie sumy wag krawędzi
    for (int v = 0; v < V; v++) {
        if (p[v] != -1) {
            mstWeightMatrix += key[v];
            mstMatrix.addEdgeFront(new Edge(v, key[v]));
        }
    }

}


void Prim::showMstList() {

    if(mstList.getFirstEdge() != nullptr) { // jesli MST nie jest puste

        Edge *current = mstList.getFirstEdge();

        cout << endl << "Minimalne drzewo rozpinajace, znalezione dla reprezentacji listowej grafu:" << endl;

        while(current != nullptr) {
            cout << "(" << p[current->getEnd()] << "-" << current->getEnd() << ": " << current->getWeight() << ")" << endl;
            current = current->getNext();               // ustawienie aktualnej krawedzi
        }

        cout << endl << "Suma krawedzi drzewa MST = " << mstWeightList << endl;

    } else {    // jesli MST jest puste

        cout << endl << "Uruchom algorytm, aby znalezc minimalne drzewo rozpinajace." << endl;

    }

}


void Prim::showMstMatrix() {

    if(mstMatrix.getFirstEdge() != nullptr) { // jesli MST nie jest puste

        Edge *current = mstMatrix.getFirstEdge();

        cout << endl << "Minimalne drzewo rozpinajace, znalezione dla reprezentacji macierzowej grafu:" << endl;

        while(current != nullptr) {
            cout << "(" << p[current->getEnd()] << "-" << current->getEnd() << ": " << current->getWeight() << ")" << endl;
            current = current->getNext();               // ustawienie aktualnej krawedzi
        }

        cout << endl << "Suma krawedzi drzewa MST = " << mstWeightMatrix << endl;

    } else {    // jesli MST jest puste

        cout << endl << "Uruchom algorytm, aby znalezc minimalne drzewo rozpinajace." << endl;

    }

}
