#include <string>

#include "race.h"

using namespace std;

race::race()
{
    _name = "Example Race";
}

race::race(string name) : _name(name)
{
}

string race::Name()
{
    return _name;
}

vector<shared_ptr<feat>> race::RacialTraits()
{
    return _racialTraits;
}

void race::AddRacialTrait(shared_ptr<feat> &&racialTrait)
{
    _racialTraits.emplace_back(racialTrait);
}