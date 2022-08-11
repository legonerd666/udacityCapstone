#ifndef RACE_H
#define RACE_H

#include <string>
#include <vector>
#include <memory>

#include "Feat.h"

using namespace std;

/**
 * @brief Stores all information pertaining to a \ref Character "characters'" \ref Race "race".
 *
 */
class Race
{
public:
    // Creates a Race object with a dummy name and everything else empty
    Race();
    // Creates a Race object with the given name and an empty vector of racial traits
    Race(string name);

    // Getters
    // Returns the name of the Race
    string Name();
    // Returns the races' vector of racial traits
    vector<shared_ptr<Feat>> RacialTraits();

    // Adders
    // Adds a racial trait to the vector of racial traits
    void AddRacialTrait(shared_ptr<Feat> &&racialTrait);

private:
    string _name;
    vector<shared_ptr<Feat>> _racialTraits;
};

#endif