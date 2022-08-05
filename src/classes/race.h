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
    race(string name);

    // Getters
    string Name();
    vector<shared_ptr<feat>> RacialTraits();

    // Adders
    void AddRacialTrait(shared_ptr<feat> &&racialTrait);

private:
    string _name;
    vector<shared_ptr<feat>> _racialTraits;
};

#endif