
#ifndef AIZO_PROJEKT2_PRIM_H
#define AIZO_PROJEKT2_PRIM_H

#include "algorithm.h"

class Prim : public Algorithm {

    int start;
    List mstList, mstMatrix;
    int mstWeightList, mstWeightMatrix;
    int *p;

public:

    Prim();                 // konstruktor
    void setStart(int s);   // ustawienie wierzcholka startowego algorytmu
    void algorithmList();   // algorytm dla reprezentacji grafu w formie listy sasiadow
    void algorithmMatrix(); // algorytm dla reprezentacji grafu w formie macierzy incydencji
    void showMstList();     // wyswietlenie wynikow algorytmu dla reprezntacji listowej grafu
    void showMstMatrix();   // wyswietlenie wynikow algorytmu dla reprezntacji macierzowej grafu

};

#endif //AIZO_PROJEKT2_PRIM_H
