#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <vector>
#include "../enums.h"

using namespace std;

class spell
{
public:
    spell();

    // Getters
    string Name();
    magicSchool School();
    vector<casterType> Roles();
    unsigned short Level();
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
    vector<casterType> _casterTypes;
    unsigned short _level;
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