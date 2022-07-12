#ifndef HITDICE_H
#define HITDICE_H

#include <string>

using namespace std;

enum die {d4, d6, d8, d10, d12, d20};

class hitDice
{
public:
    hitDice();

    string To_String();

private:
    die _hitDie;
    short _numberOfHitDice;
    string role; //Needs Class Def
};

#endif