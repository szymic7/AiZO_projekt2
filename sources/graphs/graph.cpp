#include <iostream>
#include "../../headers/graphs/graph.h"

using namespace std;

Graph::Graph(int v, int d) {
    vertices = v;
    density = d;
    edges = 0;
    adjacencyList = nullptr;
    indicenceMatrix = nullptr;
}

void Graph::loadGraph(string txt) {

}

void Graph::generateGraph() {

}

void Graph::showAdjacencyList() {

}


void Graph::showIncidenceMatrix() {

    cout << "Macierz incydencji:\n" << endl;

    // Pierwszy wiersz - etykiety krawedzi
    cout << "v\\e ";
    for(int i = 0; i < edges; i++) {
        cout << "e" << i << " ";
        if(i < 10) cout << " ";
    }
    cout << endl;

    for(int i = 0; i < vertices; i++) {
        // Pierwsza kolumna - etykiety wiercholkow
        cout << "v" << i << " ";
        if(i < 10) cout << " ";

        // Pozostale kolumny
        for (int j = 0; j < edges; j++) {
            int number = indicenceMatrix[i][j];
            if(number >= 0) cout << " ";
            cout << number << " ";
            if(number > -10 && number < 10) cout << " ";
        }

        cout << endl;

    }

}

void Graph::setIncidenceMatrix(int **matrix) {
    indicenceMatrix = matrix;
}

void Graph::setEdges(int e) {
    edges = e;
}
