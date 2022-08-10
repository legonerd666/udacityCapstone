#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <vector>
#include <memory>

#include "Feat.h"
#include "Spell.h"
#include "SpellStat.h"

using namespace std;

class Role
{
public:
    // Creates a Role object with a dummy name and level and leaves everything else uninitialized
    Role();
    // Creates a Role object with the given name, level 1, and leaves everything else uninitialized
    Role(string name);

    // Getters
    // Returns the roles' name
    string Name();
    // Returns the roles' level
    unsigned short Level();
    // Returns a vector of the roles' class features
    vector<shared_ptr<Feat>> ClassFeatures();
    // Returns the array of the roles' spell stats
    shared_ptr<SpellStat> *SpellStats();
    // Returns a vector of the roles' spells
    vector<shared_ptr<Spell>> Spells();
    // Returns if the Role is a casting class
    bool IsCastingClass();

    // Setters
    // Marks the Role as a casting class and initializes its' bonus spells based on its' casting ability scores modifier
    void SetToCastingClass(abilityType castingAbility, short castingAbilityMod);

    // Adders (not the snake kind)
    // Initializes a class feature with the given values and adds it to the vector of class features
    void AddClassFeature(string name, string description);
    // Adds the provided spell object to the vector of spells
    void AddSpell(shared_ptr<Spell> &&spell);

private:
    string _name;
    unsigned short _level;
    vector<shared_ptr<Feat>> _classFeatures;
    shared_ptr<SpellStat> _spellStats[10];
    vector<shared_ptr<Spell>> _spells;
    bool _isCastingClass;
};

#endif