#include "feat.h"

feat::feat()
{
    _name = "Example Feat";
    _description = "Example Description";
}

feat::feat(string name, string description) : _name(name), _description(description)
{
}

string feat::Name()
{
    return _name;
}

string feat::Description()
{
    return _description;
}