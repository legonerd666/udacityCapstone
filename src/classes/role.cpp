#include "role.h"

role::role() {
    _name = "Example Class";
    _level = 1;
}

string role::ToString() {
    return _name + " " + to_string(_level) + ". ";
}