#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <vector>
#include <memory>

#include "../enums.h"
#include "ClassSpellListItem.h"

using namespace std;

/**
 * @brief Stores all the details of a \ref Spell "spell" in Pathfinder 1e.
 *
 */
class Spell
{
public:
    // Creates a Spell object with dummy values
    Spell();
    // Creates a Spell object with the provided values
    Spell(string name, magicSchool magicSchool, vector<shared_ptr<ClassSpellListItem>> roles, string castingTime, string components, string range, string target, string duration, string savingThrow, bool spellResistance, string description);

    // Getters
    // Returns the spells' name
    string Name();
    // Returns the spells' magic school
    magicSchool School();
    // Returns the spells' casting class spell list entries
    vector<shared_ptr<ClassSpellListItem>> Roles();
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
    // Returns a bool based on if the Spell is affected by spell resistance
    bool SpellResistance();
    // Returns the spells' description
    string Description();

private:
    string _name;
    magicSchool _school;
    vector<shared_ptr<ClassSpellListItem>> _roles;
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