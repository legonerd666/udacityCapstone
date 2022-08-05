#ifndef SPELLSTAT_H
#define SPELLSTAT_H

#include <string>
#include "../enums.h"

using namespace std;

class spellStat
{
public:
    // Creates a spellstat object with dummy values
    spellStat();
    // Creates a spellstat object with the given values
    spellStat(unsigned short spellLevel, short spellsKnown, abilityType abilityType, short spellsPerDay, short bonusSpells);

    // Getters
    // Returns the spellstats' level
    unsigned short SpellLevel();
    // Returns the spellstats' spells known
    short SpellsKnown();
    // Returns the spellstats' casting ability type
    abilityType AbilityType();
    // Returns the spellstats' spells per day
    short SpellsPerDay();
    // Returns the spellstats' bonus spells per day
    short BonusSpells();
    // Returns the spellstats' spell difficulty class
    short SpellDC(short abilityMod);

    // Setters
    // Sets the spell stats' spells known to the given values
    void SpellsKnown(short spellsKnown);
    // Sets the spell stats' spells per day to the provided short
    void SpellsPerDay(short spellsPerDay);

private:
    unsigned short _spellLevel;
    short _spellsKnown;
    abilityType _abilityType;
    short _spellsPerDay;
    short _bonusSpells;
};

#endif