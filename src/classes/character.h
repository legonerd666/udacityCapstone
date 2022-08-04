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
    string Proficiencies();
    int Currency(currencyType currency);

    // Setters
    void AbilityScores(short newAbilityScores[6]);
    void Race(string name);
    void Size(sizeType sizeType);
    void Speed(short baseSpeed);
    void Proficiencies(string proficiencies);
    void Languages(string languages);
    void HitPoints(die hitdie);
    void SetRoleToCastingClass(short index, abilityType castingAbility);
    void SetSpellsKnown(short roleIndex, short spellLevel, short spellsKnown);
    void SetSpellsPerDay(short roleIndex, short spellLevel, short spellsPerDay);
    void BaB(unsigned short BaB);
    void Save(saveType saveType, unsigned short save);
    void Currency(currencyType currency, int amount);

    // Adders
    void AddRacialTrait(shared_ptr<feat> &&racialTrait);
    void AddRole(string name);
    void AddClassSkill(skillType skillType);
    short AddSkillRankToSkill(skillType skillType);
    void AddClassFeature(short roleIndex, string name, string description);
    void AddSpell(short roleIndex, shared_ptr<spell> &&spell);
    void AddFeat(unique_ptr<feat> &&feat);

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