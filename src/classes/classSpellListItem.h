#include "../enums.h"

class classSpellListItem
{
public:
    classSpellListItem();
    classSpellListItem(casterType casterType, unsigned short level);

    // Getters
    casterType CasterType();
    unsigned short Level();

private:
    casterType _casterType;
    unsigned short _level;
};