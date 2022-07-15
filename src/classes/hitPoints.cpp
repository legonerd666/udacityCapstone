#include "hitPoints.h"
#include "hitDie.h"

hitPoints::hitPoints() {
    _totalHP = 8;
    _currentDamage = 0;
    _nonLethalDamage = 0;
}

short hitPoints::TotalHP() {
    return _totalHP;
}

short hitPoints::CurrentHP() {
    return _totalHP - _currentDamage;
}

short hitPoints::CurrentNonLethalHP() {
    return CurrentHP() - _nonLethalDamage;
}

vector<unique_ptr<hitDie>>& hitPoints::HitDice(){
    return _hitdice;
}