#ifndef TOMB_H_INCLUDED
#define TOMB_H_INCLUDED
#include "memtrace.h"

class Tomb
{
    bool* tomb;
public:
    Tomb(): tomb(new bool[24]) {for(int i = 0; i < 24; i++)tomb[i] = false;};   ///t�mb elemeit false-ra �ll�tjuk be
    Tomb(const Tomb& rhs):tomb(new bool[24]) {for(int i = 0; i < 24; i++)tomb[i] = rhs[i];}
    Tomb& operator=(const Tomb& rhs)
    {
        if(this != &rhs)
        {
            delete[] tomb;
            tomb = new bool[24];
            for(int i = 0; i < 24; i++)
                tomb[i] = rhs[i];
        }
        return *this;
    }
    bool& operator[](int idx){return tomb[idx];}
    const bool& operator[](int idx)const{return tomb[idx];}
    ~Tomb()
    {
        delete[] tomb;
    }
};

#endif // TOMB_H_INCLUDED
