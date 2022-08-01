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
    character();

    // Getters
    string ToStringForConsole();
    short AbilityMod(abilityType abilityType);

    // Setters

    // void Name(string newName);
    // void Alignment(alignment newAlignment);
    // void Player(string newPlayer);
    // void Roles(vector<unique_ptr<role>>&& newRoles);
    // void Deity(string newDeity);
    // void Homeland(string newHomeland);
    // void Race(unique_ptr<race> newRace);
    // void Gender(string newGender);
    // void Age(short newAge);
    // void Height(short newHeight);
    // void Weight(short newWeight);
    // void HairColor(string newHairColor);
    // void EyeColor(string newEyeColor);

    void AbilityScores(short newAbilityScores[6]);
    void Race(string name);
    void Size(sizeType sizeType);
    void Speed(short baseSpeed);
    void Proficiencies(string proficiencies);
    void Languages(string languages);
    void HitPoints(die hitdie);
    // void HitPoints(unique_ptr<hitPoints> newHitPoints);
    // void Speed(unique_ptr<speed> newSpeed);
    // void ArmorClass(unique_ptr<armorClass> newArmorClass);
    // void saves(unique_ptr<save> newSaves [3]);
    // void Skills(vector<unique_ptr<skill>>&& newSkills);
    // void Languages(string newLanguages);

    // void BaseAttackBonus(vector<unsigned short> newBaseAttackBonuses);
    // void SpellResistance(short newSpellResistance);
    // void Weapons(vector<unique_ptr<weapon>>&& newWeapons);
    // void Proficiencies(string newProficiencies);

    // void ArmorClassItems(vector<unique_ptr<armorClassItem>>&& newArmorClassItems);
    // void Gear(vector<unique_ptr<gear>>&& newGear);
    // void Currency(vector<unique_ptr<currency>>&& newCurrency);

    // void Feats(vector<unique_ptr<feat>>&& newFeats);

    // void Xp(unsigned int newXp);
    // void NextLevelXpAmount(unsigned int newNextLevelXpAmount);

    // Adders
    void AddRacialTrait(shared_ptr<feat> &&racialTrait);
    void AddRole(string name);
    void AddClassSkill(skillType skillType);
    short AddSkillRankToSkill(skillType skillType);

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