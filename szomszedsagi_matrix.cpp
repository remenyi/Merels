#include "szomszedsagi_matrix.h"
#include "memtrace.h"

void SzomszedsagiMatrix::el_beallit(int a, int b)
{
    --a;--b;
    tomb[a] = tomb[a] | (1 << b);         ///a. sz�m b. bitj�nek be�ll�t�sa
    tomb[b] = tomb[b] | (1 << a);         ///b. sz�m a. bitj�nek be�ll�t�sa
}

void SzomszedsagiMatrix::nemel_beallit(int a, int b)
{
    --a;--b;
    tomb[a] = tomb[a] ^ (1 << b);       ///a. sz�m b. bitj�nek be�ll�t�sa
    tomb[b] = tomb[b] ^ (1 << a);       ///b. sz�m a. bitj�nek be�ll�t�sa
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
