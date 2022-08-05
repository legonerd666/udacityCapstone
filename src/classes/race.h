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
    // Creates a race object with a dummy name and everything else empty
    race();
    // Creates a race object with the given name and an empty vector of racial traits
    race(string name);

    // Getters
    // Returns the name of the race
    string Name();
    // Returns the races' vector of racial traits
    vector<shared_ptr<feat>> RacialTraits();

    // Adders
    // Adds a racial trait to the vector of racial traits
    void AddRacialTrait(shared_ptr<feat> &&racialTrait);

private:
    string _name;
    vector<shared_ptr<feat>> _racialTraits;
};

#endif