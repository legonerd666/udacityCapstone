#ifndef SKILL_H
#define SKILL_H

#include "../enums.h"

class skill
{
public:
    // skill();

    skill(skillType skillType);

    // Getters
    short Total(short abilityMod);
    skillType SkillType();
    abilityType AbilityType();
    short Ranks();
    short MiscMod();
    bool IsClassSkill();

private:
    skillType _skillType;
    abilityType _abilityType;
    short _ranks;
    short _miscMod;
    bool _isClassSkill;
    bool _isTrainedOnly;
};

#endif