#include <iostream>
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
    void loadGraph(string txt);
    void generateGraph();
    void showAdjacencyList();
    void showIncidenceMatrix();

    // na potrzeby testow
    void setIncidenceMatrix(int **matrix);
    void setEdges(int e = 0);


};

#endif //AIZO_PROJEKT2_GRAPH_H
