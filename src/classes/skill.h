#ifndef SKILL_H
#define SKILL_H

#include "../enums.h"

class skill
{
public:
    //skill();

    skill(skillType skillType);

    //Getters
    const short Total(short abilityMod);
    const skillType SkillType();
    const abilityType AbilityType();
    const short Ranks();
    const short MiscMod();
    const bool IsClassSkill();

    //Setters
    //void SkillType(skillType newSkillType);
    //void AbilityType(abilityType newAbilityType);
    //void Ranks(short newRanks);
    //void MiscMod(short newMiscMod);
    //void IsClassSkill(bool newIsClassSkill);
    //void IsTrainedOnly(bool newIsTrainedOnly);

private:
    skillType _skillType;
    abilityType _abilityType;
    short _ranks;
    short _miscMod;
    bool _isClassSkill;
    bool _isTrainedOnly;
};


#endif