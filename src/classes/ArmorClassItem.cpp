#include "ArmorClassItem.h"

#include <climits>

ArmorClassItem::ArmorClassItem()
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

ArmorClassItem::ArmorClassItem(string name, string type, unsigned short bonus, unsigned short maxDexBonus, short checkPenalty, unsigned short spellFailureChance, unsigned short baseSpeedAdjustment, unsigned short weight, string properties) : _name(name), _type(type), _bonus(bonus), _maxDexBonus(maxDexBonus), _checkPenalty(checkPenalty), _spellFailureChance(spellFailureChance), _baseSpeedAdjustment(baseSpeedAdjustment), _weight(weight), _properties(properties)
{
}

string ArmorClassItem::Name()
{
    return _name;
}

string ArmorClassItem::Type()
{
    return _type;
}

unsigned short ArmorClassItem::Bonus()
{
    return _bonus;
}

unsigned short ArmorClassItem::MaxDexBonus()
{
    return _maxDexBonus;
}

short ArmorClassItem::CheckPenalty()
{
    return _checkPenalty;
}

unsigned short ArmorClassItem::SpellFailureChance()
{
    return _spellFailureChance;
}

unsigned short ArmorClassItem::BaseSpeedAdjustment()
{
    return _baseSpeedAdjustment;
}

unsigned short ArmorClassItem::Weight()
{
    return _weight;
}

string ArmorClassItem::Properties()
{
    return _properties;
}