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
    shared_ptr<spellStat> *SpellStats();
    bool IsCastingClass();

private:
    string _name;
    unsigned short _level;
    vector<shared_ptr<feat>> _classFeatures;
    shared_ptr<spellStat> _spellStats[10];
    vector<unique_ptr<spell>> spells;
    bool _isCastingClass;
};

#endif