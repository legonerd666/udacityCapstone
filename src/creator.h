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

    vector<thread> _threads;
};

#endif