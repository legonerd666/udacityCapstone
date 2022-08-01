#ifndef ENUMS_H
#define ENUMS_H

#include <string>

using namespace std;

enum alignment
{
    LG,
    NG,
    CG,
    LN,
    TN,
    CN,
    LE,
    NE,
    CE
};

enum abilityType
{
    strength,
    dexterity,
    constitution,
    intelligence,
    wisdom,
    charisma
};

enum sizeType
{
    fine,
    diminutive,
    tiny,
    small,
    medium,
    large,
    huge,
    gargantuan,
    colossal
};

enum die
{
    d4,
    d6,
    d8,
    d10,
    d12,
    d20
};

enum saveType
{
    fortitude,
    reflex,
    will
};

enum skillType
{
    acrobatics,
    appraise,
    bluff,
    climb,
    craft,
    diplomacy,
    disableDevice,
    disguise,
    escapeArtist,
    fly,
    handleAnimal,
    heal,
    intimidate,
    knowArcana,
    knowDungeoneering,
    knowEngineering,
    knowGeography,
    knowHistory,
    knowLocal,
    knowNature,
    knowNobility,
    knowPlanes,
    knowReligion,
    linguistics,
    perception,
    perform,
    profession,
    ride,
    senseMotive,
    sleightOfHand,
    spellcraft,
    stealth,
    survival,
    swim,
    useMagicDevice
};

enum currencyType
{
    copper,
    silver,
    gold,
    platinum
};

enum magicSchool
{
    abjuration,
    conjuration,
    divination,
    enchantment,
    evocation,
    illusion,
    necromancy,
    transmutation,
    universal
};

enum casterType
{
    bard,
    cleric,
    druid,
    paladin,
    sorcererWizard
};

enum loadType
{
    light,
    mediumLoad,
    heavy,
    incalculable
};

string EnumToString(alignment alignment);

string EnumToString(abilityType abilityType);

string EnumToString(sizeType sizeType);

string EnumToString(die die);

string EnumToString(saveType saveType);

string EnumToString(skillType skillType);

string EnumToString(loadType loadType);

string EnumToString(currencyType currencyType);

string EnumToString(magicSchool magicSchool);

string EnumToString(casterType casterType);

short EnumToMax(die die);

short EnumToIndex(abilityType abilityType);

abilityType EnumToAbilityType(saveType saveType);

abilityType EnumToAbilityType(skillType skillType);

short EnumToBonus(sizeType sizeType);

loadType CalcLoad(short strength, unsigned short weight);

short CalcMaxLoad(short strength);

#endif