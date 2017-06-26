#include "jatekos.h"
#include "memtrace.h"

int Jatekos::rak(const Tomb& t, std::ostream& os, std::istream& is)
{
    korong_lent--;
    korong_tablan++;
    os << "Adja meg a korong koordinatait: ";
    return beolvas(t, os, is);
}

void Jatekos::levesz(std::ostream& os, std::istream& is)
{
    korong_tablan--;
    os << "Adja meg a korong koordinatait: ";
    torol(os, is);
}

int Jatekos::lep(const Tomb& t, std::ostream& os, std::istream& is)
{
    os << "Adja meg a korong koordinatait: ";
    int temp = torol(os, is);                             ///elt�roljuk, hogy honnan t�r�lt�nk
    os << "Adja meg a hely koordinatait: ";
    int ujhely;
    if(korong_tablan == 3)                          ///ha a j�t�kosnak csak 3 korongja van, b�rhov� l�phet
        ujhely = beolvas(t, os, is);
    else
        while(!tabla.el_get(temp+1, (ujhely = beolvas(t, os, is))+1))   ///egy�bk�nt meg kell vizsg�lni, hogy k�zt�nk �s ahov� l�pni szeretn�nk van-e �l
        {
            os << "Ide nem lephet!" << std::endl;
            os << "Probalkozzon ujra: " << std::endl;
            torol(ujhely);                                      ///ha nincs ki kell t�r�lni a beolvasott korongot
        }
    return ujhely;  ///vissza kell t�rni a korong �j hely�vel
}

