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
    adjacencyList = nullptr;
    incidenceMatrix = nullptr;
    /*adjacencyList = new List[vertices];
    incidenceMatrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        incidenceMatrix[i] = nullptr;
    }*/
}

void Graph::loadGraph(string txt) {
    // Wczytanie grafu z pliku .txt
}

void Graph::generateGraph(bool directed) {
    if (vertices <= 0) return;

    // Inicjalizacja generatora liczb losowych
    srand(time(0));

    // Obliczenie maksymalnej liczby krawędzi dla grafu skierowanego V*(V-1) i nieskierowanego: V*(V-1)/2
    int maxEdges = directed ? vertices * (vertices - 1) : vertices * (vertices - 1) / 2;

    // Obliczenie liczby krawedzi dla podanej gestosci
    edges = maxEdges * density / 100;

    // Obliczenie minimalnej liczby krawedzi do utworzenia grafu spojnego skierowanego: V i nieskierowanwgo: V-1
    int minEdges = directed ? vertices : vertices - 1;

    // Sprawdzenie, czy liczba krawedzi jest wystarczajaca do spojności
    if (edges < minEdges) {
        cout << endl << "Dla podanej gestosci i liczby wierzcholkow nie mozna utworzyc spojnego grafu.";
        cout << "\nGraf nie zostal utworzony. Sprobuj ponownie dla innych wartosci parametrow." << endl;
        edges = 0;
        return;
    }

    // Usunięcie istniejącej macierzy incydencji (zapewnienie braku wycieków pamięci)
    if(incidenceMatrix != nullptr) {
        for (int i = 0; i < vertices; ++i) {
            delete[] incidenceMatrix[i];
        }
        delete[] incidenceMatrix;
    }

    // Inicjalizacja macierzy incydencji
    incidenceMatrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        incidenceMatrix[i] = new int[edges];
        std::fill(incidenceMatrix[i], incidenceMatrix[i] + edges, 0);
    }

    // Usunięcie istniejącej listy sąsiadów (zapewnienie braku wycieków pamięci)
    if (adjacencyList != nullptr) {
        clearAdjacencyList();
    }

    // Inicjalizacja nowej listy sąsiadów
    adjacencyList = new List[vertices];

    // Lista możliwych krawędzi
    std::vector<std::pair<int, int>> possibleEdges;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (!directed && j > i) {   // graf nieskierowany
                possibleEdges.emplace_back(i, j);
            } else if (directed && i != j) {   // graf skierowany
                possibleEdges.emplace_back(i, j);
            }
        }
    }

    // Utrzymanie spójności grafu
    std::vector<bool> connected(vertices, false);
    std::vector<int> connectedVertices;
    connectedVertices.push_back(0);
    connected[0] = true;

    int edgeCount = 0;

    // Dodawanie krawędzi w celu zapewnienia spójności
    while (edgeCount < minEdges) {
        int u = connectedVertices[rand() % connectedVertices.size()];
        int v = rand() % vertices;
        while (connected[v]) {
            v = rand() % vertices;
        }
        connected[v] = true;
        connectedVertices.push_back(v);

        // Dodanie krawędzi
        int weight = rand() % 20 + 1;
        Edge *newEdgeU = new Edge(v, weight);
        adjacencyList[u].addEdge(newEdgeU);

        if (!directed) {    // graf nieskierowany
            Edge *newEdgeV = new Edge(u, weight);
            adjacencyList[v].addEdge(newEdgeV);
        }

        incidenceMatrix[u][edgeCount] = weight;
        if (directed) {
            incidenceMatrix[v][edgeCount] = -weight; // graf skierowany
        } else {
            incidenceMatrix[v][edgeCount] = weight;  // graf nieskierowany
        }
        edgeCount++;
    }

    // Dodawanie losowych krawędzi do osiągnięcia docelowej liczby krawędzi
    while (edgeCount < edges && !possibleEdges.empty()) {
        int randomIndex = rand() % possibleEdges.size();
        int u = possibleEdges[randomIndex].first;
        int v = possibleEdges[randomIndex].second;
        std::swap(possibleEdges[randomIndex], possibleEdges.back());
        possibleEdges.pop_back();

        if (adjacencyList[u].findEdge(v) == nullptr) {
            int weight = rand() % 20 + 1;
            Edge *newEdgeU = new Edge(v, weight);
            adjacencyList[u].addEdge(newEdgeU);

            if (!directed) {
                Edge *newEdgeV = new Edge(u, weight);
                adjacencyList[v].addEdge(newEdgeV);
            }

            incidenceMatrix[u][edgeCount] = weight;
            if (directed) {
                incidenceMatrix[v][edgeCount] = -weight; // graf skierowany
            } else {
                incidenceMatrix[v][edgeCount] = weight;  // graf nieskierowany
            }
            edgeCount++;
        }
    }

    cout << endl << "Graf zostal pomyslnie utworzony." << endl;
}

    /*while (edgeCount < edges) {
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
            int weight = rand() % 20 + 1;
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
                int weight = rand() % 20 + 1;
                Edge *newEdgeU = new Edge(v, weight);
                Edge *newEdgeV = new Edge(u, weight);

                adjacencyList[u].addEdge(newEdgeU);
                adjacencyList[v].addEdge(newEdgeV);

                incidenceMatrix[u][edgeCount] = weight;
                incidenceMatrix[v][edgeCount] = -weight;
                edgeCount++;
            }
        }
    }*/
//}


List *Graph::getAdjacencyList() {
    return adjacencyList;
}


int **Graph::getIncidenceMatrix() {
    return incidenceMatrix;
}


void Graph::clearAdjacencyList() {
    for (int i = 0; i < vertices; ++i) {
        adjacencyList[i].clear();
    }
    delete[] adjacencyList;
}


void Graph::showAdjacencyList() {
    cout << endl << "Lista sasiadow:\n" << endl;
    for(int i = 0; i < vertices; i++) {
        cout << i << ":";
        if(i < 10) cout << " ";
        adjacencyList[i].printList();
        cout << endl;
    }
}


void Graph::showIncidenceMatrix() {

    cout << endl << "Macierz incydencji:\n" << endl;

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







void Graph::setIncidenceMatrix(int **matrix) {
    incidenceMatrix = matrix;
}

void Graph::setEdges(int e) {
    edges = e;
}
