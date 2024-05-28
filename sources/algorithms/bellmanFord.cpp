#include "../../headers/algorithms/bellmanFord.h"

BellmanFord::BellmanFord() : Algorithm() {
    start = -1;
    end = -1;
    pathList = nullptr;
    pathWeightList = -1;
    pathMatrix = nullptr;
    pathWeightMatrix = -1;
}

void BellmanFord::setStart(int s) {
    start = s;
}


void BellmanFord::setEnd(int e) {
    end = e;
}


void BellmanFord::algorithmList() {



}


void BellmanFord::algorithmMatrix() {



}


void BellmanFord::showPathList() {

    if(pathList.getFirstEdge() != nullptr) { // jesli najkrotsza sciezka nie jest pusta

        Edge *current = pathList.getFirstEdge();

        cout << "Znaleziona najktorsza sciezka dla reprezentacji listowej:" << endl;

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