#include "speed.h"

speed::speed() {
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

const short speed::Base() {
    return _base;
}

const short speed::Armored() {
    return _armored;
}

const short speed::Fly() {
    return _fly;
}

const short speed::Swim() {
    return _swim;
}

const short speed::Climb() {
    return _climb;
}

const short speed::Burrow() {
    return _burrow;
}