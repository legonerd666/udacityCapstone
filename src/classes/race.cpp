#include <string>

#include "race.h"

using namespace std;

race::race()
{
    _name = "Example Race";
}

string race::Name()
{
    return _name;
}

vector<shared_ptr<feat>> race::RacialTraits()
{
    return _racialTraits;
}