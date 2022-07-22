#include "gear.h"

gear::gear()
{
    _name = "Example Name";
    _description = "Example Description";
    _weight = 0;
}

gear::gear(string name, string description, unsigned short weight) : _name(name), _description(description), _weight(weight)
{
}

string gear::Name()
{
    return _name;
}

string gear::Description()
{
    return _description;
}

unsigned short gear::Weight()
{
    return _weight;
}