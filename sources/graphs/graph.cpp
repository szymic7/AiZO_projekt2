#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "../../headers/graphs/graph.h"

using namespace std;

Graph::Graph(int v, int d) {
    vertices = v;
    density = d;
    edges = 0;
    adjacencyList = new List[vertices];
    incidenceMatrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        incidenceMatrix[i] = nullptr;
    }
}

void Graph::loadGraph(string txt) {

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
            int number = incidenceMatrix[i][j];
            if(number >= 0) cout << " ";
            cout << number << " ";
            if(number > -10 && number < 10) cout << " ";
        }

        cout << endl;

    }

}




void Graph::generateGraph() {
    if (vertices <= 0) return;

    // Inicjalizacja generatora liczb losowych
    srand(time(0));

    // Obliczenie maksymalnej liczby krawędzi
    int maxEdges = vertices * (vertices - 1) / 2;

    // Obliczenie docelowej liczby krawędzi
    edges = maxEdges * density / 100;

    // Inicjalizacja macierzy incydencji
    for (int i = 0; i < vertices; ++i) {
        delete[] incidenceMatrix[i]; // Zapewnienie braku wycieków pamięci
        incidenceMatrix[i] = new int[edges];
        std::fill(incidenceMatrix[i], incidenceMatrix[i] + edges, 0);
    }

    // Lista możliwych krawędzi
    std::vector<std::pair<int, int>> possibleEdges;
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            possibleEdges.emplace_back(i, j);
        }
    }

    // Utrzymanie spójności grafu
    std::vector<bool> connected(vertices, false);
    std::vector<int> connectedVertices;
    connectedVertices.push_back(0);
    connected[0] = true;

    int edgeCount = 0;

    while (edgeCount < edges) {
        if (edgeCount < vertices - 1) {
            // Drzewo rozpinające
            int u = connectedVertices[rand() % connectedVertices.size()];
            int v = rand() % vertices;
            while (connected[v]) {
                v = rand() % vertices;
            }
            connected[v] = true;
            connectedVertices.push_back(v);

            // Dodanie krawędzi
            int weight = rand() % 10 + 1;
            Edge *newEdgeU = new Edge(v, weight);
            Edge *newEdgeV = new Edge(u, weight);

            adjacencyList[u].addEdge(newEdgeU);
            adjacencyList[v].addEdge(newEdgeV);

            incidenceMatrix[u][edgeCount] = weight;
            incidenceMatrix[v][edgeCount] = -weight;
            edgeCount++;
        } else {
            // Losowe krawędzie
            int randomIndex = rand() % possibleEdges.size();
            int u = possibleEdges[randomIndex].first;
            int v = possibleEdges[randomIndex].second;
            std::swap(possibleEdges[randomIndex], possibleEdges.back());
            possibleEdges.pop_back();

            if (adjacencyList[u].findEdge(v) == nullptr) {
                int weight = rand() % 10 + 1;
                Edge *newEdgeU = new Edge(v, weight);
                Edge *newEdgeV = new Edge(u, weight);

                adjacencyList[u].addEdge(newEdgeU);
                adjacencyList[v].addEdge(newEdgeV);

                incidenceMatrix[u][edgeCount] = weight;
                incidenceMatrix[v][edgeCount] = -weight;
                edgeCount++;
            }
        }
    }
}


void Graph::setIncidenceMatrix(int **matrix) {
    incidenceMatrix = matrix;
}

void Graph::setEdges(int e) {
    edges = e;
}
