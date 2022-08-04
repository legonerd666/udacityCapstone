#ifndef SAVE_H
#define SAVE_H

#include "../enums.h"

class save
{
public:
    save();
    save(saveType saveType, unsigned short base);

    // Getters
    short Total(short abilityMod);
    saveType SaveType();
    abilityType AbilityType();
    unsigned short Base();
    short MagicMod();
    short MiscMod();
    short TempMod();

    // Setters
    //  void Type(saveType newType);
    //  void Base(short newBase);
    //  void MagicMod(short newMagicMod);
    //  void MiscMod(short newMiscMod);

private:
    saveType _type;
    abilityType _abilityType;
    unsigned short _base;
    short _magicMod;
    short _miscMod;
    short _tempMod;
};

#endif