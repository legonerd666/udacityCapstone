#include "ArmorClass.h"

ArmorClass::ArmorClass()
{
    _armor = 0;
    _shield = 0;
    _naturalArmor = 0;
    _deflectionBonus = 0;
    _miscMod = 0;
}

short ArmorClass::Total(short dexMod, sizeType sizeType)
{
    return 10 + _armor + _shield + dexMod + EnumToBonus(sizeType) + _naturalArmor + _deflectionBonus + _dodgeBonus + _miscMod;
}

short ArmorClass::TouchArmorClass(short dexMod, sizeType sizeType)
{
    return 10 + dexMod + EnumToBonus(sizeType) + _deflectionBonus + _dodgeBonus + _miscMod;
}

short ArmorClass::FlatFootedArmorClass(sizeType sizeType)
{
    return 10 + _armor + _shield + EnumToBonus(sizeType) + _naturalArmor + _deflectionBonus + _miscMod;
}

short ArmorClass::Armor()
{
    return _armor;
}

short ArmorClass::Shield()
{
    return _shield;
}

short ArmorClass::NaturalArmor()
{
    return _naturalArmor;
}

short ArmorClass::DeflectionBonus()
{
    return _deflectionBonus;
}

short ArmorClass::DodgeBonus()
{
    return _dodgeBonus;
}

short ArmorClass::MiscMod()
{
    return _miscMod;
}

void ArmorClass::Armor(short armor)
{
    _armor = armor;
}

void ArmorClass::Shield(short shield)
{
    _shield = shield;
}

void ArmorClass::MiscMod(short miscMod)
{
    _miscMod = miscMod;
}