#ifndef SPEED_H
#define SPEED_H

class Speed
{
public:
    // Creates a speeds object with all values set to 0;
    Speed();
    // Creates a speeds object with everything set to 0 except the base and armored speeds
    Speed(unsigned short baseSpeed);

    // Getters
    // Returns the base speed
    short Base();
    // Returns the armored speed
    short Armored();
    // Returns the fly speed
    short Fly();
    // Returns the swim speed
    short Swim();
    // Returns the climb speed
    short Climb();
    // Returns the burrow speed
    short Burrow();

    // Setters
    // Sets the armored speed
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