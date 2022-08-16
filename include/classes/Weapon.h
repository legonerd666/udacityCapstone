#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>

#include "../enums.h"

using namespace std;

/**
 * @brief Stores all the information needed to make an attack with a specific \ref Weapon "weapon".
 *
 */
class Weapon
{
public:
    // Creates a Weapon object with dummy values
    Weapon();
    // Creates a Weapon object with the provided values
    Weapon(string name, string critRange, string damageType, string range, die damageDie, short numberOfDice, abilityType abilityType, short ammo);

    // Getters
    // Returns the name of the Weapon
    string Name();
    // Returns the critical range of the Weapon
    string CritRange();
    // Returns the damage type of the Weapon
    string DamageType();
    // Returns the range increment of the Weapon
    string Range();
    // Returns the amount of ammo of the Weapon
    short Ammo();
    // Returns the damage formula of the Weapon
    string Damage();
    // Returns the ability the Weapon uses to attack
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