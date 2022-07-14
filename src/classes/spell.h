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

    //Getters
    string ToString();
    vector<string> Roles();

    //Setters
    void School(magicSchool newSchool);
    void Roles(vector<casterType> newCasterTypes);
    void Level(unsigned short newLevel);
    void CastingTime(string newCastingTime);
    void Components(string newComponents);
    void Range(string newRange);
    void Target(string newTarget);
    void Duration(string newDuration);
    void SavingThrow(string newSavingThrow);
    void SpellResistance(string newSpellResistance);
    void Description(string newDescription);

private:
    magicSchool _school;
    vector<casterType> _casterTypes;
    unsigned short _level;
    string _castingTime;
    string _components;
    string _range;
    string _target;
    string _duration;
    string _savingThrow;
    string _spellResistance;
    string _description;

};

#endif