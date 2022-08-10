#include "Initiative.h"

Initiative::Initiative()
{
    _miscMod = 0;
}

short Initiative::Total(short dexMod)
{
    return dexMod + _miscMod;
}

short Initiative::MiscMod()
{
    return _miscMod;
}