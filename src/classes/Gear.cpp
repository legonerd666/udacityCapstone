#include "Gear.h"

Gear::Gear()
{
    _name = "Example Name";
    _description = "Example Description";
    _weight = 0;
}

Gear::Gear(string name, string description, unsigned short weight) : _name(name), _description(description), _weight(weight)
{
}

string Gear::Name()
{
    return _name;
}

string Gear::Description()
{
    return _description;
}

unsigned short Gear::Weight()
{
    return _weight;
}