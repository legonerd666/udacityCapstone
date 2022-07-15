#ifndef SPEED_H
#define SPEED_H

class speed
{
public:
    speed();

    //Getters
    // short Base();
    // short Armored();
    // short Fly();
    // short Swim();
    // short Climb();
    // short Burrow();

    //Setters 
    // void Base(unsigned short newBase);
    // void BaseTempMod(unsigned short newBaseTempMod);
    // void Armored(unsigned short newArmored);
    // void ArmoredTempMod(unsigned short newArmoredTempMod);
    // void Fly(unsigned short newFly);
    // void FlyTempMod(unsigned short newFlyTempMod);
    // void Swim(unsigned short newSwim);
    // void SwimTempMod(unsigned short newSwimTempMod);
    // void Climb(unsigned short newClimb);
    // void ClimbTempMod(unsigned short newClimbTempMod);
    // void Burrow(unsigned short newBurrow);
    // void BurrowTempMod(unsigned short newBurrowTempMod);

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