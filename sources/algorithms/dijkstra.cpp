#include "../../headers/algorithms/dijkstra.h"
#include <limits>
#include <queue>

Dijkstra::Dijkstra() : Algorithm() {
    start = -1;
    end = -1;
    pathList = nullptr;
    pathWeightList = -1;
    pathMatrix = nullptr;
    pathWeightMatrix = -1;
    d = nullptr;
    p = nullptr;
}


void Dijkstra::setStart(int s) {
    start = s;
}


void Dijkstra::setEnd(int e) {
    end = e;
}


void Dijkstra::algorithmList() {

    // Wyczyszczenie istniejacej listy krawedzi najkrotszej sciezki i tablic d oraz p
    pathList.clear();
    delete[] d;
    delete[] p;

    // Liczba wierzcholkow grafu - rozmiar tablic d i p
    int V = getGraph()->getVertices();

    d = new int[V];
    p = new int[V];
    bool *visited = new bool[V](); // tablica visited do oznaczania odwiedzonych wierzchołków

    for(int i = 0; i < V; i++) {
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
    }
    d[start] = 0;

    auto comp = [&](int left, int right) { return d[left] > d[right]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);

    pq.push(start);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (visited[u]) {
            continue; // jeśli wierzchołek był już przetwarzany, pomijamy go
        }

        visited[u] = true; // oznaczamy wierzchołek jako odwiedzony

        for (Edge *edge = getGraph()->getAdjacencyList()[u].getFirstEdge(); edge != nullptr; edge = edge->getNext()) {
            int v = edge->getEnd();
            int weight = edge->getWeight();

            if (d[u] + weight < d[v]) {
                d[v] = d[u] + weight;
                p[v] = u;
                pq.push(v);
            }
        }
    }

    // Ustawienie calkowitego kosztu sciezki
    pathWeightList = d[end];

    // Zapisanie krawedzi sciezki do listy pathList
    for (int at = end; at != start; at = p[at]) {   // dodajemy krawedzie zaczynajac od end i idac w strone start
        if (p[at] != -1) {
            Edge *newEdge = new Edge(at, d[at] - d[p[at]]);
            pathList.addEdgeFront(newEdge);
        }
    }

    delete[] visited;

}


void Dijkstra::algorithmMatrix() {

    // Wyczyszczenie istniejacej listy krawedzi najkrotszej sciezki i tablic d oraz p
    pathMatrix.clear();
    delete[] d;
    delete[] p;

    // Liczba wierzcholkow grafu - rozmiar tablic d i p
    int V = getGraph()->getVertices();

    d = new int[V];
    p = new int[V];
    bool *visited = new bool[V](); // tablica visited do oznaczania odwiedzonych wierzchołków

    for(int i = 0; i < V; i++) {
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
    }
    d[start] = 0;

    auto comp = [&](int left, int right) { return d[left] > d[right]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);

    pq.push(start);

    int weight, v;

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (visited[u]) {
            continue; // jeśli wierzchołek był już przetwarzany, pomijamy go
        }

        visited[u] = true; // oznaczamy wierzchołek jako odwiedzony

        for (int i = 0; i < getGraph()->getEdges(); ++i) {   // szukamy kolumny, odpowiadajacej krawedzi (u, v)

            // Sprawdzamy po kolei kazda krawedz, czy wychodzi z u
            weight = getGraph()->getIncidenceMatrix()[u][i];
            if (weight > 0) {   // gdy wartosc w macierzy jest dodatnia to krawedz wychodzi z u - szukamy v
                // i = indeks kolumny dla szukanej krawedzi

                // Szukamy wiersza, odpowiadajacego wierzcholkowi v
                for(int j = 0; j < V; j++) {
                    if(getGraph()->getIncidenceMatrix()[j][i] == -weight) {
                        v = j;
                        break;
                    }
                }

                // Relaksacja krawedzi
                if (d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    p[v] = u;
                    pq.push(v);
                }

            }

        }

    }

    // Ustawienie calkowitego kosztu sciezki
    pathWeightMatrix = d[end];

    // Zapisanie krawedzi sciezki do listy pathMatrix
    for (int at = end; at != start; at = p[at]) {   // dodajemy krawedzie zaczynajac od end i idac w strone start
        if (p[at] != -1) {
            Edge *newEdge = new Edge(at, d[at] - d[p[at]]);
            pathMatrix.addEdgeFront(newEdge);
        }
    }

    delete[] visited;

}


void Dijkstra::showPathList() {

    if(pathList.getFirstEdge() != nullptr) { // jesli najkrotsza sciezka nie jest pusta

        Edge *current = pathList.getFirstEdge();

        cout << endl << "Znaleziona najktorsza sciezka dla reprezentacji listowej:" << endl;

        // Wyswietlenie pierwszej krawedzi w formacie: (u-v: w)
        cout << "(" << start << "-" << current->getEnd() << ": " << current->getWeight() << ")" << endl;

        // Wyswietlenie kolejnych krawedzi
        while(current->getNext() != nullptr) {
            cout << "(" << current->getEnd() << "-";    // wierzch. startowy krawedzi = wierzcholek koncowy poprzedniej
            current = current->getNext();               // ustawienie aktualnej krawedzi
            cout << current->getEnd() << ": " << current->getWeight() << ")" << endl;
        }

        cout << endl << "Calkowity koszt sciezki = " << pathWeightList << endl;

    } else {    // jesli najkrotsza sciezka jest pusta

        cout << endl << "Uruchom algorytm, aby znalezc najkrotsza sciezke." << endl;

    }

}


void Dijkstra::showPathMatrix() {

    if(pathMatrix.getFirstEdge() != nullptr) { // jesli najkrotsza sciezka nie jest pusta

        Edge *current = pathMatrix.getFirstEdge();

        cout << endl << "Znaleziona najktorsza sciezka dla reprezentacji macierzowej:" << endl;

        // Wyswietlenie pierwszej krawedzi w formacie: (u-v: w)
        cout << "(" << start << "-" << current->getEnd() << ": " << current->getWeight() << ")" << endl;

        // Wyswietlenie kolejnych krawedzi
        while(current->getNext() != nullptr) {
            cout << "(" << current->getEnd() << "-";    // wierzch. startowy krawedzi = wierzcholek koncowy poprzedniej
            current = current->getNext();               // ustawienie aktualnej krawedzi
            cout << current->getEnd() << ": " << current->getWeight() << ")" << endl;
        }

        cout << endl << "Calkowity koszt sciezki = " << pathWeightMatrix << endl;

    } else {    // jesli najkrotsza sciezka jest pusta
        cout << endl << "Uruchom algorytm, aby znalezc najkrotsza sciezke." << endl;
    }

}
