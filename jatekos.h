#ifndef JATEKOS_H_INCLUDED
#define JATEKOS_H_INCLUDED

#include "tarolo.h"
#include <iostream>
#include "memtrace.h"

class Jatekos: public Tarolo
{
    int korong_lent;        ///hány korong van még lent, amit nem raktak föl a táblára
    int korong_tablan;      ///hány korong van a táblán
public:
    Jatekos():korong_lent(9), korong_tablan(0){}
    bool rakas_vege(){return korong_lent <= 0;}     ///igaz, ha nem tud a játékos több korongot a táblára helyezni
    bool jatek_vege(){return korong_tablan >= 2;}   ///igaz, ha a játékosnak csak két korongja van a táblán, azaz veszített
    int rak(const Tomb&, std::ostream& = std::cout, std::istream& = std::cin);                           ///lerak egy korongot, visszatér annak számával, a paraméterben átvett korongok helyére nem rakhat
    void levesz(std::ostream&, std::istream&);                                  ///levesz egy korongot
    int lep(const Tomb&, std::ostream& = std::cout, std::istream& = std::cin);                           ///lép egy koronggal, visszatér az új hely számával, a paraméterben átvett korongok helyére nem léphet
};


#endif // JATEKOS_H_INCLUDED
