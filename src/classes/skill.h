#ifndef SKILL_H
#define SKILL_H

#include "../enums.h"

class skill
{
public:
    skill();

    //Getters
    short Total(short abilityMod);
    abilityType AbilityType();

    //Setters
    void SkillType(skillType newSkillType);
    void AbilityType(abilityType newAbilityType);
    void Ranks(short newRanks);
    void MiscMod(short newMiscMod);
    void IsClassSkill(bool newIsClassSkill);
    void IsTrainedOnly(bool newIsTrainedOnly);

private:
    skillType _skillType;
    abilityType _abilityType;
    short _ranks;
    short _miscMod;
    bool isClassSkill;
    bool isTrainedOnly;
};


#endif