#ifndef ARMORCLASSITEM_H
#define ARMORCLASSITEM_H

#include <string>

using namespace std;

class armorClassItem
{
public:
    armorClassItem();
    armorClassItem(string name, string type, unsigned short bonus, unsigned short maxDexBonus, short checkPenalty, unsigned short spellFailureChance, short baseSpeedAdjustment, unsigned short weight, string properties);

    // Getters
    string Name();
    string Type();
    unsigned short Bonus();
    unsigned short MaxDexBonus();
    short CheckPenalty();
    unsigned short SpellFailureChance();
    short BaseSpeedAdjustment();
    unsigned short Weight();
    string Properties();

private:
    string _name;
    string _type;
    unsigned short _bonus;
    unsigned short _maxDexBonus;
    short _checkPenalty;
    unsigned short _spellFailureChance;
    short _baseSpeedAdjustment;
    unsigned short _weight;
    string _properties;
};

#endif