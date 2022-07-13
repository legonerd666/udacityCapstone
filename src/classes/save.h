#ifndef SAVE_H
#define SAVE_H

#include "../enums.h"

class save {
public:
    save();

    //Getters
    short GetSave(short abilityMod);

    //Setters
    void Type(saveType newType);
    void Base(short newBase);
    void MagicMod(short newMagicMod);
    void MiscMod(short newMiscMod);

private:
    saveType _type;
    short _base;
    short _magicMod;
    short _miscMod;
};

#endif