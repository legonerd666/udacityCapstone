#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "abilityScore.h"
#include "speed.h"
#include "armorClass.h"

using namespace std;

enum alignment {LG, NG, CG, LN, TN, CN, LE, NE, CE};

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
    short _fortitudeSave;
    short _reflexSave;
    short _willSave;
    vector<string> _skills; //Needs Class Def
    vector<string> _languages;

    short _baseAttackBonus;
    short _spellResistance;
    vector<string> _weapons; //Needs Class Def

    vector<string> _armorClassItems; //Needs Class Def
    vector<string> _gear; //Needs Class Def
    vector<string> _money; //Needs Class Def

    vector<string> _feats; //Needs Class Def
    vector<string> _specialAbilities; //Needs Class Def

    int _xp;
    int _nextLevelXpAmount;

    vector<string> _spells; //Needs Class Def
    vector<string> _spellsKnown; //Needs Class Def
    
};

#endif