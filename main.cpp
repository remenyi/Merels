#include <iostream>
#include <sstream>
#include "jatekos.h"
#include "tabla.h"
#include "tarolo.h"
#include "tomb.h"
#include "szomszedsagi_matrix.h"

///állapotgép állapotai
enum Allapot{feher_rak, fekete_rak, feher_malom, fekete_malom, feher_lep, fekete_lep, feher_veszit, fekete_veszit};

#define TESZT
#include "gtest_lite.h"

int main()
{
    #ifdef TESZT
    setbuf(stdout, 0);
    ///szomszédsági mátrix tesztelése
    SzomszedsagiMatrix mtx;
    mtx.el_beallit(6, 3);
    EXPECT_TRUE(mtx.el_get(6, 3)); ///6 és 3 között kell hogy legyen él
    EXPECT_TRUE(mtx.el_get(3, 6)); ///ahogy 6 és 3 között is
    mtx.nemel_beallit(3, 6);
    EXPECT_FALSE(mtx.el_get(6, 3)); ///6 és 3 között nem lehet él
    EXPECT_FALSE(mtx.el_get(3, 6)); ///ahogy 6 és 3 között sem

    ///tömb tesztelése
    Tomb tomb;
    tomb[6] = true;
    EXPECT_FALSE(tomb[3]);          ///false-ra lett inicializálva a tömb minden eleme
    EXPECT_TRUE(tomb[6]);           ///a hatodikat most állítottuk igazra
    Tomb tomb2 = tomb;
    EXPECT_TRUE(tomb[6]);           ///helyes volt a másoló konstruktor
    tomb2[2] = true;
    tomb = tomb2;
    EXPECT_TRUE(tomb[2]);           ///helyes volt az értékadó operátor

    ///tároló tesztelése
    Tarolo tarolo;
    Tomb tomb3;
    std::stringstream kimenet;
    try
    {
        std::cout << "Az input legyen 3ak: ";
        int temp_korong = tarolo.beolvas(tomb3, kimenet);   ///sajnos külön kell tárolni a függvények visszatérési értékeit, mert a gtest_lite valamiért kétsszer is meghívja
        std::string temp_sor;
        std::getline(kimenet, temp_sor);
        EXPECT_EQ("Tul hosszu a bemeno adat!", temp_sor);   ///először egy túl hosszú adat fog bejönni a bemenetről
        std::getline(kimenet, temp_sor);
        EXPECT_EQ("Probalkozzon ujra: ", temp_sor);         ///aztán egy üzenet, hogy próbálkozzunk újra
        EXPECT_EQ(22, temp_korong);                         ///3ak fog jönni a bemenetrõl, ami a 22. korong
        kimenet.clear();                                    ///lenullázuk a kimeneti streamet

        std::cout << "Az input legyen 2jf: ";
        temp_korong = tarolo.beolvas(tomb3, kimenet);
        std::getline(kimenet, temp_sor);
        EXPECT_EQ("Hibas elso koordinatat adott meg!", temp_sor);   ///először egy olyan koordináta fog bejönni, aminek az első koordinátája hibás
        EXPECT_EQ(5, temp_korong);                                  ///2jf fog jönni a bemenetrõl, ami az 5. korong
        kimenet.str("");                                            ///lenullázuk a kimeneti streamet

        std::cout << "Az input legyen 3ak: ";
        temp_korong = tarolo.torol(kimenet);
        std::getline(kimenet, temp_sor);
        EXPECT_EQ("Hibas masodik vagy harmadik koordinatat adott meg!", temp_sor);  ///először egy olyan koordináta fog jönni a standard bemenetről, aminek a második vagy harmadik koordinátája helytelenül lett megadva
        EXPECT_EQ(22, temp_korong);                                 ///most törlünk, 3ak fog jönni a bemenetről, ami a 22. korong
        kimenet.clear();
    }catch(int err)
    {
        std::cout << "Veget ert a file!" << std::endl;
        return 0;
    }

    ///Játékos tesztelése
    Jatekos jatekos;
    EXPECT_FALSE(jatekos.rakas_vege()); ///még nincs vége a rakosgatásnak
    EXPECT_FALSE(jatekos.jatek_vege()); ///még nincs vége a játéknak
    try
    {
        std::cout << "Az input legyen 3ak: ";
        int temp_korong = jatekos.rak(tomb3);
        EXPECT_EQ(22, temp_korong);                   ///most rakunk, 3ak fog jönni a bemenetrõl, ami a 22. korong

        std::cout << "Az input legyen 3ak, majd 3ja: ";
        temp_korong = jatekos.rak(tomb3);
        EXPECT_EQ(23, temp_korong);                   ///most lépünk, 3ak fog jönni a bemenetről, majd 3ja, ami a 23. korong

        for(int i = 0; i < 8; i++)
            jatekos.rak(tomb3);                       ///még lerakunk 8 korongot
        EXPECT_TRUE(jatekos.rakas_vege());            ///most már biztosan elfogyotak a korongok, amiket le tudtunk rakni
    }catch(int err)
    {
        std::cout << "Veget ert a file!" << std::endl;
        return 0;
    }

    ///tábla tersztelése
    Tabla tabla;
    EXPECT_EQ(false, tabla.malom(jatekos.getMtx(), 3));     ///üres szomszédsági mátrixban természetesen nincs korong
    EXPECT_EQ(true, tabla.malom(jatekos.getMtx(), 2));      ///most már kell hogy legyen malom
    std::stringstream ss;
    tabla.rajzol(jatekos.getTomb(), Tomb(), ss);
    EXPECT_EQ("\n0---------0---------1\n|         |         |\n|  0------0------1  |\n|  |      |      |  |\n|  |  0---0---1  |  |\n|  |  |       |  |  |\n0--0--0       1--1--1\n|  |  |       |  |  |\n|  |  0---1---0  |  |\n|  |      |      |  |\n|  0------1------0  |\n|         |         |\n0---------1---------1\n\n", ss.str());

    #endif // TESZT



    #ifndef TESZT
    ///két játékos és a tábla létrehozása
    Jatekos feher;
    Jatekos fekete;
    Tabla tabla;

    ///fehér játékos kezd
    Allapot allapot = feher_rak;
    std::cout << "Kezdjen a feher!" << std::endl;

    ///amíg tart a játék
    bool fut = true;
    while(fut)
    {
        try
        {
        switch(allapot)
        {
            case feher_rak:
                tabla.rajzol(feher.getTomb(), fekete.getTomb());                ///elõször kirajzoljuk a táblát
                std::cout << "Feher rak!" << std::endl;
                if(tabla.malom(feher.getMtx(), feher.rak(fekete.getTomb())))    ///lerakunk egy korongot, és megvizsgáljuk, hogy van-e malom
                {
                    allapot = feher_malom;
                    break;
                }
                if(fekete.rakas_vege())                                         ///ha a feketének nincs több korongja lent
                    allapot = fekete_lep;
                else
                    allapot = fekete_rak;
                break;
            case fekete_rak:
                tabla.rajzol(feher.getTomb(), fekete.getTomb());                ///elõször kirajzoljuk a táblát
                std::cout << "Fekete rak!" << std::endl;
                if(tabla.malom(fekete.getMtx(), fekete.rak(feher.getTomb())))   ///lerakunk egy korongot, és megvizsgáljuk, hogy van-e malom
                {
                    allapot = fekete_malom;
                    break;
                }
                if(feher.rakas_vege())                                          ///ha a fehérnek nincs több korongja lent
                    allapot = feher_lep;
                else
                    allapot = feher_rak;
                break;
            case feher_malom:
                tabla.rajzol(feher.getTomb(), fekete.getTomb());                ///elõször kirajzoljuk a táblát
                std::cout << "Fehernek malma van!\nToroljon egy fekete korongot!" << std::endl;
                fekete.levesz();                                                ///leveszünk egy korongot az ellenségtõl
                if(fekete.jatek_vege())                                         ///ha csak két korong van a táblán
                    allapot = fekete_veszit;
                else if(fekete.rakas_vege())                                    ///ha az ellenség nem tud több korongot lerakni a táblára
                    allapot = fekete_lep;
                else
                    allapot = fekete_rak;
                break;
            case fekete_malom:
                tabla.rajzol(feher.getTomb(), fekete.getTomb());                ///elõször kirajzoljuk a táblát
                std::cout << "Feketenek malma van!\nToroljon egy feher korongot" << std::endl;
                feher.levesz();                                                 ///leveszünk egy korongot az ellenségtõl
                if(feher.jatek_vege())                                          ///ha csak két korong van a táblán
                    allapot = feher_veszit;
                else if(feher.rakas_vege())                                       ///ha az ellenség nem tud több korongot lerakni a táblára
                    allapot = feher_lep;
                else
                    allapot = feher_rak;
                break;
            case feher_lep:
                tabla.rajzol(feher.getTomb(), fekete.getTomb());                ///elõször kirajzoljuk a táblát
                std::cout << "Feher lep!" << std::endl;
                if(tabla.malom(feher.getMtx(), feher.lep(fekete.getTomb())))    ///lépünk egy koronggal, és megvizsgáljuk, hogy van-e malom
                {
                    allapot = feher_malom;
                    break;
                }
                allapot = fekete_lep;
                break;
            case fekete_lep:
                tabla.rajzol(feher.getTomb(), fekete.getTomb());                ///elõször kirajzoljuk a táblát
                std::cout << "Fekete lep!" << std::endl;
                if(tabla.malom(fekete.getMtx(), fekete.lep(feher.getTomb())))    ///lépünk egy koronggal, és megvizsgáljuk, hogy van-e malom
                {
                    allapot = fekete_malom;
                    break;
                }
                allapot = feher_lep;
                break;
            case feher_veszit:
                std::cout << "Feher nyer!" << std::endl;
                fut = false;                               ///leállítjuk a program futását
                break;
            case fekete_veszit:
                std::cout << "Fekete nyer!" << std::endl;
                fut = false;                               ///leállítjuk a program futását
                break;
            default:
                break;
        }
        }catch(int ex)
        {
            std::cout << "Veget ert a file!" << std::endl;
            fut = false;
        }
    }
    #endif
    return 0;
}
