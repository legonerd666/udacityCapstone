#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>

#include "abilityScore.h"
#include "speed.h"
#include "initiative.h"
#include "armorClass.h"
#include "save.h"
#include "skill.h"
#include "weapon.h"
#include "armorClassItem.h"
#include "gear.h"
#include "currency.h"
#include "feat.h"
#include "race.h"
#include "role.h"
#include "hitPoints.h"

#include "../enums.h"

using namespace std;

class character
{
public:
    // Creates a basic character object and initializes its initiative, armor class, one of each of the 35 skills, a default spell resistance, an object for each of the 4 currencies, and default xp at level 1 (0)
    character();

    // Getters
    // Outputs the character data as a nicely formatted dynamic string
    string ToStringForConsole();
    // Returns the score of an ability based on the given type
    short AbilityScore(abilityType abilityType);
    // Returns the adjusted modifier of an ability of the given type
    short AbilityMod(abilityType abilityType);
    // Returns the characters proficiencies
    string Proficiencies();
    // Returns the amount of currency a character has of the given type
    int Currency(currencyType currency);
    // Returns the type of currency at a given index
    currencyType CurrencyType(short index);

    // Setters
    // Initializes the characters ability scores base off of an array of 6 shorts
    void AbilityScores(short newAbilityScores[6]);
    // Initializes the race of a character with the name provided and everything else with dummy or empty values
    void Race(string name);
    // Sets the size of the character to the provided size enum
    void Size(sizeType sizeType);
    // Initializes the characters speed with base and armored speeds set to the given short
    void Speed(short baseSpeed);
    // Sets the characters proficiencies to the given string
    void Proficiencies(string proficiencies);
    // Sets the characters languages to the given string
    void Languages(string languages);
    // Initializes the characters hitpoints with the max value of the given die enum and adds the hitdie to the list of hitdice in the hitpoints object
    void HitPoints(die hitdie);
    // Sets the role at the given index to a casting class with the casting ability score provided
    void SetRoleToCastingClass(short index, abilityType castingAbility);
    // Sets the spells known of the role at the given index at the given level to the short provided
    void SetSpellsKnown(short roleIndex, short spellLevel, short spellsKnown);
    // Sets the spells per day of the role at the given index at the given level to the short provided
    void SetSpellsPerDay(short roleIndex, short spellLevel, short spellsPerDay);
    // Empties the Base Attack Bonuses vector and sets its first value to the given short and any subsequent values to the previous - 5 as long as it would set it to at least 1
    void BaB(unsigned short BaB);
    // Initializes the save at the proper index for the saves type with the save enum and the base save value provided
    void Save(saveType saveType, unsigned short save);
    // Sets the amount of the currency of the given type to the provided int
    void Currency(currencyType currency, int amount);
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
    void AddRacialTrait(shared_ptr<feat> &&racialTrait);
    // Initializes a role with the given name along with all its other values either dummy or empty and then adds it the the vector of the characters roles
    void AddRole(string name);
    // Sets all skills of the given skill type in the characters vector of skills to be a class skill
    void AddClassSkill(skillType skillType);
    // Finds all the skills of the given type and if their ranks are less than 1 adds 1 rank to them, if the skill already has 1 or more ranks the function returns -1 and does not add any ranks
    short AddSkillRankToSkill(skillType skillType);
    // Adds a class feature to the vector of class features in the role at the given index
    void AddClassFeature(short roleIndex, string name, string description);
    // Adds a spell to the vector of spells in the role at the given index
    void AddSpell(short roleIndex, shared_ptr<spell> &&spell);
    // Adds the feat given to the characters vector of feats
    void AddFeat(unique_ptr<feat> &&feat);
    // Adds a gear item to the characters vector of gear
    void AddGear(unique_ptr<gear> &&gear);
    // Adds a weapon to the characters vector of weaponry
    void AddWeapon(unique_ptr<weapon> &&weapon);
    // Adds a armor item to the characters vector of armor items
    void AddArmor(unique_ptr<armorClassItem> &&armor);

private:
    string _name;
    alignment _alignment;
    string _player;
    vector<unique_ptr<role>> _roles;
    string _deity;
    string _homeland;
    unique_ptr<race> _race;
    sizeType _size;
    string _gender;
    short _age;
    short _height;
    short _weight;
    string _hairColor;
    string _eyeColor;

    unique_ptr<hitPoints> _hitpoints;
    unique_ptr<abilityScore> _abilityScores[6];
    unique_ptr<speed> _speed;
    unique_ptr<initiative> _initiative;
    unique_ptr<armorClass> _armorClass;
    unique_ptr<save> _saves[3];
    vector<unique_ptr<skill>> _skills;
    string _languages;

    vector<unsigned short> _baseAttackBonuses;
    short _spellResistance;
    vector<unique_ptr<weapon>> _weapons;
    string _proficiencies;

    vector<unique_ptr<armorClassItem>> _armorClassItems;
    vector<unique_ptr<gear>> _gear;
    unique_ptr<currency> _currency[4];

    vector<unique_ptr<feat>> _feats;

    unsigned int _xp;
    unsigned int _nextLevelXpAmount;

    mutex _mutex;

    short CMB();
    short CMD();
};

#endif