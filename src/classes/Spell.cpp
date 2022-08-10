#include "Spell.h"

Spell::Spell()
{
    _name = "Example Spell";
    _school = evocation;
    _roles.emplace_back(make_shared<ClassSpellListItem>());
    _castingTime = "Example Casting Time";
    _components = "V, S, M (Example Material Component)";
    _range = "Example Range";
    _target = "Example Target(s)";
    _duration = "Example Duration";
    _savingThrow = "None";
    _spellResistance = false;
    _description = "Example Description";
}

Spell::Spell(string name, magicSchool magicSchool, vector<shared_ptr<ClassSpellListItem>> roles, string castingTime, string components, string range, string target, string duration, string savingThrow, bool spellResistance, string description) : _name(name), _school(magicSchool), _roles(roles), _castingTime(castingTime), _components(components), _range(range), _target(target), _duration(duration), _savingThrow(savingThrow), _spellResistance(spellResistance), _description(description) {}

string Spell::Name()
{
    return _name;
}

magicSchool Spell::School()
{
    return _school;
}

vector<shared_ptr<ClassSpellListItem>> Spell::Roles()
{
    return _roles;
}

string Spell::CastingTime()
{
    return _castingTime;
}

string Spell::Components()
{
    return _components;
}

string Spell::Range()
{
    return _range;
}

string Spell::Target()
{
    return _target;
}

string Spell::Duration()
{
    return _duration;
}

string Spell::SavingThrow()
{
    return _savingThrow;
}

bool Spell::SpellResistance()
{
    return _spellResistance;
}

string Spell::Description()
{
    return _description;
}
