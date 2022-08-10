#include "HitPoints.h"
#include "HitDie.h"

HitPoints::HitPoints()
{
    _totalHP = 8;
    _currentDamage = 0;
    _nonLethalDamage = 0;
    _hitdice.emplace_back(make_unique<HitDie>());
}

HitPoints::HitPoints(die hitdie) : _currentDamage(0), _nonLethalDamage(0)
{
    _totalHP = EnumToMax(hitdie);
    _hitdice.emplace_back(make_unique<HitDie>(hitdie));
}

short HitPoints::TotalHP(short constitutionBonus)
{

    return (constitutionBonus * TotalHitDice()) + _totalHP > 0 ? (constitutionBonus * TotalHitDice()) + _totalHP : 1;
}

short HitPoints::CurrentHP(short constitutionBonus)
{
    return TotalHP(constitutionBonus) - _currentDamage;
}

short HitPoints::CurrentNonLethalHP(short constitutionBonus)
{
    return CurrentHP(constitutionBonus) - _nonLethalDamage;
}

vector<unique_ptr<HitDie>> &HitPoints::HitDice()
{
    return _hitdice;
}

short HitPoints::TotalHitDice()
{
    short totalHitDice = 0;
    for (auto &&hitdie : _hitdice)
    {
        totalHitDice += hitdie->HitDieNumber();
    }
    return totalHitDice;
}