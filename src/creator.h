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
    creator();
    ~creator();

    void Intro(shared_ptr<character> character);

    void DelayedCout(string &&string);
    void DelayedCout(string &&string, bool doNewLine);

private:
    void AbilityScores(shared_ptr<character> &&character);
    void Race(shared_ptr<character> &&character, short abilityScores[6]);
    void Role(shared_ptr<character> &&character);
    void Feats(shared_ptr<character> &&character);
    void Equipment(shared_ptr<character> &&character);

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

    vector<thread> _threads;
};

#endif