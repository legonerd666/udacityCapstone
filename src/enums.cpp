#include "enums.h"

#include <string>

string EnumToString(alignment alignment){
    switch (alignment) {
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

string EnumToString(die die) {
    switch (die) {
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

string EnumToString(skillType skillType) {
    switch (skillType) {
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

short EnumToIndex(abilityType abilityType) {
    switch (abilityType) {
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

abilityType EnumToAbilityType(skillType skillType) {
    switch (skillType)
    {
    case climb: case swim:
        return strength;
    case acrobatics: case disableDevice: case escapeArtist: case fly: case ride: case sleightOfHand: case stealth:
        return dexterity;
    case appraise: case craft: case knowArcana: case knowDungeoneering: case knowEngineering: case knowGeography: case knowHistory: case knowLocal: case knowNature: case knowNobility: case knowPlanes: case knowReligion: case linguistics: case spellcraft:
        return intelligence;
    case heal: case perception: case profession: case senseMotive: case survival:
        return wisdom;
    case bluff: case diplomacy: case disguise: case handleAnimal: case intimidate: case perform: case useMagicDevice:
        return charisma;
    default:
        return constitution;
    }
}