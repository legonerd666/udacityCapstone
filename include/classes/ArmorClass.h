#ifndef ARMORCLASS_H
#define ARMORCLASS_H

#include "enums.h"

class ArmorClass
{
public:
    // Creates an armorclass object with all the values set to 0
    ArmorClass();

    // Getters
    // Returns the total armor class based off the stored values, the characters dexterity modifier, and size modifier, + 10
    short Total(short dexMod, sizeType sizeType);
    // Returns the characters armor class based off of the characters dexterity, size, and all the stored stats except for armor, shields, and natural armor, + 10
    short TouchArmorClass(short dexMod, sizeType sizeType);
    // Returns the characters armor class based off all the stored stats and size, + 10, not taking into account dexterity or dodge bonuses
    short FlatFootedArmorClass(sizeType sizeType);

    // Returns the characters armor bonus
    short Armor();
    // Returns the characters shield bonus
    short Shield();
    // Returns the characters natural armor bonus
    short NaturalArmor();
    // Returns the characters deflection bonus
    short DeflectionBonus();
    // Returns the characters dodge bonus
    short DodgeBonus();
    // Returns the characters miscellaneous bonus
    short MiscMod();

    // Setters
    // Sets the armor bonus to the given short
    void Armor(short newArmor);
    // Sets the shield bonus to the given short
    void Shield(short newShield);
    // Sets the miscellaneous bonus to the given short
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