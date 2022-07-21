#include "hitPoints.h"
#include "hitDie.h"

hitPoints::hitPoints() {
    _totalHP = 8;
    _currentDamage = 0;
    _nonLethalDamage = 0;
    _hitdice.emplace_back(make_unique<hitDie>());
}

short hitPoints::TotalHP(short constitutionBonus) {
    
    return (constitutionBonus * TotalHitDice()) + _totalHP > 0 ? (constitutionBonus * TotalHitDice()) + _totalHP : 1;
}

short hitPoints::CurrentHP(short constitutionBonus) {
    return TotalHP(constitutionBonus) - _currentDamage;
}

short hitPoints::CurrentNonLethalHP(short constitutionBonus) {
    return CurrentHP(constitutionBonus) - _nonLethalDamage;
}

vector<unique_ptr<hitDie>>& hitPoints::HitDice(){
    return _hitdice;
}

short hitPoints::TotalHitDice() {
    short totalHitDice = 0;
    for (auto &&hitdie : _hitdice) {
        totalHitDice += hitdie->HitDieNumber();
    }
    return totalHitDice;
}