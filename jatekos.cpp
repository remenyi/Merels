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
    int temp = torol(os, is);                             ///eltároljuk, hogy honnan töröltünk
    os << "Adja meg a hely koordinatait: ";
    int ujhely;
    if(korong_tablan == 3)                          ///ha a játékosnak csak 3 korongja van, bárhová léphet
        ujhely = beolvas(t, os, is);
    else
        while(!tabla.el_get(temp+1, (ujhely = beolvas(t, os, is))+1))   ///egyébként meg kell vizsgálni, hogy köztünk és ahová lépni szeretnénk van-e él
        {
            os << "Ide nem lephet!" << std::endl;
            os << "Probalkozzon ujra: " << std::endl;
            torol(ujhely);                                      ///ha nincs ki kell törölni a beolvasott korongot
        }
    return ujhely;  ///vissza kell térni a korong új helyével
}

