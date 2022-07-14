#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <vector>

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
    void Proficiencies(string newProficiencies);
    void ClassFeatures(vector<specialAbility>&& newClassFeatures);
    void Level(unsigned short newLevel);
    void SpellStats(spellStat newSpellStats [10]);
    void Spells(vector<spell>&& spells);

private:
    string _proficiencies;
    vector<unique_ptr<specialAbility>> _classFeatures;
    unsigned short _level;
    spellStat spellStats [10];
    vector<unique_ptr<spell>> spells;
};

#endif