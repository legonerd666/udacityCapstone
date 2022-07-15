#ifndef HITPOINTS_H
#define HITPOINTS_H

#include <vector>
#include <memory>

#include "hitDie.h"

using namespace std;

class hitPoints {
public:
    hitPoints();

    //Getters
    short TotalHP();
    short CurrentHP();
    short CurrentNonLethalHP();
    vector<unique_ptr<hitDie>>& HitDice();

    //Setters
    // void TotalHP(short newTotalHP);
    // void CurrentHP(short newCurrentHP);
    // void CurrentNonLethalHP(short newCurrentNonLethalDamage);
    // void HitDice(vector<unique_ptr<hitDice>> newHitDice);

private:
    short _totalHP;
    short _currentDamage;
    short _nonLethalDamage;
    vector<unique_ptr<hitDie>> _hitdice;

};


#endif