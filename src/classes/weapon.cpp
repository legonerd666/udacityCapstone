#include "weapon.h"

#include "../enums.h"

weapon::weapon() {
    _name = "Example Weapon";
    _criticalRange = "x2";
    _damageType = "S";
    _range = "Melee";
    _ammo = 0;
    _damageDie = d4;
    _numberOfDamageDice = 1;
    _abiliyType = strength;
}

weapon::weapon(string name, string critRange, string damageType, string range, die damageDie, short numberOfDice, abilityType abilityType):
_name(name), _criticalRange(critRange), _damageType(damageType), _range(range), _damageDie(damageDie), _numberOfDamageDice(numberOfDice), _abiliyType(abilityType) {
    _ammo = 0;
}

string weapon::Name() {
    return _name;
}

string weapon::CritRange() {
    return _criticalRange;
}

string weapon::DamageType() {
    return _damageType;
}

string weapon::Range() {
    return _range;
}

short weapon::Ammo() {
    return _ammo;
}

string weapon::Damage() {
    return to_string(_numberOfDamageDice) + EnumToString(_damageDie);
}

abilityType weapon::AbilityType() {
    return _abiliyType;
}