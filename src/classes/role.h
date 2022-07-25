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

    // Getters
    string Name();
    unsigned short Level();
    vector<shared_ptr<feat>> ClassFeatures();

    // Setters
    //  void Proficiencies(string newProficiencies);
    //  void ClassFeatures(vector<unique_ptr<specialAbility>>&& newClassFeatures);
    //  void Level(unsigned short newLevel);
    //  void SpellStats(unique_ptr<spellStat> newSpellStats [10]);
    //  void Spells(vector<unique_ptr<spell>>&& spells);

private:
    string _name;
    unsigned short _level;
    vector<shared_ptr<feat>> _classFeatures;
    unique_ptr<spellStat> spellStats[10];
    vector<unique_ptr<spell>> spells;
};

#endif