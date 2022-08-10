#include "Speed.h"

Speed::Speed()
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

Speed::Speed(unsigned short baseSpeed) : _base(baseSpeed), _armored(baseSpeed)
{
    _baseTempMod = 0;
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

short Speed::Base()
{
    return _base;
}

short Speed::Armored()
{
    return _armored;
}

short Speed::Fly()
{
    return _fly;
}

short Speed::Swim()
{
    return _swim;
}

short Speed::Climb()
{
    return _climb;
}

short Speed::Burrow()
{
    return _burrow;
}

void Speed::Armored(unsigned short speed)
{
    _armored = speed;
}