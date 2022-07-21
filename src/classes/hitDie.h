#ifndef HITDIE_H
#define HITDIE_H

#include <string>

#include "../enums.h"

using namespace std;

class hitDie
{
public:
    hitDie();

    string To_String();

private:
    die _hitDie;
    short _numberOfHitDice;
};

#endif