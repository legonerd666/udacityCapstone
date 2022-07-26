#include "role.h"

role::role()
{
    _name = "Example Class";
    _level = 1;

    _isCastingClass = true;
    for (short i = 0; i < 10; i++)
    {
        _spellStats[i] = make_shared<spellStat>();
    }
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

bool role::IsCastingClass()
{
    return _isCastingClass;
}