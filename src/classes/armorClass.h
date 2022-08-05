#ifndef ARMORCLASS_H
#define ARMORCLASS_H

#include "../enums.h"

class armorClass
{
public:
    armorClass();

    // Getters
    short Total(short dexMod, sizeType sizeType);
    short TouchArmorClass(short dexMod, sizeType sizeType);
    short FlatFootedArmorClass(sizeType sizeType);

    short Armor();
    short Shield();
    short NaturalArmor();
    short DeflectionBonus();
    short DodgeBonus();
    short MiscMod();

    // Setters
    void Armor(short newArmor);
    void Shield(short newShield);
    // void NaturalArmor(short newNaturalArmor);
    // void DeflectionMod(short newDeflectionMod);
    void MiscMod(short NewMiscMod);

private:
    short _armor;
    short _shield;
    short _naturalArmor;
    short _deflectionBonus;
    short _dodgeBonus;
    short _miscMod;
};

#endif