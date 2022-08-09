#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <vector>
#include "enums.h"
#include "classSpellListItem.h"
#include <memory>

using namespace std;

class spell
{
public:
    // Creates a spell object with dummy values
    spell();
    // Creates a spell object with the provided values
    spell(string name, magicSchool magicSchool, vector<shared_ptr<classSpellListItem>> roles, string castingTime, string components, string range, string target, string duration, string savingThrow, bool spellResistance, string description);

    // Getters
    // Returns the spells' name
    string Name();
    // Returns the spells' magic school
    magicSchool School();
    // Returns the spells' casting class spell list entries
    vector<shared_ptr<classSpellListItem>> Roles();
    // Returns the spells' casting time
    string CastingTime();
    // Returns the spells' components
    string Components();
    // Returns the spells' range
    string Range();
    // Returns the spells' targets
    string Target();
    // Returns the spells' duration
    string Duration();
    // Returns the spells' saving throw
    string SavingThrow();
    // Returns a bool based on if the spell is affected by spell resistance
    bool SpellResistance();
    // Returns the spells' description
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
    string _savingThrow;
    bool _spellResistance;
    string _description;
};

#endif