#include "Weapon.h"

#include "enums.h"

Weapon::Weapon()
{
    _name = "Example Weapon";
    _criticalRange = "x2";
    _damageType = "S";
    _range = "Melee";
    _ammo = 0;
    _damageDie = d4;
    _numberOfDamageDice = 1;
    _abiliyType = strength;
}

Weapon::Weapon(string name, string critRange, string damageType, string range, die damageDie, short numberOfDice, abilityType abilityType, short ammo) : _name(name), _criticalRange(critRange), _damageType(damageType), _range(range), _damageDie(damageDie), _numberOfDamageDice(numberOfDice), _abiliyType(abilityType), _ammo(ammo)
{
}

string Weapon::Name()
{
    return _name;
}

string Weapon::CritRange()
{
    return _criticalRange;
}

string Weapon::DamageType()
{
    return _damageType;
}

string Weapon::Range()
{
    return _range;
}

short Weapon::Ammo()
{
    return _ammo;
}

string Weapon::Damage()
{
    return to_string(_numberOfDamageDice) + EnumToString(_damageDie);
}

abilityType Weapon::AbilityType()
{
    return _abiliyType;
}