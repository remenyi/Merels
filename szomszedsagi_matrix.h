#ifndef SZOMSZEDSAGI_MATRIX_H_INCLUDED
#define SZOMSZEDSAGI_MATRIX_H_INCLUDED

#include <iostream>
#include "memtrace.h"

class SzomszedsagiMatrix
{
    int* tomb;
public:
    SzomszedsagiMatrix():tomb(new int[24]){for(int i = 0; i < 24; i++)tomb[i] = 0;} ///0-al felt�ltj�k
    SzomszedsagiMatrix(const SzomszedsagiMatrix&);
    SzomszedsagiMatrix& operator=(const SzomszedsagiMatrix&);
    void el_beallit(int, int);                                                      ///a param�terk�nt megadott korongok k�z�tt �lt �ll�t be
    void nemel_beallit(int, int);                                                   ///a param�terk�nt megadott korongok k�z�tt megsz�nteti az �lt
    bool el_get(int, int)const;                                                     ///igaz, ha a param�terk�nt megadott korongok k�z�tt van �l
    ~SzomszedsagiMatrix(){delete[] tomb;}
};

#endif // SZOMSZEDSAGI_MATRIX_H_INCLUDED
