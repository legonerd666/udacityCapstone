#include "HitDie.h"
#include "enums.h"

HitDie::HitDie()
{
    _hitDie = d8;
    _numberOfHitDice = 1;
}

HitDie::HitDie(die hitdie) : _hitDie(hitdie), _numberOfHitDice(1)
{
}

string HitDie::To_String()
{
    return to_string(_numberOfHitDice) + EnumToString(_hitDie) + " ";
}

short HitDie::HitDieNumber()
{
    return _numberOfHitDice;
}