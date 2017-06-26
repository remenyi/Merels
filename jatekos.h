#ifndef JATEKOS_H_INCLUDED
#define JATEKOS_H_INCLUDED

#include "tarolo.h"
#include <iostream>
#include "memtrace.h"

class Jatekos: public Tarolo
{
    int korong_lent;        ///h�ny korong van m�g lent, amit nem raktak f�l a t�bl�ra
    int korong_tablan;      ///h�ny korong van a t�bl�n
public:
    Jatekos():korong_lent(9), korong_tablan(0){}
    bool rakas_vege(){return korong_lent <= 0;}     ///igaz, ha nem tud a j�t�kos t�bb korongot a t�bl�ra helyezni
    bool jatek_vege(){return korong_tablan >= 2;}   ///igaz, ha a j�t�kosnak csak k�t korongja van a t�bl�n, azaz vesz�tett
    int rak(const Tomb&, std::ostream& = std::cout, std::istream& = std::cin);                           ///lerak egy korongot, visszat�r annak sz�m�val, a param�terben �tvett korongok hely�re nem rakhat
    void levesz(std::ostream&, std::istream&);                                  ///levesz egy korongot
    int lep(const Tomb&, std::ostream& = std::cout, std::istream& = std::cin);                           ///l�p egy koronggal, visszat�r az �j hely sz�m�val, a param�terben �tvett korongok hely�re nem l�phet
};


#endif // JATEKOS_H_INCLUDED
