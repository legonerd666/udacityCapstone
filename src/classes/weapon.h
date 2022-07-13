#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>
#include "../enums.h"

using namespace std;

class weapon
{
public:
    weapon();

    //Getters
    string ToString();
    short Damage(short abilityMod, short baseAttackBonus, short sizeMod);

private:
    string _weapon;
    short _attackBonus;
    string _criticalRange;
    vector<damageType> _damageType;
    string _range;
    short _ammo;
    die _damageDie;
    short _numberOfDamageDice;
    abilityType _abiliyType;
};


#endif