#include "ClassSpellListItem.h"

ClassSpellListItem::ClassSpellListItem()
{
    _casterType = sorcererWizard;
    _level = 0;
}

ClassSpellListItem::ClassSpellListItem(casterType casterType, unsigned short level) : _casterType(casterType), _level(level) {}

casterType ClassSpellListItem::CasterType()
{
    return _casterType;
}

unsigned short ClassSpellListItem::Level()
{
    return _level;
}