#include "SpellStat.h"

SpellStat::SpellStat()
{
    _spellLevel = 0;
    _spellsKnown = 0;
    _abilityType = intelligence;
    _spellsPerDay = 0;
    _bonusSpells = 0;
}

SpellStat::SpellStat(unsigned short spellLevel, short spellsKnown, abilityType abilityType, short spellsPerDay, short bonusSpells) : _spellLevel(spellLevel), _spellsKnown(spellsKnown), _abilityType(abilityType), _spellsPerDay(spellsPerDay), _bonusSpells(bonusSpells)
{
}

unsigned short SpellStat::SpellLevel()
{
    return _spellLevel;
}
short SpellStat::SpellsKnown()
{
    return _spellsKnown;
}
abilityType SpellStat::AbilityType()
{
    return _abilityType;
}
short SpellStat::SpellsPerDay()
{
    return _spellsPerDay;
}
short SpellStat::BonusSpells()
{
    return _bonusSpells;
}

short SpellStat::SpellDC(short abilityMod)
{
    return 10 + _spellLevel + abilityMod;
}

void SpellStat::SpellsKnown(short spellsKnown)
{
    _spellsKnown = spellsKnown;
}

void SpellStat::SpellsPerDay(short spellsPerDay)
{
    _spellsPerDay = spellsPerDay;
}