#include "enums.h"

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