#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <vector>
#include <memory>

#include "specialAbility.h"
#include "spell.h"
#include "spellStat.h"

using namespace std;

class role
{
public:
    role();

    //Getters
    string ToString();

    //Setters
    // void Proficiencies(string newProficiencies);
    // void ClassFeatures(vector<unique_ptr<specialAbility>>&& newClassFeatures);
    // void Level(unsigned short newLevel);
    // void SpellStats(unique_ptr<spellStat> newSpellStats [10]);
    // void Spells(vector<unique_ptr<spell>>&& spells);

private:
    string _name;
    string _proficiencies;
    vector<unique_ptr<specialAbility>> _classFeatures;
    unsigned short _level;
    unique_ptr<spellStat> spellStats [10];
    vector<unique_ptr<spell>> spells;
};

#endif