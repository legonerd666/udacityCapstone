#include "hitDie.h"
#include "../enums.h"

hitDie::hitDie() {
    _hitDie = d8;
    _numberOfHitDice = 1;
}

string hitDie::To_String() {
    return to_string(_numberOfHitDice) + EnumToString(_hitDie) + " ";
}

short hitDie::HitDieNumber() {
    return _numberOfHitDice;
}