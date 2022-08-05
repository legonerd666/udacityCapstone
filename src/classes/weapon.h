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

    weapon(string name, string critRange, string damageType, string range, die damageDie, short numberOfDice, abilityType abilityType, short ammo);

    // Getters
    string Name();
    string CritRange();
    string DamageType();
    string Range();
    short Ammo();
    string Damage();
    abilityType AbilityType();

private:
    string _name;
    string _criticalRange;
    string _damageType;
    string _range;
    short _ammo;
    die _damageDie;
    short _numberOfDamageDice;
    abilityType _abiliyType;
};

#endif