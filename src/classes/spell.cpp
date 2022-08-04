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

spell::spell(string name, magicSchool magicSchool, vector<shared_ptr<classSpellListItem>> roles, string castingTime, string components, string range, string target, string duration, string savingThrow, bool spellResistance, string description) : _name(name), _school(magicSchool), _roles(roles), _castingTime(castingTime), _components(components), _range(range), _target(target), _duration(duration), _savingThrow(savingThrow), _spellResistance(spellResistance), _description(description) {}

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
