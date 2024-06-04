#include <vector>
#include <algorithm>
#include "../../headers/algorithms/kruskal.h"


Kruskal::Kruskal() : Algorithm() {
    mstList = nullptr;
    mstMatrix = nullptr;
    mstWeightList = -1;
    mstWeightMatrix = -1;
}


int Kruskal::findSet(int v, std::vector<int>& parent) {
    if (v == parent[v]) return v;   // jesli v jest reprezentantem w swoim zbiorze
    return parent[v] = findSet(parent[v], parent);  // jesli nie to szukamy rekurencyjnie reprezentanta
}


void Kruskal::unionSets(int a, int b, std::vector<int>& parent, std::vector<int>& rank) {
    a = findSet(a, parent); // pierwszy zbior
    b = findSet(b, parent); // drugi zbior
    if (a != b) {   // Jesli rangi a i b sa rozne
        if (rank[a] < rank[b])  std::swap(a, b); // aby dolaczyc zbior o mniejszej randze do tego o wiekszej
        parent[b] = a;                                 // dolaczenie zbioru b do zbioru a
        if (rank[a] == rank[b]) rank[a]++;             // jesli rangi zbiorow byly rowne - zwiekszamy range zbioru a
    }
}


void Kruskal::algorithmList() {

    // Wyczyszczenie istniejącej listy MST
    mstList.clear();

    int V = getGraph()->getVertices();
    std::vector<EdgeWithStart*> edges;

    // Utworzenie listy wszystkich krawedzi - szukamy ich w liscie sasiadow
    for (int u = 0; u < V; ++u) {
        for (Edge* edge = getGraph()->getAdjacencyList()[u].getFirstEdge(); edge != nullptr; edge = edge->getNext()) {
            if (u < edge->getEnd()) { // Aby uniknąć dodania każdej krawędzi dwukrotnie
                edges.push_back(new EdgeWithStart(u, edge->getEnd(), edge->getWeight()));
            }
        }
    }

    // Sortowanie krawedzi wg wagi - sortowanie szybkie (zlozonosc: O(ElogE))
    std::sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
        return a->getWeight() < b->getWeight();
    });


    std::vector<int> parent(V);
    std::vector<int> rank(V, 0);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    mstWeightList = 0;

    // Licznik krawedzi dodanych do MST
    int mstEdges = 0;

    for (EdgeWithStart* edge : edges) {
        int u = edge->getStart();
        int v = edge->getEnd();
        int weight = edge->getWeight();

        if (findSet(u, parent) != findSet(v, parent)) { // jesli u i v naleza do roznych zbiorow
            mstList.addEdge(new EdgeWithStart(u, v, weight));   // dodanie krawedzi do rozwiazania
            mstWeightList += weight;    // dodanie wagi krawedzi do calkowitej wagi MST
            mstEdges++;
            unionSets(u, v, parent, rank);  // polaczenie zbiorow u i v
            if(mstEdges >= V-1) break;  // jesli drzewo MST ma juz V-1 krawedzi - koniec algorytmu
        }
    }

    // Wyczyszczenie dynamicznie zaalokowanej listy krawedzi
    for (EdgeWithStart* edge : edges) {
        delete edge;
    }

}


void Kruskal::algorithmMatrix() {

    // Wyczyszczenie istniejącej listy MST
    mstMatrix.clear();

    int V = getGraph()->getVertices();
    int E = getGraph()->getEdges();
    std::vector<EdgeWithStart*> edges;

    // Utworzenie listy wszystkich krawedzi - szukamy ich w macierzy incydencji
    for (int j = 0; j < E; ++j) {   // j - numer kolumny

        int u = -1, v = -1, weight = 0;

        for (int i = 0; i < V; ++i) {   // i - numer wiersza; szukamy u i v (graf nieskierowany, wiec kolejnosc dowolna)

            if (getGraph()->getIncidenceMatrix()[i][j] != 0) {  // krawedz wychodzi z wierzcholka i

                if (u == -1) {  // jesli to pierwszy znaleziony wierzcholek w kolumnie
                    u = i;
                    weight = getGraph()->getIncidenceMatrix()[i][j];
                } else {    // jesli znalezlismy juz pierwszy wierzcholek w kolumnie
                    v = i;
                    break;
                }

            }

        }

        if (u != -1 && v != -1) {
            edges.push_back(new EdgeWithStart(u, v, weight));
        }

    }

    // Sortowanie krawędzi według wagi
    std::sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
        return a->getWeight() < b->getWeight();
    });

    std::vector<int> parent(V);
    std::vector<int> rank(V, 0);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    mstWeightMatrix = 0;

    // Licznik krawedzi dodanych do MST
    int mstEdges = 0;

    for (EdgeWithStart* edge : edges) {
        int u = edge->getStart();
        int v = edge->getEnd();
        int weight = edge->getWeight();

        if (findSet(u, parent) != findSet(v, parent)) {
            mstMatrix.addEdge(new EdgeWithStart(u, v, weight));
            mstWeightMatrix += weight;
            mstEdges++;
            unionSets(u, v, parent, rank);
            if(mstEdges >= V-1) break;  // jesli drzewo MST ma juz V-1 krawedzi - koniec algorytmu
        }
    }

    // Wyczyszczenie dynamicznie zaalokowanej listy krawedzi
    for (EdgeWithStart* edge : edges) {
        delete edge;
    }

}


void Kruskal::showMstList() {

    if(mstList.getFirstEdge() != nullptr) { // jesli MST nie jest puste

        cout << endl << "Minimalne drzewo rozpinajace, znalezione dla reprezentacji listowej grafu:" << endl;
        mstList.printList();
        cout << endl << "Suma krawedzi drzewa MST = " << mstWeightList << endl;

    } else {    // jesli MST jest puste

        cout << endl << "Uruchom algorytm, aby znalezc minimalne drzewo rozpinajace." << endl;

    }

}


void Kruskal::showMstMatrix() {

    if(mstMatrix.getFirstEdge() != nullptr) { // jesli MST nie jest puste

        cout << endl << "Minimalne drzewo rozpinajace, znalezione dla reprezentacji macierzowej grafu:" << endl;
        mstMatrix.printList();
        cout << endl << "Suma krawedzi drzewa MST = " << mstWeightMatrix << endl;

    } else {    // jesli MST jest puste

        cout << endl << "Uruchom algorytm, aby znalezc minimalne drzewo rozpinajace." << endl;

    }

}
