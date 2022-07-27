#include "classSpellListItem.h"

classSpellListItem::classSpellListItem()
{
    _casterType = sorcererWizard;
    _level = 0;
}

classSpellListItem::classSpellListItem(casterType casterType, unsigned short level) : _casterType(casterType), _level(level) {}

casterType classSpellListItem::CasterType()
{
    return _casterType;
}

unsigned short classSpellListItem::Level()
{
    return _level;
}