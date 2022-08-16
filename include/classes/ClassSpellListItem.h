#include "../enums.h"

/**
 * @brief Holds a \ref casterType "caster class" and a level to represent what \ref Role "classes" can cast a \ref Spell "spell" and at what spell level.
 *
 * Stores the information of one \ref casterType "casting class type" and level. \n
 * The \ref casterType "casting class type" representing what \ref Role "classes" spell list it is in. \n
 * And the level representing what level the \ref Spell "spell" is for that given \ref Role "class". \n
 */
class ClassSpellListItem
{
public:
    // Creates an object that stores what class spell list a Spell is in and at what class level it can be cast with dummy values
    ClassSpellListItem();
    // Creates an object that stores what class spell list a spell is in and at what class level it can be cast with the given values
    ClassSpellListItem(casterType casterType, unsigned short level);

    // Getters
    // Returns the class spell list it is as a caster type
    casterType CasterType();
    // Returns the level it is in the given class spell list
    unsigned short Level();

private:
    casterType _casterType;
    unsigned short _level;
};