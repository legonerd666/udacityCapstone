#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <vector>
#include "../enums.h"
#include "classSpellListItem.h"
#include <memory>

using namespace std;

class spell
{
public:
    spell();

    // Getters
    string Name();
    magicSchool School();
    vector<shared_ptr<classSpellListItem>> Roles();
    string CastingTime();
    string Components();
    string Range();
    string Target();
    string Duration();
    saveType SavingThrow();
    bool SpellResistance();
    string Description();

private:
    string _name;
    magicSchool _school;
    vector<shared_ptr<classSpellListItem>> _roles;
    string _castingTime;
    string _components;
    string _range;
    string _target;
    string _duration;
    saveType _savingThrow;
    bool _spellResistance;
    string _description;
};

#endif