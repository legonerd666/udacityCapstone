#include "role.h"

role::role()
{
    _name = "Example Class";
    _level = 1;
}

role::role(string name) : _name(name), _level(1)
{
}

string role::Name()
{
    return _name;
}

unsigned short role::Level()
{
    return _level;
}

vector<shared_ptr<feat>> role::ClassFeatures()
{
    return _classFeatures;
}

shared_ptr<spellStat> *role::SpellStats()
{
    return _spellStats;
}

vector<shared_ptr<spell>> role::Spells()
{
    return _spells;
}

bool role::IsCastingClass()
{
    return _isCastingClass;
}

void role::AddSpell(shared_ptr<spell> &&spell)
{
    _spells.emplace_back(move(spell));
}

void role::SetToCastingClass(abilityType castingAbility, short castingAbilityMod)
{
    _isCastingClass = true;

    short bonusSpells[10];
    bonusSpells[0] = 0;
    short bonusSpellBase;
    // If the ability mod would not afford them any bonus spells it sets all the bonus spells to 0
    if (castingAbilityMod < 1)
    {
        for (auto &&spells : bonusSpells)
        {
            spells = 0;
        }
    }
    else
    {
        // For each bonus spell of level 1 to 9 it sets the bonus spells properly based on the casting ability scores' modifier (for a better understanding of the calculation check table 1-3 of the Pathfinder 1e Core Rulebook)
        for (short i = 0; i < 9; i++)
        {
            bonusSpellBase = castingAbilityMod - i;
            if (bonusSpellBase > 0)
            {
                // Brings the base number of bonus spells to a multiple of 4
                if (bonusSpellBase % 4 == 1)
                    bonusSpellBase += 3;
                else if (bonusSpellBase % 4 == 2)
                    bonusSpellBase += 2;
                else if (bonusSpellBase % 4 == 3)
                    bonusSpellBase += 1;
                // Sets the bonus spells at the proper level to the base number of bonus spells divided by 4
                bonusSpells[i + 1] = bonusSpellBase / 4;
            }
            else
            {
                bonusSpells[i + 1] = 0;
            }
        }
    }
    for (short i = 0; i < 10; i++)
    {
        _spellStats[i] = make_shared<spellStat>(i, 0, castingAbility, 0, bonusSpells[i]);
    }
}

void role::AddClassFeature(string name, string description)
{
    _classFeatures.emplace_back(make_shared<feat>(name, description));
}