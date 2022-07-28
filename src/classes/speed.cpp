#include "speed.h"

speed::speed()
{
    _base = 0;
    _baseTempMod = 0;
    _armored = 0;
    _armoredTempMod = 0;
    _fly = 0;
    _flyTempMod = 0;
    _swim = 0;
    _swimTempMod = 0;
    _climb = 0;
    _climbTempMod = 0;
    _burrow = 0;
    _burrowTempMod = 0;
}

speed::speed(unsigned short baseSpeed) : _base(baseSpeed)
{
    _baseTempMod = 0;
    _armored = 0;
    _armoredTempMod = 0;
    _fly = 0;
    _flyTempMod = 0;
    _swim = 0;
    _swimTempMod = 0;
    _climb = 0;
    _climbTempMod = 0;
    _burrow = 0;
    _burrowTempMod = 0;
}

short speed::Base()
{
    return _base;
}

short speed::Armored()
{
    return _armored;
}

short speed::Fly()
{
    return _fly;
}

short speed::Swim()
{
    return _swim;
}

short speed::Climb()
{
    return _climb;
}

short speed::Burrow()
{
    return _burrow;
}