#ifndef INITIATIVE_H
#define INITIATIVE_H

/**
 * @brief Stores and calculates a \ref Character "characters'" \ref Initiative "initiative".
 *
 */
class Initiative
{
public:
    // Creates an Initiative object with its values set to 0
    Initiative();

    // Getters
    //  Returns the total initiative bonus based off the characters dexterity modifier
    short Total(short dexMod);
    // Returns the miscellaneous modifier to Initiative
    short MiscMod();

private:
    short _miscMod;
};

#endif