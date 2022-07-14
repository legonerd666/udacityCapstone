#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>

#include "abilityScore.h"
#include "speed.h"
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

class character {
public:
    character();

    //Getters
    string ToString();

    //Setters

    void Name(string newName);
    void Alignment(alignment newAlignment);
    void Player(string newPlayer);
    void Roles(vector<role>&& newRoles);
    void Deity(string newDeity);
    void Homeland(string newHomeland);
    void Race(race&& newRace);
    void Gender(string newGender);
    void Age(short newAge);
    void Height(short newHeight);
    void Weight(short newWeight);
    void HairColor(string newHairColor);
    void EyeColor(string newEyeColor);

    void AbilityScores(vector<abilityScore>&& newAbilityScores);
    void HitPoints(hitPoints&& newHitPoints);
    void Speed(speed&& newSpeed);
    void ArmorClass(armorClass&& newArmorClass);
    void saves(save newSaves [3]);
    void Skills(vector<skill>&& newSkills);
    void Languages(string newLanguages);
    
    void BaseAttackBonus(vector<unsigned short> newBaseAttackBonuses);
    void SpellResistance(short newSpellResistance);
    void Weapons(vector<weapon>&& newWeapons);
    void Proficiencies(string newProficiencies);
    
    void ArmorClassItems(vector<armorClassItem>&& newArmorClassItems);
    void Gear(vector<gear>&& newGear);
    void Currency(vector<currency>&& newCurrency);

    void Feats(vector<feat>&& newFeats);

    void Xp(unsigned int newXp);
    void NextLevelXpAmount(unsigned int newNextLevelXpAmount);
    
private:

    string _name;
    alignment _alignment;
    string _player;
    vector<unique_ptr<role>> _roles;
    string _deity;
    string _homeland;
    unique_ptr<race> _race;
    string _gender;
    short _age;
    short _height;
    short _weight;
    string _hairColor;
    string _eyeColor;

    abilityScore _abilityScores [6];
    unique_ptr<hitPoints> _hitpoints;
    unique_ptr<speed> _speed;
    unique_ptr<armorClass> _armorClass;
    save saves [3];
    vector<unique_ptr<skill>> _skills;
    string _languages;

    vector<unsigned short> _baseAttackBonuses;
    short _spellResistance;
    vector<unique_ptr<weapon>> _weapons;
    string _proficiencies;

    vector<unique_ptr<armorClassItem>> _armorClassItems;
    vector<unique_ptr<gear>> _gear;
    unique_ptr<currency> _currency [4];

    vector<unique_ptr<feat>> _feats;

    unsigned int _xp;
    unsigned int _nextLevelXpAmount;
    
};

#endif