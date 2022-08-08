#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>
#include "enums.h"

using namespace std;

class weapon
{
public:
    // Creates a weapon object with dummy values
    weapon();
    // Creates a weapon object with the provided values
    weapon(string name, string critRange, string damageType, string range, die damageDie, short numberOfDice, abilityType abilityType, short ammo);

    // Getters
    // Returns the name of the weapon
    string Name();
    // Returns the critical range of the weapon
    string CritRange();
    // Returns the damage type of the weapon
    string DamageType();
    // Returns the range increment of the weapon
    string Range();
    // Returns the amount of ammo of the weapon
    short Ammo();
    // Returns the damage formula of the weapon
    string Damage();
    // Returns the ability the weapon uses to attack
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