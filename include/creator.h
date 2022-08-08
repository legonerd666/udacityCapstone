#ifndef INTRO_H
#define INTRO_H

#include "character.h"
#include "enums.h"

#include <memory>
#include <vector>
#include <thread>

class creator
{
public:
    // Stops users from not providing a character object to populate
    creator() = delete;
    // Initializes a creator object with the provided character as the character it will edit
    creator(shared_ptr<character> character);
    // Joins all threads in the vector of threads before destructing
    ~creator();
    // Disables a creator and its' threads from being copied
    creator(const creator &) = delete;
    // Disables a creator and its' threads from being copied
    creator &operator=(const creator &) = delete;
    // Disables moving a creator object
    creator(creator &&oldCreator) = delete;
    // Disables moving a creator object
    creator &operator=(creator &&oldCreator) = delete;

    // Gets user input from the console to set the variables of the provided character
    void CreateCharacter();

    // Prints string to the console one character at a time to make reading it more pleasant and less overwhelming
    void DelayedCout(string &&string);
    // Prints string to the console one character at a time to make reading it more pleasant and less overwhelming and allows you to choose if you'd like a new line character to be added at the end
    void DelayedCout(string &&string, bool doNewLine);

private:
    // Prints a short intro to how the creator is going to work to the console and starts character creation by running the ability scores function
    void Intro();
    // Gets the characters base ability scores and sets them
    void AbilityScores();
    // Gets the ability scores from the character and adjusts them based on user input and gets user input then sets all other stats in character determined by race in threads (size, speed, racial traits, and languages), weapon familiarities however are not set in a worker thread as they are referenced in role and the execution order must be guaranteed
    void Race();
    // Takes user input and sets all role determined stats in the character using worker threads (Hitpoints, class skills, skill ranks, proficiencies, isCastingClass, spellstats, spells, BaB, saves, and class features)
    void Role();
    // Adds any feats the user wants to add using worker threads
    void Feats();
    // Takes user input and sets all equipment related stats in the character using worker threads (money, weaponry, armor, and gear)
    void Equipment();
    // Takes user input and sets all characteristics using worker threads (name, alignment, player name, deity, homeland, gender, age, height, weight, hair color, and eye color) then waits for user to click enter before ending the creation process
    void Characteristics();

    // Returns short ranging from 3 to 18 to be used as ability scores either one entered by the user or a random one if none was entered
    short GetScore(abilityType abilityType);
    // Returns a short of value 2 or -2 to be used as racial adjustments to ability scores
    short GetScoreAdj(abilityType abilityType);
    // Returns size enum to be used as character size
    sizeType GetSize();
    // Returns short ranging from 0 to SHRT_MAX to be used as character base speed
    short GetSpeed();
    // Recurrently adds racial traits to character until user chooses to stop
    void RacialTraits();
    // Uses a for loop to add languages to inputted languages based on characters intelligence modifier
    void ExtraLanguages(string languages);
    // Returns a die enum of d6, d8, d10, or d12 to be used as characters hitdie
    die GetHitDie();
    // Takes string and finds all skills listed in them and send them to the ChechClassSkills function to be verified
    void SetClassSkills();
    // Checks list of skills provided by SetClassSkills and if it's correct sets characters class skills to said list
    void CheckClassSkills(vector<skillType> skillTypes);
    // Uses a for loop to call AddSkillRankToSkill after getting the amount of ranks to use and ensuring the amount is less than 35 (which would cause an infinite loop)
    void SetSkillRanks();
    // Displays the number of remaining ranks and allows user to input a skill to place a rank into, if however that skill already has one it recursively calls this function to allow the user to enter a different skill
    void AddSkillRankToSkill(short ranks);
    // Sets the characters role to a casting class with all that that entails if the user wants it to
    void IsCastingClass();
    // Returns the casting ability score the characters role should use
    abilityType GetCastingAbility();
    // Sets spells known for a given level
    void SetSpellsKnown(short spellLevel);
    // Sets spell per day for a given level
    void SetSpellsPerDay(short spellLevel);
    // Recursively calls itself to add all the characters spells to its' spell list
    void AddSpell();
    // Returns the desired magic school for a spell
    magicSchool GetSchool();
    // Populates a vector of classSpellListItems for a spell
    void GetRoles(vector<shared_ptr<classSpellListItem>> &roles);
    // Returns the caster type for GetRoles function
    casterType GetCasterType();
    // Returns the level for GetRoles function
    unsigned short GetLevel();
    // Returns a bool based on if a spell is affected by spell resistance
    bool GetSpellResistance();
    // Returns an unsigned short to be used as a characters base attack bonus
    unsigned short GetBaB();
    // Returns an unsigned short to used as the base save for a given save type
    unsigned short GetSave(saveType saveType);
    // Recursively adds class features to the character
    void AddClassFeatures();
    // Recursively adds feats to the character
    void AddFeat();
    // Sets the characters starting gold
    void SetGold();
    // Returns a formatted string displaying a characters funds for purchasing equipment in the creator
    string FormattedCurrencies();
    // Recursively adds weapons and gear items of the weapon to the character
    void AddWeapon();
    // Returns a currency type to be used for purchasing in the creator
    currencyType GetCurrencyType();
    // Returns an int to be used as the cost of an item purchased in the creator
    int GetCost();
    // Checks if an item is affordable to the user by checking if the user has the required amount of the type of currency the item costs and if not if if they converted their other currency types to the used currency type they would have sufficient funds, if so it returns 0 and sets the characters new funds as neccesary, if funds are not sufficient character funds aren't changed and the function returns -1
    int SubtractCost(currencyType &&currencyType, int &&cost);
    // Returns the number of damage dice rolled for a weapon
    short GetNDice();
    // Returns die enum for die used by a weapon
    die GetDie();
    // Returns an unsigned short to be used as an items' weight
    unsigned short GetWeight();
    // Returns the ability a weapons attack uses
    abilityType GetAbilityType();
    // Returns a short indicating the amount of ammo the character has for the weapon and adds it to gear
    short GetAmmo();
    // Returns a bool based off if the user would like to purchase ammo for a weapon
    bool WillBuyAmmo();
    // Returns a short of how much ammo they are buying
    short GetAmmoAmount();
    // Recursively adds armor to the characters armor class items and gear, and adds to the armor, shield, or miscellaneous bonus to the characters armor class
    void AddArmor();
    // Recursively adds gear to the character
    void AddGear();
    // Returns the AC bonus to be used in an armor class item
    unsigned short GetACBonus();
    // Returns the Maximum dexterity bonus allowed by an armor class item when worn
    unsigned short GetMaxDex();
    // Returns the check penalty afforded when wearing an armor class item
    short GetCheckPenalty();
    // Returns the spell failure chance inflicted by wearing an armor class item
    unsigned short GetSpellFailureChance();
    // Returns the speed adjustment made when wearing an armor class item
    unsigned short GetBaseSpeedAdjustment();
    // Returns an alignment enum to be used as the characters alignment
    alignment GetAlignment();
    // Returns the characters age
    short GetAge();
    // Returns the characters height
    short GetHeight();
    // Returns the characters weight in pounds
    short GetCharacterWeight();

    shared_ptr<character> _character;
    vector<thread> _threads;
};

#endif