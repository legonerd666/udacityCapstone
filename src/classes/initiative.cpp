#include "initiative.h"

initiative::initiative() {
    _miscMod = 0;
}

short initiative::Total(short dexMod) {
    return dexMod + _miscMod;
}

short initiative::MiscMod() {
    return _miscMod;
}