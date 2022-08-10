#ifndef INTRO_H
#define INTRO_H

#include "character.h"
#include "enums.h"

#include <memory>
#include <vector>
#include <thread>

/**
 * @brief A class that takes a shared pointer to character and populates it.
 *
 * This class takes a shared pointer to a character and gathers user input via the console to fill in all the required character data.
 */
class creator
{
public:
    /**
     * @brief Stops users from not providing a character object to populate.
     *
     * This function is deleted because we want to ensure that character pointer is passed to the creator on initialization.
     */
    creator() = delete;
    /**
     * @brief Construct a new creator object with character pointer.
     *
     * Initializes a creator object with the provided character as the character it will populate with data from user input via the console in CreateCharacter().
     * @param character Saved as a member variable which the creator can then populate with CreateCharacter()
     */
    creator(shared_ptr<character> character);
    /**
     * @brief Destroy the creator object and joins all threads.
     *
     * Destroys the creator object and joins any remaining threads in _threads.
     */
    ~creator();
    /**
     * @brief Disables the creator copy constuctor
     *
     * Explicitly deletes the copy constructor of the creator class to ensure threads are kept safe and aren't copied.
     */
    creator(const creator &) = delete;
    /**
     * @brief Disables the creator copy assignment operator.
     *
     * Explicitly deletes the copy assignement operator of the creator class to ensure threads are kept safe and aren't copied.
     */
    creator &operator=(const creator &) = delete;
    /**
     * @brief Disables the creator move constuctor
     *
     * Explicitly deletes the move constructor of the creator class to ensure threads are kept safe and aren't copied.
     */
    creator(creator &&oldCreator) = delete;
    /**
     * @brief Disables the creator move assignment operator.
     *
     * Explicitly deletes the move assignement operator of the creator class to ensure threads are kept safe and aren't copied.
     */
    creator &operator=(creator &&oldCreator) = delete;

    /**
     * @brief Runs the entire character creator
     *
     * Gathers input from the user via the console, parses the data supplied by the user, and populates the character object provided.
     * It then joins all threads in _threads before returning, to ensure all the character information was filled.
     *
     * Calls:
     * Intro(), AbilityScores(), Race(), Role(), Feats(), Equipment(), and Characteristics() before joining _threads.
     */
    void CreateCharacter();
    /**
     * @brief Adds a short delay before each char printed to the console.
     *
     * Prints string to the console one character at a time with a short delay to make reading it more pleasant and less overwhelming.
     *
     * @param string The string it should print.
     */
    void DelayedCout(string &&string);
    // Prints string to the console one character at a time to make reading it more pleasant and less overwhelming and allows you to choose if you'd like a new line character to be added at the end
    /**
     * @brief Adds a short delay before each char printed to the console.
     *
     * Prints string to the console one character at a time with a short delay to make reading it more pleasant and less overwhelming.
     *
     * @param string The string it should print.
     * @param doNewLine If false does not print a new line after the provided string.
     */
    void DelayedCout(string &&string, bool doNewLine);

private:
    /**
     * @brief Prints a short intro about how the creator is going to work.
     *
     * Prints an intro to the program to the console using DelayedCout().
     */
    void Intro();
    /**
     * @brief Fills the ability scores of the character.
     *
     * Gives a short explanation of how to generate ability scores in Pathfinder 1e.
     * Gets user input on what each ability score should be.
     * If the user provides nothing it randomly sets each ability score using the Standard Method for generating ability scores.
     * Then sets character ability scores in the main thread to ensure it is done before the main thread retrieves the ability scores later.
     *
     * Ability Score values are gotten using GetScore().
     *
     * Standard Method: Roll 4d6 and take away the lowest roll. Add up the remaining dice.
     */
    void AbilityScores();
    /**
     * @brief Fills in all information determined by the characters race.
     *
     * Gathers user input to do the following:
     *
     * Sets the name of the users race, all the racial ability score modifiers, characters size, speed, racial traits, languages, and weapon familiarities.
     *
     * Uses worker threads to set all values except weapon familiarities and ability scores which are set in the main thread to ensure order of execution.
     */
    void Race();
    /**
     * @brief Sets characters' class and all attributes determined by their class in Pathfinder.
     *
     * Gathers user input and uses it to set:
     *
     * Hitpoints and hitdice, class skills, skill ranks and which skills have ranks in them, proficiencies, Base attack bonuses, saves, class features
     * and determines if the user class is a casting class.
     *
     * If the users character is a spell casting class this function additionally sets the characters spell stats for level 0 and level 1 spells,
     * including determining bonus spells, spell casting ability score, spells in detail which the character knows,
     * and creates a class feature Spells and fills it with a description on how spells work for the class.
     *
     * For any values entered as blank the program fills them with default values.
     *
     * The characters race name, hitpoints and hitdice, BaB, Saves, Detailed Spells, and Class Features are all set in worker threads.
     * Everything else is done in the main thread to ensure order of execution.
     */
    void Role();
    /**
     * @brief Sets the characters feats
     *
     * Uses worker threads to set the characters feats with user input.
     * Sets default values to any feat which isnt provided input.
     */
    void Feats();
    /**
     * @brief Sets characters equipment and gold.
     *
     * Gathers user input to fill out the character gold, weapons, armor, and gear.
     *
     * When purchasing a weapon, adds it to the characters weapon vector and the characters gear vector.
     *
     * When purchasing armor, adds it to the characters armorClassItems vector and gear vector, and adds the armor bonus to the appropriate field in characters armorClass attribute.
     *
     * Sets gold in the main thread so that cost is calculated properly for each purchase
     * and auto converts money to the required currency type if a character doesn't have the required amount of a currency to purchase the item.
     *
     * Sets weapons, armor, and other gear in worker threads.
     *
     * Will not let a user purchase an item if they don't have enough money to.
     */
    void Equipment();
    /**
     * @brief Gets the final bits of data to fill out the character.
     *
     * Gets user input to fill out the characters characteristics.
     *
     * Eg. Alignment, player name, deity, homeland, gender, age, height, weight, hair color, eye color, and the character name.
     *
     * Sets all of these values in a worker thread and then waits for the user to click \<enter\> one last time before joining the threads and ending creation.
     */
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