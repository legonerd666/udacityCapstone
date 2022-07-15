#include <string>

#include "race.h"

using namespace std;

race::race(){
    _name = "Example Race";
}

string race::ToString() {
    return _name;
}