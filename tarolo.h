#ifndef TAROLO_H_INCLUDED
#define TAROLO_H_INCLUDED

#include "szomszedsagi_matrix.h"
#include "tomb.h"
#include <iostream>
#include "memtrace.h"

class Tarolo
{
    Tomb korongok;              ///korongokat t�rol� t�mb
    SzomszedsagiMatrix mtx;     ///szomsz�ds�gi m�trixot t�rol�
public:
    static SzomszedsagiMatrix tabla;    ///korong t�bl�j�nak szomsz�ds�gi m�trixa
    Tarolo();
    int beolvas(const Tomb&, std::ostream& = std::cout, std::istream& = std::cin);           ///lerak egy korongot, vissazt�r annak sz�m�val, a param�terben �tvett korongok hely�re nem rakhat
    int torol(std::ostream& = std::cout, std::istream& = std::cin);                        ///levesz egy korongot, visszat�r annak sz�m�val
    void torol(int);                    ///leveszi a param�terben megadott korongot
    const Tomb& getTomb()const{return korongok;}
    const SzomszedsagiMatrix& getMtx()const{return mtx;}

private:
    int string_to_korong(const std::string&, std::ostream& = std::cout);   ///felhaszn�l� �ltal megadott koordian�t�kat konvert�lja 0 �s 23 k�z� es� korongokk�
    void szomszedsag_beallit(int);              ///szomsz�ds�gi m�trixban be�ll�tja a param�terk�nt megadott korong �leit
    void nemszomszedsag_beallit(int);           ///szomsz�ds�gi m�trixban t�rli a param�terk�nt megadott korong �leit
};

#endif // TAROLO_H_INCLUDED
