#include "role.h"

role::role()
{
    _name = "Example Class";
    _level = 1;
}

string role::Name()
{
    return _name;
}

unsigned short role::Level()
{
    return _level;
}

vector<shared_ptr<feat>> role::ClassFeatures()
{
    return _classFeatures;
}