#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "abilityScore.h"
#include "speed.h"
#include "armorClass.h"
#include "save.h"
#include "skill.h"
#include "weapon.h"
#include "armorClassItem.h"
#include "gear.h"
#include "currency.h"

#include "../enums.h"

using namespace std;

class character {
public:
    character();

    void Name(string newName);
    void Alignment(alignment newAlignment);
    void Player(string newPlayer);
    void Deity(string newDeity);
    void Homeland(string newHomeland);
    void Gender(string newGender);
    void Age(short newAge);
    void Height(short newHeight);
    void Weight(short newWeight);
    void HairColor(string newHairColor);
    void EyeColor(string newEyeColor);
    void fortitudeSave(short newFortitudeSave);
    void reflexSave(short newReflexSave);
    void willSave(short newWillSave);
    void baseAttackBonus(short newBaseAttackBonus);
    void spellResistance(short newSpellResistance);
    void xp(int newXp);
    void nextLevelAmount(int newNextLevelXpAmount);
    
private:

    string _name;
    alignment _alignment;
    string _player;
    vector<string> _roles; //Needs Class Def
    string _deity;
    string _homeland;
    string _race; //Needs Class Def
    string _gender;
    short _age;
    short _height;
    short _weight;
    string _hairColor;
    string _eyeColor;

    abilityScore _abilityScores [6];
    int _hitpoints;
    speed _speed;
    armorClass _armorClass;
    save saves [3];
    vector<skill> _skills;
    vector<string> _languages;

    short _baseAttackBonus;
    short _spellResistance;
    vector<weapon> _weapons;

    vector<armorClassItem> _armorClassItems;
    vector<gear> _gear;
    currency _currency [4];

    vector<string> _feats; //Needs Class Def
    vector<string> _specialAbilities; //Needs Class Def

    int _xp;
    int _nextLevelXpAmount;

    vector<string> _spells; //Needs Class Def
    vector<string> _spellsKnown; //Needs Class Def
    
};

#endif