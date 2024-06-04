#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include "../../headers/graphs/graph.h"

using namespace std;

Graph::Graph(int v, int d) {
    vertices = v;
    density = d;
    edges = 0;
    adjacencyList = nullptr;
    incidenceMatrix = nullptr;
}


void Graph::setVertices(int v) {
    vertices = v;
}


void Graph::setDensity(int d) {
    density = d;
}


void Graph::loadGraph(string txt, bool directed) {
    ifstream file(txt);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << txt << endl;
        return;
    }

    // Zczytanie liczby krawedzi i wierzcholkow z pierwszej linijki pliku tekstowego
    file >> edges >> vertices;

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


    // Usuniecie istniejacej listy sasiadow
    if (adjacencyList != nullptr) {
        clearAdjacencyList();
    }

    // Inicjalizacja nowej listy sąsiadów
    adjacencyList = new List[vertices];

    // Zczytanie krawedzi z kolejnych linijek pliku tekstowego
    int start, end, weight;
    for (int i = 0; i < edges; ++i) {
        file >> start >> end >> weight;

        adjacencyList[start].addEdge(new Edge(end, weight));
        incidenceMatrix[start][i] = weight;

        if (!directed) {    // graf nieskierowany
            adjacencyList[end].addEdge(new Edge(start, weight));
            incidenceMatrix[end][i] = weight;
        } else {    // graf skierowany
            incidenceMatrix[end][i] = -weight;
        }
    }

    file.close();

    cout << endl << "Graf zostal prawidlowo wczytany." << endl;

}



void Graph::generateGraph(bool directed, std::default_random_engine& rng) {
    if (vertices <= 0) return;

    // Obliczenie maksymalnej liczby krawędzi dla grafu skierowanego V*(V-1) i nieskierowanego: V*(V-1)/2
    int maxEdges = directed ? vertices * (vertices - 1) : vertices * (vertices - 1) / 2;

    // Obliczenie liczby krawedzi dla podanej gestosci
    edges = maxEdges * density / 100;

    // Obliczenie minimalnej liczby krawedzi do utworzenia grafu spojnego skierowanego: V i nieskierowanwgo: V-1
    int minEdges = directed ? vertices : vertices - 1;

    // Sprawdzenie, czy liczba krawedzi jest wystarczajaca do spojności
    if (edges < minEdges) {
        cout << endl << "Dla podanej gestosci i liczby wierzcholkow nie mozna utworzyc spojnego grafu." << endl;
        cout << "Graf nie zostal utworzony. Sprobuj ponownie dla innych wartosci parametrow." << endl;
        edges = 0;
        return;
    }

    // Usuniecie istniejacej macierzy incydencji
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

    // Usuniecie istniejacej listy sasiadow
    if (adjacencyList != nullptr) {
        clearAdjacencyList();
    }

    // Inicjalizacja nowej listy sasiadow
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

    int edgeCount = 0;

    if(directed) {  // graf skierowany

        // Utworzenie wektora z losowa kolejnoscia wierzcholkow w cyklu - dla zapewnienia spojnosci grafu skierowanego
        std::vector<int> randomOrder(vertices);
        for (int i = 0; i < vertices; ++i) {
            randomOrder[i] = i;
        }
        std::shuffle(randomOrder.begin(), randomOrder.end(), rng);

        // Utworzenie cyklu zawierajacego wszystkie wierzcholki w celu zapewnienia spojnosci
        for (int i = 0; i < vertices; ++i) {
            int u = randomOrder[i];
            int v = randomOrder[(i + 1) % vertices];

            // Dodanie krawędzi
            int weight = rng() % 20 + 1;
            Edge *newEdgeU = new Edge(v, weight);
            adjacencyList[u].addEdge(newEdgeU);

            incidenceMatrix[u][edgeCount] = weight;
            incidenceMatrix[v][edgeCount] = -weight; // graf skierowany

            edgeCount++;

            // Usun dodana krawedz z listy mozliwych krawedzi
            possibleEdges.erase(std::remove(possibleEdges.begin(), possibleEdges.end(), std::make_pair(u, v)), possibleEdges.end());
        }

    } else {    // graf nieskierowany

        // Utrzymanie spójności grafu
        std::vector<bool> connected(vertices, false);
        std::vector<int> connectedVertices;

        // Losujemy wierzcholek, od ktorego zaczniemy generowanie grafu
        int firstVertice = rng() % vertices;
        connectedVertices.push_back(firstVertice);
        connected[firstVertice] = true;

        // Dodawanie krawedzi w celu zapewnienia spojnosci
        while (edgeCount < minEdges) {
            int u = connectedVertices[rng() % connectedVertices.size()];    // losowy juz polaczony wierzcholek
            int v = rng() % vertices;
            while (connected[v]) {  // jesli wylosowane v jest juz polaczone
                v = rng() % vertices;   // losujemy v ponownie (dopoki nie bedzie wierzcholkiem nie polaczonym)
            }
            connected[v] = true;
            connectedVertices.push_back(v);

            // Dodanie krawedzi
            int weight = rng() % 20 + 1;
            Edge *newEdgeU = new Edge(v, weight);
            adjacencyList[u].addEdge(newEdgeU);

            Edge *newEdgeV = new Edge(u, weight);
            adjacencyList[v].addEdge(newEdgeV);

            incidenceMatrix[u][edgeCount] = weight;
            incidenceMatrix[v][edgeCount] = weight;  // graf nieskierowany

            edgeCount++;

            // Usun dodana krawedz z listy mozliwych krawedzi
            possibleEdges.erase(std::remove(possibleEdges.begin(), possibleEdges.end(), std::make_pair(u, v)), possibleEdges.end());
        }

    }


    // Dodawanie losowych krawedzi do osiągniecia docelowej liczby krawedzi
    while (edgeCount < edges && !possibleEdges.empty()) {

        int randomIndex = rng() % possibleEdges.size(); // losujemy krawedz z mozliwych do dodania
        int u = possibleEdges[randomIndex].first;
        int v = possibleEdges[randomIndex].second;
        std::swap(possibleEdges[randomIndex], possibleEdges.back());
        possibleEdges.pop_back();   // usuniecie wylosowanej krawedzi z possibleEdges

        if (adjacencyList[u].findEdge(v) == nullptr) {  // jesli nie istnieje krawedz z u do v
            int weight = rng() % 20 + 1;
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

    }

    cout << endl << "Graf zostal pomyslnie utworzony." << endl;

}




int Graph::getVertices() {
    return vertices;
}


int Graph::getEdges() {
    return edges;
}


List *Graph::getAdjacencyList() {
    return adjacencyList;
}


int **Graph::getIncidenceMatrix() {
    return incidenceMatrix;
}


void Graph::clearAdjacencyList() {
    for(int i = 0; i < vertices; ++i) {
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
