#ifndef SAVE_H
#define SAVE_H

#include "../enums.h"

/**
 * @brief Stores all information for a \ref Character "characters'" \ref Save "save", such as their \ref fortitude "fortitude" \ref Save "save".
 *
 */
class Save
{
public:
    // Creates a Save object with dummy values
    Save();
    // Creates a Save object with the given type and base and sets the ability type base off of the provided save type enum and sets everything else to 0
    Save(saveType saveType, unsigned short base);

    // Getters
    // Returns the total save bonus based off of the characters appropriate ability score
    short Total(short abilityMod);
    // Returns the saves' type enum
    saveType SaveType();
    // Returns the saves' ability used to calculate the bonus
    abilityType AbilityType();
    // Returns the base save
    unsigned short Base();
    // Returns the saves' magic modifier
    short MagicMod();
    // Returns the saves' miscellaneous modifier
    short MiscMod();
    // Returns the saves' temporary modifier
    short TempMod();

private:
    saveType _type;
    abilityType _abilityType;
    unsigned short _base;
    short _magicMod;
    short _miscMod;
    short _tempMod;
};

#endif