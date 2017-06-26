#ifndef SZOMSZEDSAGI_MATRIX_H_INCLUDED
#define SZOMSZEDSAGI_MATRIX_H_INCLUDED

#include <iostream>
#include "memtrace.h"

class SzomszedsagiMatrix
{
    int* tomb;
public:
    SzomszedsagiMatrix():tomb(new int[24]){for(int i = 0; i < 24; i++)tomb[i] = 0;} ///0-al feltöltjük
    SzomszedsagiMatrix(const SzomszedsagiMatrix&);
    SzomszedsagiMatrix& operator=(const SzomszedsagiMatrix&);
    void el_beallit(int, int);                                                      ///a paraméterként megadott korongok között élt állít be
    void nemel_beallit(int, int);                                                   ///a paraméterként megadott korongok között megszünteti az élt
    bool el_get(int, int)const;                                                     ///igaz, ha a paraméterként megadott korongok között van él
    ~SzomszedsagiMatrix(){delete[] tomb;}
};

#endif // SZOMSZEDSAGI_MATRIX_H_INCLUDED
