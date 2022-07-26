#ifndef SPELLSTAT_H
#define SPELLSTAT_H

#include <string>
#include "../enums.h"

using namespace std;

class spellStat
{
public:
    spellStat();
    spellStat(unsigned short spellLevel, short spellsKnown, abilityType abilityType, short spellsPerDay, short bonusSpells);

    // Getters
    unsigned short SpellLevel();
    short SpellsKnown();
    abilityType AbilityType();
    short SpellsPerDay();
    short BonusSpells();
    short SpellDC(short abilityMod);

private:
    unsigned short _spellLevel;
    short _spellsKnown;
    abilityType _abilityType;
    short _spellsPerDay;
    short _bonusSpells;
};

#endif