#include "save.h"

#include "enums.h"

save::save()
{
    _type = fortitude;
    _abilityType = constitution;
    _base = 0;
    _magicMod = 0;
    _miscMod = 0;
    _tempMod = 0;
}

save::save(saveType saveType, unsigned short base) : _type(saveType), _base(base)
{
    _abilityType = EnumToAbilityType(saveType);
    _magicMod = 0;
    _miscMod = 0;
    _tempMod = 0;
}

short save::Total(short abilityMod)
{
    return _base + abilityMod + _magicMod + _miscMod + _tempMod;
}

saveType save::SaveType()
{
    return _type;
}

abilityType save::AbilityType()
{
    return _abilityType;
}

unsigned short save::Base()
{
    return _base;
}

short save::MagicMod()
{
    return _magicMod;
}

short save::MiscMod()
{
    return _miscMod;
}

short save::TempMod()
{
    return _tempMod;
}