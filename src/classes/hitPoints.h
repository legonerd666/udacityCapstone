#ifndef HITPOINTS_H
#define HITPOINTS_H

#include <vector>
#include <memory>

#include "hitDie.h"

using namespace std;

class hitPoints
{
public:
    hitPoints();
    hitPoints(die hitdie);

    // Getters
    short TotalHP(short constitutionBonus);
    short CurrentHP(short constitionBonus);
    short CurrentNonLethalHP(short constitutionBonus);
    vector<unique_ptr<hitDie>> &HitDice();
    short TotalHitDice();

private:
    short _totalHP;
    short _currentDamage;
    short _nonLethalDamage;
    vector<unique_ptr<hitDie>> _hitdice;
};

#endif