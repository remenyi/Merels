#include "tarolo.h"
#include "memtrace.h"

SzomszedsagiMatrix Tarolo::tabla;
Tarolo::Tarolo()
{
    ///be�ll�tjuk a malom j�t�k t�bl�j�t
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
    if(string_be.length() > 3)      ///ha a beolvasott string nagyobb, mint ami nek�nk kell...
    {
        os << "Tul hosszu a bemeno adat!" << std::endl;
        return -1;
    }
    if((string_be[0] == '1') | (string_be[0] == '2') | (string_be[0] == '3')) ///ha j�k az els� koordin�t�k
    {
        std::string temp = string_be.substr(1, 3);              ///vizsg�ljuk a 2. �s 3. koordin�t�t
        if(temp == "bf")return (51-string_be[0])*3;             ///bf v�gz�d�s� lehet 1, 4, 7
        else if(temp == "fk")return (51-string_be[0])*3+1;      ///fk v�gz�d�s� lehet 2, 5, 8
        else if(temp == "jf")return (51-string_be[0])*3+2;      ///jf v�gz�d�s� lehet 3, 6, 9
        else if(temp == "bk")return (51-string_be[0])+9;        ///bk v�gz�d�s� lehet 10, 11, 12
        else if(temp == "jk")return (14-(51-string_be[0]));     ///jk v�gz�d�s� lehet 13, 14, 15
        else if(temp == "ba")return 21-3*(51-string_be[0]);     ///ba v�gz�d�s� lehet 16, 19, 22
        else if(temp == "ak")return 22-3*(51-string_be[0]);     ///ak v�gz�d�s� lehet 17, 20, 23
        else if(temp == "ja")return 23-3*(51-string_be[0]);     ///ja v�gz�d�s� lehet 18, 21, 24
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
            if(korongok[i])                             ///ha l�tezik egy m�sik korong is a korongt�mbben
                if(tabla.el_get(korong+1, i+1))         ///�s van k�z�tt�k �l a t�bl�n
                    mtx.el_beallit(korong+1, i+1);      ///legyen k�z�tt�k �l a szomsz�ds�gi m�trixban is
}

int Tarolo::beolvas(const Tomb& t, std::ostream& os, std::istream& is)
{
    std::string string_be;
    is >> string_be;                    ///bek�rj�k a felhaszn�l�t�l a koordin�t�kat
    if(is.eof())throw -1;               ///ha EOF kil�p�nk
    int korong = string_to_korong(string_be, os);           ///�tv�ltjuk a bemen� koordin�t�kat
    while((korong == -1) | t[korong] | korongok[korong])///ha nem siker�lt �tv�ltani, vagy m�r benne van az ellens�g koronglist�j�ban vagy a mi�nkben, �jra pr�b�lkozunk az olvas�ssal
    {
        if(t[korong] & (korong > -1))
            os << "Nem rakhat az ellenseg korongjaira!" << std::endl;   ///ha az ellens�g�ben van benne
        if(korongok[korong] & (korong > -1))
            os << "Nem rakhat a sajat korongjaira!" << std::endl;        ///ha a mi�nkben
        os << "Probalkozzon ujra: ";
        is >> string_be;
        if(is.eof())throw -1;
        korong = string_to_korong(string_be, os);
    }
    korongok[korong] = true;        ///ha sikeres a beolvas�s, beletessz�k a koronglist�ba
    szomszedsag_beallit(korong);    ///be�ll�tjuk a szomsz�ds�gi m�trixot
    return korong;
}

void Tarolo::nemszomszedsag_beallit(int korong)
{
    for(int i = 0; i < 24; ++i)
        if(korong != i)
            if(korongok[i])          ///ha l�tezik egy m�sik korong is a korongt�mbben
                if(tabla.el_get(korong+1, i+1))         ///�s van k�z�tt�k �l a t�bl�n
                    mtx.nemel_beallit(korong+1, i+1);   ///ne legyen k�z�tt�k �l a szomsz�ds�gi m�trixban
}

int Tarolo::torol(std::ostream& os, std::istream& is)
{
    std::string string_be;
    is >> string_be;                              ///bek�rj�k a felhaszn�l�t�l a koordin�t�kat
    if(is.eof())throw -1;               ///ha EOF kil�p�nk
    int korong = string_to_korong(string_be, os);           ///�tv�ltjuk a bemen� koordin�t�kat
    while((korong == -1) | !korongok[korong])           ///ha nem siker�lt �tv�ltani, vagy nincs a mi t�mb�nkben, �jra pr�b�lkounk az olvas�ssal
    {
        if(!korongok[korong])                           ///ha nem a mi t�mb�nkben volt
            os << "Rossz helyrol torolt korongot!" << std::endl;
        os << "Probalokozzon ujra: ";
        is >> string_be;
        if(is.eof())throw -1;
        korong = string_to_korong(string_be, os);
    }
    korongok[korong] = false;                           ///ha siker�lt az olvas�s, t�r�lj�k a list�b�l
    nemszomszedsag_beallit(korong);                     ///�s a szomsz�ds�gi mtxb�l is
    return korong;
}

void Tarolo::torol(int korong)
{
    korongok[korong] = false;
    nemszomszedsag_beallit(korong);
}
