#ifndef HITDIE_H
#define HITDIE_H

#include <string>

#include "../enums.h"

using namespace std;

class hitDie
{
public:
    hitDie();
    hitDie(die hitdie);

    string To_String();

    short HitDieNumber();

private:
    die _hitDie;
    short _numberOfHitDice;
};

#endif