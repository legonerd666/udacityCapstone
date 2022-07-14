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
private:
    string _proficiencies;
    vector<specialAbility> _classFeatures;
    unsigned short _level;
    spellStat spellStats [10];
    vector<spell> spells;
};

#endif