#ifndef ENUMS_H
#define ENUMS_H

#include <string>

using namespace std;

// Pathfinder 1e alignments
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

// Pathfinder 1e ability scores
enum abilityType
{
    strength,
    dexterity,
    constitution,
    intelligence,
    wisdom,
    charisma
};

// Pathfinder 1e sizes
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

// Pathfinder 1e dice used
enum die
{
    d2,
    d3,
    d4,
    d6,
    d8,
    d10,
    d12,
    d20
};

// Pathfinder 1e saves
enum saveType
{
    fortitude,
    reflex,
    will
};

// Pathfinder 1e skills
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

// Pathfinder 1e currencies
enum currencyType
{
    copper,
    silver,
    gold,
    platinum
};

// Pathfinder 1e schools of magic
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

// Pathfinder 1e casting classes
enum casterType
{
    bard,
    cleric,
    druid,
    paladin,
    ranger,
    sorcererWizard
};

// Pathfinder 1e carried load categories
enum loadType
{
    light,
    mediumLoad,
    heavy,
    incalculable
};

// Returns alignment enum as a string
string EnumToString(alignment alignment);

// Returns ability enum score as a string
string EnumToString(abilityType abilityType);

// Returns size enum as a string
string EnumToString(sizeType sizeType);

// Returns die enum as a string
string EnumToString(die die);

// Returns save enum as a string
string EnumToString(saveType saveType);

// Returns skill enum as a string
string EnumToString(skillType skillType);

// Returns load enum as a string
string EnumToString(loadType loadType);

// Returns currency enum as a string
string EnumToString(currencyType currencyType);

// Returns magic school enum as a string
string EnumToString(magicSchool magicSchool);

// Returns casting class enum as a string
string EnumToString(casterType casterType);

// Returns maximum rollable value of a die enum
short EnumToMax(die die);

// Returns ability score index based off of the ability score type
short EnumToIndex(abilityType abilityType);

// Returns save index based off of the save type
short EnumToIndex(saveType saveType);

// Returns currency index based off of the currency type
short EnumToIndex(currencyType currencyType);

// Returns the ability score tied to a specific save
abilityType EnumToAbilityType(saveType saveType);

// Returns the ability score tied to a specific skill
abilityType EnumToAbilityType(skillType skillType);

// Returns bonus given based off of the size category given
short EnumToBonus(sizeType sizeType);

// Returns load enum based off of a characters strength score and current carried weight
loadType CalcLoad(short strength, unsigned short weight);

// Returns maximum liftable over head load for a Character based off of their strength
short CalcMaxLoad(short strength);

#endif