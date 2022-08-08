#ifndef HITDIE_H
#define HITDIE_H

#include <string>

#include "enums.h"

using namespace std;

class hitDie
{
public:
    // Creates a hit die with dummy values
    hitDie();
    // Creates a hit die with the die set to the given die enum and the number of dice set to 1
    hitDie(die hitdie);

    // Returns a formatted string of the hitdie (eg. "1d8 ")
    string To_String();

    // Returns the number of hitdie
    short HitDieNumber();

private:
    die _hitDie;
    short _numberOfHitDice;
};

#endif