#include "armorClass.h"

armorClass::armorClass()
{
    _armor = 0;
    _shield = 0;
    _naturalArmor = 0;
    _deflectionBonus = 0;
    _miscMod = 0;
}

short armorClass::Total(short dexMod, sizeType sizeType)
{
    return 10 + _armor + _shield + dexMod + EnumToBonus(sizeType) + _naturalArmor + _deflectionBonus + _dodgeBonus + _miscMod;
}

short armorClass::TouchArmorClass(short dexMod, sizeType sizeType)
{
    return 10 + dexMod + EnumToBonus(sizeType) + _deflectionBonus + _dodgeBonus + _miscMod;
}

short armorClass::FlatFootedArmorClass(sizeType sizeType)
{
    return 10 + _armor + _shield + EnumToBonus(sizeType) + _naturalArmor + _deflectionBonus + _miscMod;
}

short armorClass::Armor()
{
    return _armor;
}

short armorClass::Shield()
{
    return _shield;
}

short armorClass::NaturalArmor()
{
    return _naturalArmor;
}

short armorClass::DeflectionBonus()
{
    return _deflectionBonus;
}

short armorClass::DodgeBonus()
{
    return _dodgeBonus;
}

short armorClass::MiscMod()
{
    return _miscMod;
}

void armorClass::Armor(short armor)
{
    _armor = armor;
}

void armorClass::Shield(short shield)
{
    _shield = shield;
}

void armorClass::MiscMod(short miscMod)
{
    _miscMod = miscMod;
}