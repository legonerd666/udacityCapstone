#include "Feat.h"

Feat::Feat()
{
    _name = "Example Feat";
    _description = "Example Description";
}

Feat::Feat(string name, string description) : _name(name), _description(description)
{
}

string Feat::Name()
{
    return _name;
}

string Feat::Description()
{
    return _description;
}