#ifndef HITDICE_H
#define HITDICE_H

#include <string>

#include "../enums.h"

using namespace std;

class hitDice
{
public:
    hitDice();

    string To_String();

private:
    die _hitDie;
    short _numberOfHitDice;
};

#endif