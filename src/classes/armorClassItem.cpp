#include "armorClassItem.h"

#include <climits>

armorClassItem::armorClassItem()
{
    _name = "Example Armor Item";
    _type = "Armor";
    _bonus = 0;
    _maxDexBonus = USHRT_MAX;
    _checkPenalty = 0;
    _spellFailureChance = 5;
    _baseSpeedAdjustment = 30;
    _weight = 0;
    _properties = "Example Properties";
}

armorClassItem::armorClassItem(string name, string type, unsigned short bonus, unsigned short maxDexBonus, short checkPenalty, unsigned short spellFailureChance, unsigned short baseSpeedAdjustment, unsigned short weight, string properties) : _name(name), _type(type), _bonus(bonus), _maxDexBonus(maxDexBonus), _checkPenalty(checkPenalty), _spellFailureChance(spellFailureChance), _baseSpeedAdjustment(baseSpeedAdjustment), _weight(weight), _properties(properties)
{
}

string armorClassItem::Name()
{
    return _name;
}

string armorClassItem::Type()
{
    return _type;
}

unsigned short armorClassItem::Bonus()
{
    return _bonus;
}

unsigned short armorClassItem::MaxDexBonus()
{
    return _maxDexBonus;
}

short armorClassItem::CheckPenalty()
{
    return _checkPenalty;
}

unsigned short armorClassItem::SpellFailureChance()
{
    return _spellFailureChance;
}

unsigned short armorClassItem::BaseSpeedAdjustment()
{
    return _baseSpeedAdjustment;
}

unsigned short armorClassItem::Weight()
{
    return _weight;
}

string armorClassItem::Properties()
{
    return _properties;
}