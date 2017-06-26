#include "szomszedsagi_matrix.h"
#include "memtrace.h"

void SzomszedsagiMatrix::el_beallit(int a, int b)
{
    --a;--b;
    tomb[a] = tomb[a] | (1 << b);         ///a. szám b. bitjének beállítása
    tomb[b] = tomb[b] | (1 << a);         ///b. szám a. bitjének beállítása
}

void SzomszedsagiMatrix::nemel_beallit(int a, int b)
{
    --a;--b;
    tomb[a] = tomb[a] ^ (1 << b);       ///a. szám b. bitjének beállítása
    tomb[b] = tomb[b] ^ (1 << a);       ///b. szám a. bitjének beállítása
}

bool SzomszedsagiMatrix::el_get(int a, int b)const
{
    --a;--b;
    return (tomb[a] | (1 << b)) == tomb[a];
}

SzomszedsagiMatrix::SzomszedsagiMatrix(const SzomszedsagiMatrix& rhs):tomb(new int[24])
{
    for(int i = 0; i < 24; i++)
        for(int j = 0; j < 24; j++)
            if(i != j)
                if(rhs.el_get(i+1, j+1))
                    el_beallit(i+1, j+1);
}

SzomszedsagiMatrix& SzomszedsagiMatrix::operator=(const SzomszedsagiMatrix& rhs)
{
    if(this != &rhs)
    {
        delete[] tomb;
        SzomszedsagiMatrix(rhs);
    }
    return *this;
}
