#include <string>

#include "Race.h"

using namespace std;

Race::Race()
{
    _name = "Example Race";
}

Race::Race(string name) : _name(name)
{
}

string Race::Name()
{
    return _name;
}

vector<shared_ptr<Feat>> Race::RacialTraits()
{
    return _racialTraits;
}

void Race::AddRacialTrait(shared_ptr<Feat> &&racialTrait)
{
    _racialTraits.emplace_back(racialTrait);
}