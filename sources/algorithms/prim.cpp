#include "../../headers/algorithms/prim.h"

Prim::Prim() : Algorithm() {
    start = -1;
    mstList = nullptr;
    mstMatrix = nullptr;
    mstWeightList = -1;
    mstWeightMatrix = -1;
}


void Prim::algorithmList() {



}


void Prim::algorithmMatrix() {



}


void Prim::showMstList() {

    if(mstList.getFirstEdge() != nullptr) { // jesli MST nie jest puste

        Edge *current = mstList.getFirstEdge();

        cout << endl << "Minimalne drzewo rozpinajace, znalezione dla reprezentacji listowej grafu:" << endl;

        // Wyswietlenie pierwszej krawedzi w formacie: (u-v: w)
        cout << "(" << start << "-" << current->getEnd() << ": " << current->getWeight() << ")" << endl;

        // Wyswietlenie kolejnych krawedzi
        while(current->getNext() != nullptr) {
            cout << "(" << current->getEnd() << "-";    // wierzch. startowy krawedzi = wierzcholek koncowy poprzedniej
            current = current->getNext();               // ustawienie aktualnej krawedzi
            cout << current->getEnd() << ": " << current->getWeight() << ")" << endl;
        }

        cout << endl << "Suma krawedzi drzewa MST = " << mstWeightList << endl;

    } else {    // jesli MST jest puste

        cout << endl << "Uruchom algorytm, aby znalezc minimalne drzewo rozpinajace." << endl;

    }

}


void Prim::showMstMatrix() {

    if(mstMatrix.getFirstEdge() != nullptr) { // jesli MST nie jest puste

        Edge *current = mstMatrix.getFirstEdge();

        cout << endl << "Minimalne drzewo rozpinajace, znalezione dla reprezentacji macierzowej grafu:" << endl;

        // Wyswietlenie pierwszej krawedzi w formacie: (u-v: w)
        cout << "(" << start << "-" << current->getEnd() << ": " << current->getWeight() << ")" << endl;

        // Wyswietlenie kolejnych krawedzi
        while(current->getNext() != nullptr) {
            cout << "(" << current->getEnd() << "-";    // wierzch. startowy krawedzi = wierzcholek koncowy poprzedniej
            current = current->getNext();               // ustawienie aktualnej krawedzi
            cout << current->getEnd() << ": " << current->getWeight() << ")" << endl;
        }

        cout << endl << "Suma krawedzi drzewa MST = " << mstWeightMatrix << endl;

    } else {    // jesli MST jest puste

        cout << endl << "Uruchom algorytm, aby znalezc minimalne drzewo rozpinajace." << endl;

    }

}
