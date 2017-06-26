#ifndef TAROLO_H_INCLUDED
#define TAROLO_H_INCLUDED

#include "szomszedsagi_matrix.h"
#include "tomb.h"
#include <iostream>
#include "memtrace.h"

class Tarolo
{
    Tomb korongok;              ///korongokat tároló tömb
    SzomszedsagiMatrix mtx;     ///szomszédsági mátrixot tároló
public:
    static SzomszedsagiMatrix tabla;    ///korong táblájának szomszédsági mátrixa
    Tarolo();
    int beolvas(const Tomb&, std::ostream& = std::cout, std::istream& = std::cin);           ///lerak egy korongot, vissaztér annak számával, a paraméterben átvett korongok helyére nem rakhat
    int torol(std::ostream& = std::cout, std::istream& = std::cin);                        ///levesz egy korongot, visszatér annak számával
    void torol(int);                    ///leveszi a paraméterben megadott korongot
    const Tomb& getTomb()const{return korongok;}
    const SzomszedsagiMatrix& getMtx()const{return mtx;}

private:
    int string_to_korong(const std::string&, std::ostream& = std::cout);   ///felhasználó által megadott koordianátákat konvertálja 0 és 23 közé esõ korongokká
    void szomszedsag_beallit(int);              ///szomszédsági mátrixban beállítja a paraméterként megadott korong éleit
    void nemszomszedsag_beallit(int);           ///szomszédsági mátrixban törli a paraméterként megadott korong éleit
};

#endif // TAROLO_H_INCLUDED
