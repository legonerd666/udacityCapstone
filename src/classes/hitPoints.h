#ifndef HITPOINTS_H
#define HITPOINTS_H

#include <vector>
#include <memory>

#include "hitDie.h"

using namespace std;

class hitPoints
{
public:
    // Creates a hitpoint object with dummy values
    hitPoints();
    // Creates a hitpoint object with the max health of the hit die provided and initializes a hitdie object with the hitdie
    hitPoints(die hitdie);

    // Getters
    // Returns the max hitpoints based off the stored values and the characters constitution score
    short TotalHP(short constitutionBonus);
    // Returns the current hitpoints based off the stored values and the characters constitution score
    short CurrentHP(short constitionBonus);
    // Returns the current non lethal hp based off the stored values and the characters constitution
    short CurrentNonLethalHP(short constitutionBonus);
    // Returns a refernce to the vector of hitdice in the object
    vector<unique_ptr<hitDie>> &HitDice();
    // Returns the total hitdice by adding up the number of hit dice in the objects vector of hitdie objects
    short TotalHitDice();

private:
    short _totalHP;
    short _currentDamage;
    short _nonLethalDamage;
    vector<unique_ptr<hitDie>> _hitdice;
};

#endif