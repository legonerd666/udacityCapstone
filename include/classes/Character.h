#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>

#include "AbilityScore.h"
#include "Speed.h"
#include "Initiative.h"
#include "ArmorClass.h"
#include "Save.h"
#include "Skill.h"
#include "Weapon.h"
#include "ArmorClassItem.h"
#include "Gear.h"
#include "Currency.h"
#include "Feat.h"
#include "Race.h"
#include "Role.h"
#include "HitPoints.h"

#include "enums.h"

using namespace std;

/**
 * @brief Stores all the information in a character sheet in Pathfinder 1e.
 *
 * This is a composite class of raw types and custom classes that stores all the information on a character sheet in Pathfinder 1e. \n
 * It has functions to return and set different values that are subject to user input and a ToStringForConsole() function which calculates all the values of the
 * sheet and converts it a formatted string to be printed to the console.
 */
class Character
{
public:
    // Creates a basic Character object and initializes its Initiative, armor class, one of each of the 35 skills, a default spell resistance, an object for each of the 4 currencies, and default xp at level 1 (0)
    Character();

    // Getters
    // Outputs the Character data as a nicely formatted dynamic string
    string ToStringForConsole();
    /**
     * @brief Formats the character sheet using html
     * 
     * @return string 
     */
    string ToStringForWeb();
    // Returns the score of an ability based on the given type
    short GetAbilityScore(abilityType abilityType);
    // Returns the adjusted modifier of an ability of the given type
    short AbilityMod(abilityType abilityType);
    // Returns the characters proficiencies
    string Proficiencies();
    // Returns the amount of Currency a Character has of the given type
    int GetCurrencyAmount(currencyType currency);
    // Returns the type of Currency at a given index
    currencyType CurrencyType(short index);

    // Setters
    // Initializes the characters ability scores base off of an array of 6 shorts
    void AbilityScores(short newAbilityScores[6]);
    // Initializes the Race of a Character with the name provided and everything else with dummy or empty values
    void SetRace(string name);
    // Sets the size of the Character to the provided size enum
    void Size(sizeType sizeType);
    // Initializes the characters Speed with base and armored speeds set to the given short
    void SetSpeed(short baseSpeed);
    // Sets the characters proficiencies to the given string
    void Proficiencies(string proficiencies);
    // Sets the characters languages to the given string
    void Languages(string languages);
    // Initializes the characters hitpoints with the max value of the given die enum and adds the hitdie to the list of hitdice in the hitpoints object
    void SetHitPoints(die hitdie);
    // Sets the Role at the given index to a casting class with the casting ability score provided
    void SetRoleToCastingClass(short index, abilityType castingAbility);
    // Sets the spells known of the Role at the given index at the given level to the short provided
    void SetSpellsKnown(short roleIndex, short spellLevel, short spellsKnown);
    // Sets the spells per day of the Role at the given index at the given level to the short provided
    void SetSpellsPerDay(short roleIndex, short spellLevel, short spellsPerDay);
    // Empties the Base Attack Bonuses vector and sets its first value to the given short and any subsequent values to the previous - 5 as long as it would set it to at least 1
    void BaB(unsigned short BaB);
    // Initializes the Save at the proper index for the saves type with the save enum and the base save value provided
    void SetSave(saveType saveType, unsigned short save);
    // Sets the amount of the Currency of the given type to the provided int
    void SetCurrency(currencyType currency, int amount);
    // If the armored speed adjustment is less than the current armored speed it sets the armored speed to the provided unsigned short
    void ArmoredSpeed(unsigned short speed);
    // Adds the provided bonus to the armor class' armor bonus
    void ArmorBonus(short armorBonus);
    // Adds the provided bonus to the armor class' shield bonus
    void ShieldBonus(short shieldBonus);
    // Adds the provided bonus to the armor class' miscellaneous modifier
    void MiscACBonus(short miscBonus);
    // Sets the characters alignment, player name, deity, homeland, gender, age, height, weight, hair color, eye color, and name to the provided values
    void Characteristics(alignment alignment, string playerName, string deity, string homeland, string gender, short age, short height, short weight, string hair, string eyes, string name);

    // Adders
    // Adds the given racial trait to the characters races' vector of racial traits
    void AddRacialTrait(shared_ptr<Feat> &&racialTrait);
    // Initializes a Role with the given name along with all its other values either dummy or empty and then adds it the the vector of the characters roles
    void AddRole(string name);
    // Sets all skills of the given skill type in the characters vector of skills to be a class skill
    void AddClassSkill(skillType skillType);
    // Finds all the skills of the given type and if their ranks are less than 1 adds 1 rank to them, if the skill already has 1 or more ranks the function returns -1 and does not add any ranks
    short AddSkillRankToSkill(skillType skillType);
    // Adds a class feature to the vector of class features in the Role at the given index
    void AddClassFeature(short roleIndex, string name, string description);
    // Adds a Spell to the vector of spells in the Role at the given index
    void AddSpell(short roleIndex, shared_ptr<Spell> &&spell);
    // Adds the Feat given to the characters vector of feats
    void AddFeat(unique_ptr<Feat> &&feat);
    // Adds a Gear item to the characters vector of Gear
    void AddGear(unique_ptr<Gear> &&gear);
    // Adds a Weapon to the characters vector of weaponry
    void AddWeapon(unique_ptr<Weapon> &&weapon);
    // Adds a armor item to the characters vector of armor items
    void AddArmor(unique_ptr<ArmorClassItem> &&armor);

private:
    string _name;
    alignment _alignment;
    string _player;
    vector<unique_ptr<Role>> _roles;
    string _deity;
    string _homeland;
    unique_ptr<Race> _race;
    sizeType _size;
    string _gender;
    short _age;
    short _height;
    short _weight;
    string _hairColor;
    string _eyeColor;

    unique_ptr<HitPoints> _hitpoints;
    unique_ptr<AbilityScore> _abilityScores[6];
    unique_ptr<Speed> _speed;
    unique_ptr<Initiative> _initiative;
    unique_ptr<ArmorClass> _armorClass;
    unique_ptr<Save> _saves[3];
    vector<unique_ptr<Skill>> _skills;
    string _languages;

    vector<unsigned short> _baseAttackBonuses;
    short _spellResistance;
    vector<unique_ptr<Weapon>> _weapons;
    string _proficiencies;

    vector<unique_ptr<ArmorClassItem>> _armorClassItems;
    vector<unique_ptr<Gear>> _gear;
    unique_ptr<Currency> _currency[4];

    vector<unique_ptr<Feat>> _feats;

    unsigned int _xp;
    unsigned int _nextLevelXpAmount;

    mutex _mutex;

    short CMB();
    short CMD();
};

#endif