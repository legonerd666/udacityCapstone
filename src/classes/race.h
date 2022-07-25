#ifndef RACE_H
#define RACE_H

#include <string>
#include <vector>
#include <memory>

#include "feat.h"

using namespace std;

class race
{
public:
    race();

    // Getters
    string Name();
    vector<shared_ptr<feat>> RacialTraits();

    // Setters
    // void Name(string newName);
    // void RacialAblities(vector<unique_ptr<specialAbility>>&& newRacialAbilities);
private:
    string _name;
    vector<shared_ptr<feat>> _racialTraits;
};

#endif