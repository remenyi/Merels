#include "tabla.h"
#include "memtrace.h"
bool Tabla::malom(const SzomszedsagiMatrix& mtx, int hely)
{
    hely++;
    switch(hely)
    {
    case 1:
        return((mtx.el_get(1, 2) & mtx.el_get(2, 3)) | (mtx.el_get(1, 10) & mtx.el_get(10, 22)));
    case 2:
        return((mtx.el_get(1, 2) & mtx.el_get(2, 3)) | (mtx.el_get(2, 5) & mtx.el_get(5, 8)));
    case 3:
        return((mtx.el_get(1, 2) & mtx.el_get(2, 3)) | (mtx.el_get(3, 15) & mtx.el_get(15, 24)));
    case 4:
        return((mtx.el_get(4, 5) & mtx.el_get(5, 6)) | (mtx.el_get(4, 11) & mtx.el_get(11, 19)));
    case 5:
        return((mtx.el_get(4, 5) & mtx.el_get(5, 6)) | (mtx.el_get(2, 5) & mtx.el_get(5, 8)));
    case 6:
        return((mtx.el_get(4, 5) & mtx.el_get(5, 6)) | (mtx.el_get(6, 14) & mtx.el_get(14, 21)));
    case 7:
        return((mtx.el_get(7, 8) & mtx.el_get(8, 9)) | (mtx.el_get(7, 12) & mtx.el_get(12, 16)));
    case 8:
        return((mtx.el_get(7, 8) & mtx.el_get(8, 9)) | (mtx.el_get(5, 8) & mtx.el_get(2, 5)));
    case 9:
        return((mtx.el_get(7, 8) & mtx.el_get(8, 9)) | (mtx.el_get(9, 13) & mtx.el_get(13, 18)));
    case 10:
        return((mtx.el_get(10, 11) & mtx.el_get(11, 12)) | (mtx.el_get(1, 10) & mtx.el_get(10, 22)));
    case 11:
        return((mtx.el_get(10, 11) & mtx.el_get(11, 12)) | (mtx.el_get(4, 11) & mtx.el_get(11, 19)));
    case 12:
        return((mtx.el_get(10, 11) & mtx.el_get(11, 12)) | (mtx.el_get(7, 12) & mtx.el_get(12, 16)));
    case 13:
        return((mtx.el_get(13, 14) & mtx.el_get(14, 15)) | (mtx.el_get(9, 13) & mtx.el_get(13, 18)));
    case 14:
        return((mtx.el_get(13, 14) & mtx.el_get(14, 15)) | (mtx.el_get(6, 14) & mtx.el_get(14, 21)));
    case 15:
        return((mtx.el_get(13, 14) & mtx.el_get(14, 15)) | (mtx.el_get(3, 15) & mtx.el_get(15, 24)));
    case 16:
        return((mtx.el_get(16, 17) & mtx.el_get(17, 18)) | (mtx.el_get(4, 11) & mtx.el_get(11, 19)));
    case 17:
        return((mtx.el_get(16, 17) & mtx.el_get(17, 18)) | (mtx.el_get(17, 20) & mtx.el_get(20, 23)));
    case 18:
        return((mtx.el_get(16, 17) & mtx.el_get(17, 18)) | (mtx.el_get(9, 13) & mtx.el_get(13, 18)));
    case 19:
        return((mtx.el_get(19, 20) & mtx.el_get(20, 21)) | (mtx.el_get(4, 11) & mtx.el_get(11, 19)));
    case 20:
        return((mtx.el_get(19, 20) & mtx.el_get(20, 21)) | (mtx.el_get(17, 20) & mtx.el_get(20, 23)));
    case 21:
        return((mtx.el_get(19, 20) & mtx.el_get(20, 21)) | (mtx.el_get(6, 14) & mtx.el_get(14, 21)));
    case 22:
        return((mtx.el_get(22, 23) & mtx.el_get(23, 24)) | (mtx.el_get(1, 10) & mtx.el_get(10, 22)));
    case 23:
        return((mtx.el_get(22, 23) & mtx.el_get(23, 24)) | (mtx.el_get(17, 20) & mtx.el_get(20, 23)));
    case 24:
        return((mtx.el_get(22, 23) & mtx.el_get(23, 24)) | (mtx.el_get(3, 15) & mtx.el_get(15, 24)));
    default:
        std::cout << "Nem 1 es 24 koze eso korongot adott meg!" << std::endl;
        return false;
    }
}

void Tabla::rajzol(const Tomb& feher_tomb, const Tomb& fekete_tomb, std::ostream& os)
{
    int korongok[24] = {0};
    for(int i = 0; i < 24; i++)
        korongok[i] = (feher_tomb[i] ? 1 : fekete_tomb[i]? 2 : 0);
    //system("cls");
    os << "\n" << korongok[0] << "---------" << korongok[1] << "---------" << korongok[2]
                << "\n|         |         |\n|  "
                << korongok[3] << "------" << korongok[4] << "------" << korongok[5]
                << "  |\n|  |      |      |  |\n|  |  "
                << korongok[6] << "---" << korongok[7] << "---" << korongok[8]
                << "  |  |\n|  |  |       |  |  |\n"
                << korongok[9] << "--" << korongok[10] << "--" << korongok[11] << "       " << korongok[12] << "--" << korongok[13] << "--" << korongok[14]
                << "\n|  |  |       |  |  |\n|  |  " << korongok[15] << "---" << korongok[16] << "---" << korongok[17]
                << "  |  |\n|  |      |      |  |\n|  "
                << korongok[18] << "------" << korongok[19] << "------" << korongok[20]
                << "  |\n|         |         |\n"
                << korongok[21] << "---------" << korongok[22] << "---------" << korongok[23] << "\n" << std::endl;
}
