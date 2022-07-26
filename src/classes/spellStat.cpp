#include "spellStat.h"

spellStat::spellStat()
{
    _spellLevel = 0;
    _spellsKnown = 0;
    _abilityType = intelligence;
    _spellsPerDay = 0;
    _bonusSpells = 0;
}

spellStat::spellStat(unsigned short spellLevel, short spellsKnown, abilityType abilityType, short spellsPerDay, short bonusSpells) : _spellLevel(spellLevel), _spellsKnown(spellsKnown), _abilityType(abilityType), _spellsPerDay(spellsPerDay), _bonusSpells(bonusSpells)
{
}

unsigned short spellStat::SpellLevel()
{
    return _spellLevel;
}
short spellStat::SpellsKnown()
{
    return _spellsKnown;
}
abilityType spellStat::AbilityType()
{
    return _abilityType;
}
short spellStat::SpellsPerDay()
{
    return _spellsPerDay;
}
short spellStat::BonusSpells()
{
    return _bonusSpells;
}

short spellStat::SpellDC(short abilityMod)
{
    return 10 + _spellLevel + abilityMod;
}