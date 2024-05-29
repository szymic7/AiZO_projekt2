
#ifndef AIZO_PROJEKT2_BELLMANFORD_H
#define AIZO_PROJEKT2_BELLMANFORD_H

#include "../graphs/graph.h"
#include "algorithm.h"

class BellmanFord : public Algorithm {

    int start, end; // wierzcholek startowy i koncowy
    List pathList, pathMatrix; // listy krawedzi najkrotszej sciezki dla reprezentacji listowej i macierzowej grafu
    int pathWeightList, pathWeightMatrix; // calkowity koszt sciezki dla reprezentacji listowej i macierzowej grafu
    int *d, *p; // tablice sledzace odleglosc wierzcholkow od wierzcholka startowego i poprzednikow wierzcholkow

public:

    BellmanFord();          // kontruktor
    void setStart(int s);   // ustawienie wierzcholka startowego algorytmu
    void setEnd(int e);     // ustawienie wierzcholka koncowego algorytmu
    void algorithmList();   // algorytm dla reprezentacji grafu w formie listy sasiadow
    void algorithmMatrix(); // algorytm dla reprezentacji grafu w formie macierzy incydencji
    void showPathList();    // wyswietlenie wynikow algorytmu dla reprezntacji listowej grafu
    void showPathMatrix();  // wyswietlenie wynikow algorytmu dla reprezentacji macierzowej grafu

};

#endif //AIZO_PROJEKT2_BELLMANFORD_H
