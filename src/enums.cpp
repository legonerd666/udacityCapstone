#include "enums.h"

#include <string>

string EnumToString(alignment alignment)
{
    switch (alignment)
    {
    case LG:
        return "LG";
    case NG:
        return "NG";
    case CG:
        return "CG";
    case LN:
        return "LN";
    case TN:
        return "TN";
    case CN:
        return "CN";
    case LE:
        return "LE";
    case NE:
        return "NE";
    case CE:
        return "CE";
    default:
        return "Error: Invalid Alignment Enum";
    }
}

string EnumToString(abilityType abilityType)
{
    switch (abilityType)
    {
    case strength:
        return "Strength";
    case dexterity:
        return "Dexterity";
    case constitution:
        return "Constitution";
    case intelligence:
        return "Intelligence";
    case wisdom:
        return "Wisdom";
    case charisma:
        return "Charisma";
    default:
        return "Invalid Enum abilityType";
    }
}

string EnumToString(sizeType sizeType)
{
    switch (sizeType)
    {
    case colossal:
        return "Colossal";
    case gargantuan:
        return "Gargantuan";
    case huge:
        return "Huge";
    case large:
        return "Large";
    case medium:
        return "Medium";
    case small:
        return "Small";
    case tiny:
        return "Tiny";
    case diminutive:
        return "Diminutive";
    case fine:
        return "Fine";
    default:
        return "Invalid Size Enum";
    }
}

string EnumToString(die die)
{
    switch (die)
    {
    case d2:
        return "d2";
    case d3:
        return "d3";
    case d4:
        return "d4";
    case d6:
        return "d6";
    case d8:
        return "d8";
    case d10:
        return "d10";
    case d12:
        return "d12";
    case d20:
        return "d20";
    default:
        return "Error: Invalid Die Enum";
    }
}

string EnumToString(saveType saveType)
{
    switch (saveType)
    {
    case fortitude:
        return "Fortitude";
    case reflex:
        return "Reflex";
    case will:
        return "Will";
    default:
        return "Error: Invalid Save Enum";
    }
}

string EnumToString(skillType skillType)
{
    switch (skillType)
    {
    case acrobatics:
        return "Acrobatics";
    case appraise:
        return "Appraise";
    case bluff:
        return "Bluff";
    case climb:
        return "Climb";
    case craft:
        return "Craft";
    case diplomacy:
        return "Diplomacy";
    case disableDevice:
        return "Disable Device";
    case disguise:
        return "Disguise";
    case escapeArtist:
        return "Escape Artist";
    case fly:
        return "Fly";
    case handleAnimal:
        return "Handle Animal";
    case heal:
        return "Heal";
    case intimidate:
        return "Intimidate";
    case knowArcana:
        return "Knowledge (Arcana)";
    case knowDungeoneering:
        return "Knowledge (Dungeoneering)";
    case knowEngineering:
        return "Knowledge (Engineering)";
    case knowGeography:
        return "Knowledge (Geography)";
    case knowHistory:
        return "Knowledge (History)";
    case knowLocal:
        return "Knowledge (Local)";
    case knowNature:
        return "Knowledge (Nature)";
    case knowNobility:
        return "Knowledge (Nobility)";
    case knowPlanes:
        return "Knowledge (Planes)";
    case knowReligion:
        return "Knowledge (Religion)";
    case linguistics:
        return "Linguistics";
    case perception:
        return "Perception";
    case perform:
        return "Perform";
    case profession:
        return "Profession";
    case ride:
        return "Ride";
    case senseMotive:
        return "Sense Motive";
    case sleightOfHand:
        return "Sleight of Hand";
    case spellcraft:
        return "Spellcraft";
    case stealth:
        return "Stealth";
    case survival:
        return "Survival";
    case swim:
        return "Swim";
    case useMagicDevice:
        return "Use Magic Device";
    default:
        return "Error: Invalid Skill Enum";
    }
}

string EnumToString(loadType loadType)
{
    switch (loadType)
    {
    case light:
        return "Light";
    case mediumLoad:
        return "Medium";
    case heavy:
        return "Heavy";
    default:
        return "Incalculable";
    }
}

string EnumToString(currencyType currencyType)
{
    switch (currencyType)
    {
    case copper:
        return "Copper";
    case silver:
        return "Silver";
    case gold:
        return "Gold";
    default:
        return "Platinum";
    }
}

string EnumToString(magicSchool magicSchool)
{
    switch (magicSchool)
    {
    case abjuration:
        return "Abjuration";
    case conjuration:
        return "Conjuration";
    case divination:
        return "Divination";
    case enchantment:
        return "Enchantment";
    case evocation:
        return "Evocation";
    case illusion:
        return "Illusion";
    case necromancy:
        return "Necromancy";
    case transmutation:
        return "Transmutation";
    default:
        return "Universal";
    }
}

string EnumToString(casterType casterType)
{
    switch (casterType)
    {
    case bard:
        return "Bard";
    case cleric:
        return "Cleric";
    case druid:
        return "Druid";
    case paladin:
        return "Paladin";
    default:
        return "Sorcerer/Wizard";
    }
}

short EnumToMax(die die)
{
    {
        switch (die)
        {
        case d2:
            return 2;
        case d3:
            return 3;
        case d4:
            return 4;

        case d6:
            return 6;

        case d8:
            return 8;

        case d10:
            return 10;

        case d12:
            return 12;
        default:
            return 20;
        }
    }
}

short EnumToIndex(abilityType abilityType)
{
    switch (abilityType)
    {
    case strength:
        return 0;
    case dexterity:
        return 1;
    case constitution:
        return 2;
    case intelligence:
        return 3;
    case wisdom:
        return 4;
    case charisma:
        return 5;
    default:
        return -1;
    }
}

short EnumToIndex(saveType saveType)
{
    switch (saveType)
    {
    case fortitude:
        return 0;
    case reflex:
        return 1;
    case will:
        return 2;
    default:
        return -1;
    }
}

short EnumToIndex(currencyType currencyType)
{
    switch (currencyType)
    {
    case copper:
        return 0;
    case silver:
        return 1;
    case gold:
        return 2;
    case platinum:
        return 3;
    default:
        return -1;
    }
}

abilityType EnumToAbilityType(saveType saveType)
{
    switch (saveType)
    {
    case fortitude:
        return constitution;
    case reflex:
        return dexterity;
    case will:
        return wisdom;
    default:
        return strength;
    }
}

abilityType EnumToAbilityType(skillType skillType)
{
    switch (skillType)
    {
    case climb:
    case swim:
        return strength;
    case acrobatics:
    case disableDevice:
    case escapeArtist:
    case fly:
    case ride:
    case sleightOfHand:
    case stealth:
        return dexterity;
    case appraise:
    case craft:
    case knowArcana:
    case knowDungeoneering:
    case knowEngineering:
    case knowGeography:
    case knowHistory:
    case knowLocal:
    case knowNature:
    case knowNobility:
    case knowPlanes:
    case knowReligion:
    case linguistics:
    case spellcraft:
        return intelligence;
    case heal:
    case perception:
    case profession:
    case senseMotive:
    case survival:
        return wisdom;
    case bluff:
    case diplomacy:
    case disguise:
    case handleAnimal:
    case intimidate:
    case perform:
    case useMagicDevice:
        return charisma;
    default:
        return constitution;
    }
}

short EnumToBonus(sizeType sizeType)
{
    switch (sizeType)
    {
    case colossal:
        return -8;
    case gargantuan:
        return -4;
    case huge:
        return -2;
    case large:
        return -1;
    case small:
        return 1;
    case tiny:
        return 2;
    case diminutive:
        return 4;
    case fine:
        return 8;
    default:
        return 0;
    }
}

loadType CalcLoad(short strength, unsigned short weight)

{
    switch (strength)
    {
    case 1:
        if (weight <= 3)
        {
            return light;
        }
        else if (weight <= 6)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 2:
        if (weight <= 6)
        {
            return light;
        }
        else if (weight <= 13)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 3:
        if (weight <= 10)
        {
            return light;
        }
        else if (weight <= 20)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 4:
        if (weight <= 13)
        {
            return light;
        }
        else if (weight <= 26)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 5:
        if (weight <= 16)
        {
            return light;
        }
        else if (weight <= 33)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 6:
        if (weight <= 20)
        {
            return light;
        }
        else if (weight <= 40)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 7:
        if (weight <= 23)
        {
            return light;
        }
        else if (weight <= 46)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 8:
        if (weight <= 26)
        {
            return light;
        }
        else if (weight <= 53)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 9:
        if (weight <= 30)
        {
            return light;
        }
        else if (weight <= 60)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 10:
        if (weight <= 33)
        {
            return light;
        }
        else if (weight <= 66)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 11:
        if (weight <= 38)
        {
            return light;
        }
        else if (weight <= 76)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 12:
        if (weight <= 43)
        {
            return light;
        }
        else if (weight <= 86)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 13:
        if (weight <= 50)
        {
            return light;
        }
        else if (weight <= 100)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 14:
        if (weight <= 58)
        {
            return light;
        }
        else if (weight <= 116)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 15:
        if (weight <= 66)
        {
            return light;
        }
        else if (weight <= 133)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 16:
        if (weight <= 76)
        {
            return light;
        }
        else if (weight <= 153)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 17:
        if (weight <= 86)
        {
            return light;
        }
        else if (weight <= 173)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 18:
        if (weight <= 100)
        {
            return light;
        }
        else if (weight <= 200)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 19:
        if (weight <= 116)
        {
            return light;
        }
        else if (weight <= 233)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 20:
        if (weight <= 133)
        {
            return light;
        }
        else if (weight <= 266)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 21:
        if (weight <= 153)
        {
            return light;
        }
        else if (weight <= 306)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 22:
        if (weight <= 173)
        {
            return light;
        }
        else if (weight <= 346)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 23:
        if (weight <= 200)
        {
            return light;
        }
        else if (weight <= 400)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 24:
        if (weight <= 233)
        {
            return light;
        }
        else if (weight <= 466)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 25:
        if (weight <= 266)
        {
            return light;
        }
        else if (weight <= 533)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 26:
        if (weight <= 306)
        {
            return light;
        }
        else if (weight <= 613)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 27:
        if (weight <= 346)
        {
            return light;
        }
        else if (weight <= 693)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 28:
        if (weight <= 400)
        {
            return light;
        }
        else if (weight <= 800)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }
    case 29:
        if (weight <= 466)
        {
            return light;
        }
        else if (weight <= 933)
        {
            return mediumLoad;
        }
        else
        {
            return heavy;
        }

    default:
        return incalculable;
    }
}

short CalcMaxLoad(short strength)
{
    switch (strength)
    {
    case 1:
        return 10;

    case 2:
        return 20;

    case 3:
        return 30;

    case 4:
        return 40;

    case 5:
        return 50;

    case 6:
        return 60;

    case 7:
        return 70;

    case 8:
        return 80;

    case 9:
        return 90;

    case 10:
        return 100;

    case 11:
        return 115;

    case 12:
        return 130;

    case 13:
        return 150;

    case 14:
        return 175;

    case 15:
        return 200;

    case 16:
        return 230;

    case 17:
        return 260;

    case 18:
        return 300;

    case 19:
        return 350;

    case 20:
        return 400;

    case 21:
        return 460;

    case 22:
        return 520;

    case 23:
        return 600;

    case 24:
        return 700;

    case 25:
        return 800;

    case 26:
        return 920;

    case 27:
        return 1040;

    case 28:
        return 1200;

    case 29:
        return 1400;

    default:
        return -1;
    }
}