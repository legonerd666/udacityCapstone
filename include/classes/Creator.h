#ifndef CREATOR_H
#define CREATOR_H

#include "Character.h"
#include "enums.h"

#include <memory>
#include <vector>
#include <thread>

/**
 * @brief A class that takes a shared pointer to Character and populates it.
 *
 * This class takes a shared pointer to a Character and gathers user input via the console to fill in all the required Character data.
 */
class Creator
{
public:
    /**
     * @brief Stops users from not providing a Character object to populate.
     *
     * This function is deleted because we want to ensure that Character pointer is passed to the Creator on initialization.
     */
    Creator() = delete;
    /**
     * @brief Construct a new Creator object with Character pointer.
     *
     * Initializes a Creator object with the provided Character as the Character it will populate with data from user input via the console in CreateCharacter().
     * @param character Saved as a member variable which the Creator can then populate with CreateCharacter()
     */
    Creator(shared_ptr<Character> character);
    /**
     * @brief Destroy the Creator object and joins all threads.
     *
     * Destroys the Creator object and joins any remaining threads in _threads.
     */
    ~Creator();
    /**
     * @brief Disables the Creator copy constuctor
     *
     * Explicitly deletes the copy constructor of the Creator class to ensure threads are kept safe and aren't copied.
     */
    Creator(const Creator &) = delete;
    /**
     * @brief Disables the Creator copy assignment operator.
     *
     * Explicitly deletes the copy assignement operator of the Creator class to ensure threads are kept safe and aren't copied.
     */
    Creator &operator=(const Creator &) = delete;
    /**
     * @brief Disables the Creator move constuctor
     *
     * Explicitly deletes the move constructor of the Creator class to ensure threads are kept safe and aren't copied.
     */
    Creator(Creator &&oldCreator) = delete;
    /**
     * @brief Disables the Creator move assignment operator.
     *
     * Explicitly deletes the move assignement operator of the Creator class to ensure threads are kept safe and aren't copied.
     */
    Creator &operator=(Creator &&oldCreator) = delete;

    /**
     * @brief Runs the entire character creator
     *
     * Gathers input from the user via the console, parses the data supplied by the user, and populates the Character object provided. \n
     * It then joins all threads in _threads before returning, to ensure all the character information was filled. \n
     * Calls: \n
     * Intro() \n
     * AbilityScores() \n
     * Race() \n
     * Role() \n
     * Feat() \n
     * Equipment() \n
     * Characteristics() \n
     * Then joins all threads in Creator::_threads
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
     * @brief Prints a short intro about how the Creator is going to work.
     *
     * Prints an intro to the program to the console using DelayedCout().
     */
    void Intro();
    /**
     * @brief Fills the ability scores of the Character.
     *
     * Gives a short explanation of how to generate ability scores in Pathfinder 1e.
     * Gets user input on what each ability score should be.
     * If the user provides nothing it randomly sets each ability score using the Standard Method for generating ability scores.
     * Then sets Character ability scores in the main thread to ensure it is done before the main thread retrieves the ability scores later.
     *
     * Ability Score values are gotten using GetScore().
     *
     * Standard Method: Roll 4d6 and take away the lowest roll. Add up the remaining dice.
     */
    void AbilityScores();
    /**
     * @brief Fills in all information determined by the characters Race.
     *
     * Gathers user input to do the following:
     *
     * Sets the name of the users Race, all the racial ability score modifiers, characters size, Speed, racial traits, languages, and weapon familiarities.
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
     * If the users Character is a spell casting class this function additionally sets the characters spell stats for level 0 and level 1 spells,
     * including determining bonus spells, spell casting ability score, spells in detail which the Character knows,
     * and creates a class feature Spells and fills it with a description on how spells work for the class.
     *
     * For any values entered as blank the program fills them with default values.
     *
     * The characters Race name, hitpoints and hitdice, BaB, Saves, Detailed Spells, and Class Features are all set in worker threads.
     * Everything else is done in the main thread to ensure order of execution.
     */
    void Role();
    /**
     * @brief Sets the characters feats
     *
     * Uses worker threads to set the characters feats with user input.
     * Sets default values to any Feat which isnt provided input.
     */
    void Feats();
    /**
     * @brief Sets characters equipment and gold.
     *
     * Gathers user input to fill out the Character gold, weapons, armor, and Gear.
     *
     * When purchasing a Weapon, adds it to the characters Weapon vector and the characters Gear vector.
     *
     * When purchasing armor, adds it to the characters armorClassItems vector and Gear vector, and adds the armor bonus to the appropriate field in characters ArmorClass attribute.
     *
     * Sets gold in the main thread so that cost is calculated properly for each purchase
     * and auto converts money to the required currency type if a Character doesn't have the required amount of a Currency to purchase the item.
     *
     * Sets weapons, armor, and other Gear in worker threads.
     *
     * Will not let a user purchase an item if they don't have enough money to.
     */
    void Equipment();
    /**
     * @brief Gets the final bits of data to fill out the Character.
     *
     * Gets user input to fill out the characters characteristics.
     *
     * Eg. Alignment, player name, deity, homeland, gender, age, height, weight, hair color, eye color, and the Character name.
     *
     * Sets all of these values in a worker thread and then waits for the user to click \<enter\> one last time before joining the threads and ending creation.
     */
    void Characteristics();

    // Returns short ranging from 3 to 18 to be used as ability scores either one entered by the user or a random one if none was entered
    short GetScore(abilityType abilityType);
    // Returns a short of value 2 or -2 to be used as racial adjustments to ability scores
    short GetScoreAdj(abilityType abilityType);
    // Returns size enum to be used as Character size
    sizeType GetSize();
    // Returns short ranging from 0 to SHRT_MAX to be used as Character base speed
    short GetSpeed();
    // Recurrently adds racial traits to Character until user chooses to stop
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
    // Displays the number of remaining ranks and allows user to input a Skill to place a rank into, if however that Skill already has one it recursively calls this function to allow the user to enter a different Skill
    void AddSkillRankToSkill(short ranks);
    // Sets the characters Role to a casting class with all that that entails if the user wants it to
    void IsCastingClass();
    // Returns the casting ability score the characters Role should use
    abilityType GetCastingAbility();
    // Sets spells known for a given level
    void SetSpellsKnown(short spellLevel);
    // Sets spells per day for a given level
    void SetSpellsPerDay(short spellLevel);
    // Recursively calls itself to add all the characters spells to its' Spell list
    void AddSpell();
    // Returns the desired magic school for a Spell
    magicSchool GetSchool();
    // Populates a vector of classSpellListItems for a Spell
    void GetRoles(vector<shared_ptr<ClassSpellListItem>> &roles);
    // Returns the caster type for GetRoles function
    casterType GetCasterType();
    // Returns the level for GetRoles function
    unsigned short GetLevel();
    // Returns a bool based on if a Spell is affected by spell resistance
    bool GetSpellResistance();
    // Returns an unsigned short to be used as a characters base attack bonus
    unsigned short GetBaB();
    // Returns an unsigned short to used as the base save for a given save type
    unsigned short GetSave(saveType saveType);
    // Recursively adds class features to the Character
    void AddClassFeatures();
    // Recursively adds feats to the Character
    void AddFeat();
    // Sets the characters starting gold
    void SetGold();
    // Returns a formatted string displaying a characters funds for purchasing equipment in the Creator
    string FormattedCurrencies();
    // Recursively adds weapons and Gear items of the Weapon to the Character
    void AddWeapon();
    // Returns a currency type to be used for purchasing in the Creator
    currencyType GetCurrencyType();
    // Returns an int to be used as the cost of an item purchased in the Creator
    int GetCost();
    // Checks if an item is affordable to the user by checking if the user has the required amount of the type of Currency the item costs and if not if if they converted their other currency types to the used currency type they would have sufficient funds, if so it returns 0 and sets the characters new funds as neccesary, if funds are not sufficient Character funds aren't changed and the function returns -1
    int SubtractCost(currencyType &&currencyType, int &&cost);
    // Returns the number of damage dice rolled for a Weapon
    short GetNDice();
    // Returns die enum for die used by a Weapon
    die GetDie();
    // Returns an unsigned short to be used as an items' weight
    unsigned short GetWeight();
    // Returns the ability a weapons attack uses
    abilityType GetAbilityType();
    // Returns a short indicating the amount of ammo the Character has for the Weapon and adds it to Gear
    short GetAmmo();
    // Returns a bool based off if the user would like to purchase ammo for a Weapon
    bool WillBuyAmmo();
    // Returns a short of how much ammo they are buying
    short GetAmmoAmount();
    // Recursively adds armor to the characters armor class items and Gear, and adds to the armor, shield, or miscellaneous bonus to the characters armor class
    void AddArmor();
    // Recursively adds Gear to the Character
    void AddGear();
    // Returns the AC bonus to be used in an armor class item
    unsigned short GetACBonus();
    // Returns the Maximum dexterity bonus allowed by an armor class item when worn
    unsigned short GetMaxDex();
    // Returns the check penalty afforded when wearing an armor class item
    short GetCheckPenalty();
    // Returns the spell failure chance inflicted by wearing an armor class item
    unsigned short GetSpellFailureChance();
    // Returns the Speed adjustment made when wearing an armor class item
    unsigned short GetBaseSpeedAdjustment();
    // Returns an alignment enum to be used as the characters alignment
    alignment GetAlignment();
    // Returns the characters age
    short GetAge();
    // Returns the characters height
    short GetHeight();
    // Returns the characters weight in pounds
    short GetCharacterWeight();

    shared_ptr<Character> _character;
    vector<thread> _threads;
};

#endif