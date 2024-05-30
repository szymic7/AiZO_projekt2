#include <limits>
#include "../../headers/algorithms/bellmanFord.h"

BellmanFord::BellmanFord() : Algorithm() {
    start = -1;
    end = -1;
    pathList = nullptr;
    pathWeightList = -1;
    pathMatrix = nullptr;
    pathWeightMatrix = -1;
    d = nullptr;
    p = nullptr;
}


void BellmanFord::setStart(int s) {
    start = s;
}


void BellmanFord::setEnd(int e) {
    end = e;
}


void BellmanFord::algorithmList() {

    // Wyczyszczenie istniejacej listy krawedzi najkrotszej sciezki i tablic d oraz p
    pathList.clear();
    delete[] d;
    delete[] p;

    // Liczba wierzcholkow grafu - rozmiar tablic d i p
    int V = getGraph()->getVertices();

    d = new int[V];
    p = new int[V];

    for (int i = 0; i < V; i++) {
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
    }
    d[start] = 0;

    int relaxation_count = 0;

    for (int i = 1; i < V; i++) { // V-1 relaksacji

        for (int u = 0; u < V; u++) {   // lista dla kazdego wierzcholka

            for (Edge *edge = getGraph()->getAdjacencyList()[u].getFirstEdge(); edge != nullptr; edge = edge->getNext()) {

                int v = edge->getEnd();
                int weight = edge->getWeight();

                // Relaksacja krawedzi
                if (d[u] != std::numeric_limits<int>::max() && d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    p[v] = u;
                    relaxation_count++; // zliczamy dokonane relaksacje
                }

            }

        }

        // Sprawdzenie czy dokonano jakiejs relaksacji; jesli nie, to mozemy zakonczyc algorytm
        if(relaxation_count == 0) break;
        relaxation_count = 0;

    }

    // Sprawdzenie na obecność cykli o ujemnej wadze
    // Nie jest to potrzebne, bo jest zalozenie, ze wagi tylko dodatnie
    /*for (int u = 0; u < V; u++) {   // lista dla kazdego wierzcholka

        for (Edge *edge = getGraph()->getAdjacencyList()[u].getFirstEdge(); edge != nullptr; edge = edge->getNext()) {

            int v = edge->getEnd();
            int weight = edge->getWeight();

            if (d[u] != std::numeric_limits<int>::max() && d[v] > d[u] + weight) {
                std::cerr << "Graf zawiera cykl o ujemnej wadze" << std::endl;
                return;
            }
        }
    }*/

    // Ustawienie całkowitego kosztu ścieżki
    pathWeightList = d[end];

    // Zapisanie krawędzi ścieżki do listy pathList
    for (int at = end; at != start; at = p[at]) {
        if (p[at] != -1) {
            Edge *newEdge = new Edge(at, d[at] - d[p[at]]);
            pathList.addEdgeFront(newEdge);
        }
    }

}


void BellmanFord::algorithmMatrix() {

    // Wyczyszczenie istniejacej listy krawedzi najkrotszej sciezki i tablic d oraz p
    pathMatrix.clear();
    delete[] d;
    delete[] p;

    // Liczba wierzcholkow grafu - rozmiar tablic d i p
    int V = getGraph()->getVertices();

    d = new int[V];
    p = new int[V];

    // Liczba krawedzi
    int E = getGraph()->getEdges();

    for (int i = 0; i < V; i++) {
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
    }
    d[start] = 0;

    int weight, u, v;
    int relaxation_count = 0;

    for (int i = 1; i < V; i++) { // V-1 relaksacji

        for (int j = 0; j < E; j++) {   // E krawedzi = E kolumn macierzy; j = indeks kolumny

            // Ustawienie wartosci domyslnych u i v przed szukaniem krawedzi
            u = -1;
            v = -1;

            for(int k = 0; k < V; k++) {    // szukamy u i v w j-tej kolumnie; k = indeks wiersza

                if(getGraph()->getIncidenceMatrix()[k][j] > 0) {    // u - poczatek krawedzi

                    u = k;
                    weight = getGraph()->getIncidenceMatrix()[k][j];
                    if(v != -1) break;  // jesli v juz znalezione => break

                } else if(getGraph()->getIncidenceMatrix()[k][j] < 0) { // v - koniec krawedzi

                    v = k;
                    if(u != -1) break;  // jesli u juz znalezione => break

                }

            }

            // Relaksacja krawedzi
            if (d[u] != std::numeric_limits<int>::max() && d[u] + weight < d[v]) {
                d[v] = d[u] + weight;
                p[v] = u;
                relaxation_count++; // zliczamy dokonane relaksacje
            }

        }

        // Sprawdzenie czy dokonano jakiejs relaksacji; jesli nie, to mozemy zakonczyc algorytm
        if(relaxation_count == 0) break;
        relaxation_count = 0;

    }

    // Sprawdzenie na obecnosc cykli o ujemnej wadze
    // Nie jest to potrzebne, bo jest zalozenie, ze wagi tylko dodatnie
    /*for (u = 0; u < V; u++) {   // lista dla kazdego wierzcholka

        for (Edge *edge = getGraph()->getAdjacencyList()[u].getFirstEdge(); edge != nullptr; edge = edge->getNext()) {

            v = edge->getEnd();
            weight = edge->getWeight();

            if (d[u] != std::numeric_limits<int>::max() && d[v] > d[u] + weight) {
                std::cerr << "Graf zawiera cykl o ujemnej wadze" << std::endl;
                return;
            }
        }
    }*/

    // Ustawienie całkowitego kosztu ścieżki
    pathWeightMatrix = d[end];

    // Zapisanie krawędzi ścieżki do listy pathList
    for (int at = end; at != start; at = p[at]) {
        if (p[at] != -1) {
            Edge *newEdge = new Edge(at, d[at] - d[p[at]]);
            pathMatrix.addEdgeFront(newEdge);
        }
    }

}


void BellmanFord::showPathList() {

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


void BellmanFord::showPathMatrix() {

    if(pathMatrix.getFirstEdge() != nullptr) { // jesli najkrotsza sciezka nie jest pusta

        Edge *current = pathMatrix.getFirstEdge();

        cout << "Znaleziona najktorsza sciezka dla reprezentacji macierzowej:" << endl;

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
