#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <vector>
#include <memory>

#include "feat.h"
#include "spell.h"
#include "spellStat.h"

using namespace std;

class role
{
public:
    role();
    role(string name);

    // Getters
    string Name();
    unsigned short Level();
    vector<shared_ptr<feat>> ClassFeatures();
    shared_ptr<spellStat> *SpellStats();
    vector<shared_ptr<spell>> Spells();
    bool IsCastingClass();

    // Setters
    void SetToCastingClass(abilityType castingAbility, short castingAbilityMod);

private:
    string _name;
    unsigned short _level;
    vector<shared_ptr<feat>> _classFeatures;
    shared_ptr<spellStat> _spellStats[10];
    vector<shared_ptr<spell>> _spells;
    bool _isCastingClass;
};

#endif