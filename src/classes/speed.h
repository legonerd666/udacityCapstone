#ifndef SPEED_H
#define SPEED_H

class speed
{
public:
    speed();

    //Getters
    short Base();
    short Armored();
    short Fly();
    short Swim();
    short Climb();
    short Burrow();

    //Setters 
    void _base(short newBase);
    void _baseTempMod(short newBaseTempMod);
    void _armored(short newArmored);
    void _armoredTempMod(short newArmoredTempMod);
    void _fly(short newFly);
    void _flyTempMod(short newFlyTempMod);
    void _swim(short newSwim);
    void _swimTempMod(short newSwimTempMod);
    void _climb(short newClimb);
    void _climbTempMod(short newClimbTempMod);
    void _burrow(short newBurrow);
    void _burrowTempMod(short newBurrowTempMod);

private:
    short _base;
    short _baseTempMod;
    short _armored;
    short _armoredTempMod;
    short _fly;
    short _flyTempMod;
    short _swim;
    short _swimTempMod;
    short _climb;
    short _climbTempMod;
    short _burrow;
    short _burrowTempMod;
};

#endif