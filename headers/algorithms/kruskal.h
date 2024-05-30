
#ifndef AIZO_PROJEKT2_KRUSKAL_H
#define AIZO_PROJEKT2_KRUSKAL_H

#include "algorithm.h"
#include "../graphs/kruskal/listWithStart.h"
#include <vector>

class Kruskal : public Algorithm {

    ListWithStart mstList, mstMatrix;
    int mstWeightList, mstWeightMatrix;

    int findSet(int v, std::vector<int>& parent);
    void unionSets(int a, int b, std::vector<int>& parent, std::vector<int>& rank);

public:

    Kruskal();              // konstruktor
    void algorithmList();   // algorytm dla reprezentacji grafu w formie listy sasiadow
    void algorithmMatrix(); // algorytm dla reprezentacji grafu w formie macierzy incydencji
    void showMstList();     // wyswietlenie wynikow algorytmu dla reprezntacji listowej grafu
    void showMstMatrix();   // wyswietlenie wynikow algorytmu dla reprezntacji macierzowej grafu

};

#endif //AIZO_PROJEKT2_KRUSKAL_H
