#ifndef TABLA_H_INCLUDED
#define TABLA_H_INCLUDED

#include "szomszedsagi_matrix.h"
#include "tomb.h"
#include <iostream>
#include <stdlib.h>
#include "memtrace.h"

class Tabla
{
public:
    bool malom(const SzomszedsagiMatrix& mtx, int hely);            ///igaz, ha van a paraméterben megadott mátrixban korong, a paramáterben megadott koronggal
    void rajzol(const Tomb& feher_tomb, const Tomb& fekete_tomb, std::ostream& = std::cout);   ///kirajzolja a két paraméterben kapott korong tömböt
};

#endif // TABLA_H_INCLUDED
