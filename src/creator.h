#ifndef INTRO_H
#define INTRO_H

#include "classes/character.h"
#include "enums.h"

#include <memory>
#include <vector>
#include <thread>

class creator
{
public:
    // Creates a creator object with an empty vector of threads
    creator();
    // Joins all threads in the vector of threads before destructing
    ~creator();
    // Disables a creator and its' threads from being copied
    creator(const creator &) = delete;
    // Disables a creator and its' threads from being copied
    creator &operator=(const creator &) = delete;
    // Moves the vector of threads from the old creator to the new one and clears the old creators' vector
    creator(creator &&oldCreator);
    // Moves the vector of threads from the old creator to the new one and clears the old creators' vector
    creator &operator=(creator &&oldCreator);

    // Prints a short intro to how the creator is going to work to the console and starts character creation by running the ability scores function
    void Intro(shared_ptr<character> character);

    // Adds a short delay before printing a line to the console to make the text print at a readable speed rather than just vomiting out a chunk of text
    void DelayedCout(string &&string);
    // Adds a short delay before printing a line to the console to make the text print at a readable speed rather than just vomiting out a chunk of text and allows you to stop it from adding a newline character
    void DelayedCout(string &&string, bool doNewLine);

private:
    // Gets the characters base ability scores and sends them to the race function
    void AbilityScores(shared_ptr<character> &&character);
    // Takes the ability scores recieved and adjusts them based on user input and starts a thread to set the characters ability scores while it continues to get user input then sets all other stats in character determined by race in threads (size, speed, racial traits, weapon familiarities, and languages) then runs the role function
    void Race(shared_ptr<character> &&character, short abilityScores[6]);
    // Takes user input and sets all role determined stats in the character using worker threads (Hitpoints, class skills, skill ranks, proficiencies, isCastingClass, spellstats, spells, BaB, saves, and class features) and then runs Feats function
    void Role(shared_ptr<character> &&character);
    // Adds any feats the user wants to add using worker threads and then runs equipment
    void Feats(shared_ptr<character> &&character);
    // Takes user input and sets all equipment related stats in the character using worker threads (money, weaponry, armor, and gear) and then runs characteristics
    void Equipment(shared_ptr<character> &&character);
    // Takes user input and sets all characteristics using worker threads (name, alignment, player name, deity, homeland, gender, age, height, weight, hair color, and eye color) then waits for user to click enter before ending the creation process
    void Characteristics(shared_ptr<character> &&character);

    short GetScore(abilityType abilityType);
    short GetScoreAdj(abilityType abilityType);
    sizeType GetSize();
    short GetSpeed();
    void RacialTraits(shared_ptr<character> character);
    void ExtraLanguages(shared_ptr<character> character, string languages);
    die GetHitDie();
    void SetClassSkills(shared_ptr<character> character);
    void CheckClassSkills(shared_ptr<character> character, vector<skillType> skillTypes);
    void SetSkillRanks(shared_ptr<character> character);
    void AddSkillRankToSkill(shared_ptr<character> character, short ranks);
    void IsCastingClass(shared_ptr<character> character);
    abilityType GetCastingAbility(shared_ptr<character> character);
    void SetSpellsKnown(shared_ptr<character> character, short spellLevel);
    void SetSpellsPerDay(shared_ptr<character> character, short spellLevel);
    void AddSpell(shared_ptr<character> character);
    magicSchool GetSchool();
    void GetRoles(vector<shared_ptr<classSpellListItem>> &roles);
    casterType GetCasterType();
    unsigned short GetLevel();
    bool GetSpellResistance();
    unsigned short GetBaB();
    unsigned short GetSave(saveType saveType);
    void AddClassFeatures(shared_ptr<character> character);
    void AddFeat(shared_ptr<character> character);
    void SetGold(shared_ptr<character> character);
    string FormattedCurrencies(shared_ptr<character> character);
    void AddWeapon(shared_ptr<character> character);
    currencyType GetCurrencyType();
    int GetCost();
    int SubtractCost(shared_ptr<character> character, currencyType &&currencyType, int &&cost);
    short GetNDice();
    die GetDie();
    unsigned short GetWeight();
    abilityType GetAbilityType();
    short GetAmmo(shared_ptr<character> character);
    bool WillBuyAmmo();
    short GetAmmoAmount();
    void AddArmor(shared_ptr<character> character);
    void AddGear(shared_ptr<character> character);
    unsigned short GetACBonus();
    unsigned short GetMaxDex();
    short GetCheckPenalty();
    unsigned short GetSpellFailureChance();
    unsigned short GetBaseSpeedAdjustment();
    alignment GetAlignment();
    short GetAge();
    short GetHeight();
    short GetCharacterWeight();

    vector<thread> _threads;
};

#endif