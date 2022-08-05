#ifndef SPEED_H
#define SPEED_H

class speed
{
public:
    speed();
    speed(unsigned short baseSpeed);

    // Getters
    short Base();
    short Armored();
    short Fly();
    short Swim();
    short Climb();
    short Burrow();

    // Setters
    void Armored(unsigned short newArmored);

private:
    unsigned short _base;
    unsigned short _baseTempMod;
    unsigned short _armored;
    unsigned short _armoredTempMod;
    unsigned short _fly;
    unsigned short _flyTempMod;
    unsigned short _swim;
    unsigned short _swimTempMod;
    unsigned short _climb;
    unsigned short _climbTempMod;
    unsigned short _burrow;
    unsigned short _burrowTempMod;
};

#endif