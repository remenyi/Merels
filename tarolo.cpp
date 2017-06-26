#include "tarolo.h"
#include "memtrace.h"

SzomszedsagiMatrix Tarolo::tabla;
Tarolo::Tarolo()
{
    ///beállítjuk a malom játék tábláját
    tabla.el_beallit(1, 2);
    tabla.el_beallit(1, 10);
    tabla.el_beallit(2, 3);
    tabla.el_beallit(2, 5);
    tabla.el_beallit(3, 15);
    tabla.el_beallit(4, 5);
    tabla.el_beallit(4, 11);
    tabla.el_beallit(5, 6);
    tabla.el_beallit(5, 8);
    tabla.el_beallit(6, 14);
    tabla.el_beallit(7, 8);
    tabla.el_beallit(7, 12);
    tabla.el_beallit(8, 9);
    tabla.el_beallit(9, 13);
    tabla.el_beallit(10, 11);
    tabla.el_beallit(10, 22);
    tabla.el_beallit(11, 12);
    tabla.el_beallit(11, 19);
    tabla.el_beallit(12, 16);
    tabla.el_beallit(13, 14);
    tabla.el_beallit(13, 18);
    tabla.el_beallit(14, 15);
    tabla.el_beallit(14, 21);
    tabla.el_beallit(15, 24);
    tabla.el_beallit(16, 17);
    tabla.el_beallit(17, 18);
    tabla.el_beallit(17, 20);
    tabla.el_beallit(19, 20);
    tabla.el_beallit(20, 21);
    tabla.el_beallit(20, 23);
    tabla.el_beallit(22, 23);
    tabla.el_beallit(23, 24);
}

int Tarolo::string_to_korong(const std::string& string_be, std::ostream& os)
{
    if(string_be.length() > 3)      ///ha a beolvasott string nagyobb, mint ami nekünk kell...
    {
        os << "Tul hosszu a bemeno adat!" << std::endl;
        return -1;
    }
    if((string_be[0] == '1') | (string_be[0] == '2') | (string_be[0] == '3')) ///ha jók az elsõ koordináták
    {
        std::string temp = string_be.substr(1, 3);              ///vizsgáljuk a 2. és 3. koordinátát
        if(temp == "bf")return (51-string_be[0])*3;             ///bf végzõdésû lehet 1, 4, 7
        else if(temp == "fk")return (51-string_be[0])*3+1;      ///fk végzõdésû lehet 2, 5, 8
        else if(temp == "jf")return (51-string_be[0])*3+2;      ///jf végzõdésû lehet 3, 6, 9
        else if(temp == "bk")return (51-string_be[0])+9;        ///bk végzõdésû lehet 10, 11, 12
        else if(temp == "jk")return (14-(51-string_be[0]));     ///jk végzõdésû lehet 13, 14, 15
        else if(temp == "ba")return 21-3*(51-string_be[0]);     ///ba végzõdésû lehet 16, 19, 22
        else if(temp == "ak")return 22-3*(51-string_be[0]);     ///ak végzõdésû lehet 17, 20, 23
        else if(temp == "ja")return 23-3*(51-string_be[0]);     ///ja végzõdésû lehet 18, 21, 24
        else
        {
            os << "Hibas masodik vagy harmadik koordinatat adott meg!" << std::endl;
            return -1;
        }
    }
    else
    {
        os << "Hibas elso koordinatat adott meg!" << std::endl;
        return -1;
    }
}

void Tarolo::szomszedsag_beallit(int korong)
{
    for(int i = 0; i < 24; ++i)
        if(i != korong)
            if(korongok[i])                             ///ha létezik egy másik korong is a korongtömbben
                if(tabla.el_get(korong+1, i+1))         ///és van közöttük él a táblán
                    mtx.el_beallit(korong+1, i+1);      ///legyen közöttük él a szomszédsági mátrixban is
}

int Tarolo::beolvas(const Tomb& t, std::ostream& os, std::istream& is)
{
    std::string string_be;
    is >> string_be;                    ///bekérjük a felhasználótól a koordinátákat
    if(is.eof())throw -1;               ///ha EOF kilépünk
    int korong = string_to_korong(string_be, os);           ///átváltjuk a bemenõ koordinátákat
    while((korong == -1) | t[korong] | korongok[korong])///ha nem sikerült átváltani, vagy már benne van az ellenség koronglistájában vagy a miénkben, újra próbálkozunk az olvasással
    {
        if(t[korong] & (korong > -1))
            os << "Nem rakhat az ellenseg korongjaira!" << std::endl;   ///ha az ellenségében van benne
        if(korongok[korong] & (korong > -1))
            os << "Nem rakhat a sajat korongjaira!" << std::endl;        ///ha a miénkben
        os << "Probalkozzon ujra: ";
        is >> string_be;
        if(is.eof())throw -1;
        korong = string_to_korong(string_be, os);
    }
    korongok[korong] = true;        ///ha sikeres a beolvasás, beletesszük a koronglistába
    szomszedsag_beallit(korong);    ///beállítjuk a szomszédsági mátrixot
    return korong;
}

void Tarolo::nemszomszedsag_beallit(int korong)
{
    for(int i = 0; i < 24; ++i)
        if(korong != i)
            if(korongok[i])          ///ha létezik egy másik korong is a korongtömbben
                if(tabla.el_get(korong+1, i+1))         ///és van közöttük él a táblán
                    mtx.nemel_beallit(korong+1, i+1);   ///ne legyen közöttük él a szomszédsági mátrixban
}

int Tarolo::torol(std::ostream& os, std::istream& is)
{
    std::string string_be;
    is >> string_be;                              ///bekérjük a felhasználótól a koordinátákat
    if(is.eof())throw -1;               ///ha EOF kilépünk
    int korong = string_to_korong(string_be, os);           ///átváltjuk a bemenõ koordinátákat
    while((korong == -1) | !korongok[korong])           ///ha nem sikerült átváltani, vagy nincs a mi tömbünkben, újra próbálkounk az olvasással
    {
        if(!korongok[korong])                           ///ha nem a mi tömbünkben volt
            os << "Rossz helyrol torolt korongot!" << std::endl;
        os << "Probalokozzon ujra: ";
        is >> string_be;
        if(is.eof())throw -1;
        korong = string_to_korong(string_be, os);
    }
    korongok[korong] = false;                           ///ha sikerült az olvasás, töröljük a listából
    nemszomszedsag_beallit(korong);                     ///és a szomszédsági mtxból is
    return korong;
}

void Tarolo::torol(int korong)
{
    korongok[korong] = false;
    nemszomszedsag_beallit(korong);
}
