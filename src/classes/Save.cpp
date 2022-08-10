#include "Save.h"

#include "enums.h"

Save::Save()
{
    _type = fortitude;
    _abilityType = constitution;
    _base = 0;
    _magicMod = 0;
    _miscMod = 0;
    _tempMod = 0;
}

Save::Save(saveType saveType, unsigned short base) : _type(saveType), _base(base)
{
    _abilityType = EnumToAbilityType(saveType);
    _magicMod = 0;
    _miscMod = 0;
    _tempMod = 0;
}

short Save::Total(short abilityMod)
{
    return _base + abilityMod + _magicMod + _miscMod + _tempMod;
}

saveType Save::SaveType()
{
    return _type;
}

abilityType Save::AbilityType()
{
    return _abilityType;
}

unsigned short Save::Base()
{
    return _base;
}

short Save::MagicMod()
{
    return _magicMod;
}

short Save::MiscMod()
{
    return _miscMod;
}

short Save::TempMod()
{
    return _tempMod;
}