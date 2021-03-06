#ifndef HITPOINTS_H
#define HITPOINTS_H

#include <vector>

#include "hitDice.h"

using namespace std;

class hitPoints {
public:
    hitPoints();

    //Getters
    short TotalHP();
    short CurrentHP();
    short CurrentNonLethalHP();

    //Setters
    void TotalHP(short newTotalHP);
    void CurrentHP(short newCurrentHP);
    void CurrentNonLethalHP(short newCurrentNonLethalDamage);

private:
    short _totalHP;
    short _currentDamage;
    short _nonLethalDamage;
    vector<hitDice> _hitdice;

};


#endif