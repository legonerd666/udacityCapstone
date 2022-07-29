#include "spell.h"

spell::spell()
{
    _name = "Example Spell";
    _school = evocation;
    _roles.emplace_back(make_shared<classSpellListItem>());
    _castingTime = "Example Casting Time";
    _components = "V, S, M (Example Material Component)";
    _range = "Example Range";
    _target = "Example Target(s)";
    _duration = "Example Duration";
    _savingThrow = "None";
    _spellResistance = false;
    _description = "Example Description";
}

string spell::Name()
{
    return _name;
}

magicSchool spell::School()
{
    return _school;
}

vector<shared_ptr<classSpellListItem>> spell::Roles()
{
    return _roles;
}

string spell::CastingTime()
{
    return _castingTime;
}

string spell::Components()
{
    return _components;
}

string spell::Range()
{
    return _range;
}

string spell::Target()
{
    return _target;
}

string spell::Duration()
{
    return _duration;
}

string spell::SavingThrow()
{
    return _savingThrow;
}

bool spell::SpellResistance()
{
    return _spellResistance;
}

string spell::Description()
{
    return _description;
}
