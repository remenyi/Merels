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
    bool malom(const SzomszedsagiMatrix& mtx, int hely);            ///igaz, ha van a param�terben megadott m�trixban korong, a param�terben megadott koronggal
    void rajzol(const Tomb& feher_tomb, const Tomb& fekete_tomb, std::ostream& = std::cout);   ///kirajzolja a k�t param�terben kapott korong t�mb�t
};

#endif // TABLA_H_INCLUDED
