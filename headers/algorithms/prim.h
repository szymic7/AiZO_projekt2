
#ifndef AIZO_PROJEKT2_PRIM_H
#define AIZO_PROJEKT2_PRIM_H

#include "algorithm.h"

class Prim : public Algorithm {

    int start;
    List mstList, mstMatrix;
    int mstWeightList, mstWeightMatrix;

public:

    Prim();
    void algorithmList();
    void algorithmMatrix();
    void showMstList();
    void showMstMatrix();

};

#endif //AIZO_PROJEKT2_PRIM_H
