#ifndef SPELLSTAT_H
#define SPELLSTAT_H

#include <string>
#include "../enums.h"

using namespace std;

class spellStat
{
public:
    spellStat();

    //Getters
    string ToString();
    short SpellDC();

    //Setters
    void SpellLevel(unsigned short newSpellLevel);
    void SpellsKnown(short newSpellsKnown);
    void AbilityType(abilityType newAbilityType);
    void SpellsPerDay(short newSpellsPerDay);
    void BonusSpells(short newBonusSpells);

private:
    unsigned short _spellLevel;
    short spellsKnown;
    abilityType _abilityType;
    short _spellsPerDay;
    short _bonusSpells;
};

#endif