#include <iostream>
#include <random>
#include "list.h"


using namespace std;

#ifndef AIZO_PROJEKT2_GRAPH_H
#define AIZO_PROJEKT2_GRAPH_H

class Graph {

    int vertices;   // liczba wierzcholkow grafu
    int density;    // gestosc grafu [%] - stosunek l. krawedzi do maksymalnej l. krawedzi dla danej liczby wierzcholkow
    int edges;      // zmienna pomocnicza

    List *adjacencyList;        // tablica list - |V| list, w kazdej maksymalnie |E| krawedzi
    int **incidenceMatrix;    // tablica dwuwymiarowa, wiersze = wierzcholki, kolumny = krawedzie

public:
    Graph(int v = 0, int d = 0);
    void setVertices(int v);
    void setDensity(int d);
    void loadGraph(string txt, bool directed);
    void generateGraph(bool directed, std::default_random_engine& rng);
    int getVertices();
    int getEdges();
    List *getAdjacencyList();
    int **getIncidenceMatrix();
    void clearAdjacencyList();
    void showAdjacencyList();
    void showIncidenceMatrix();

};

#endif //AIZO_PROJEKT2_GRAPH_H
