#include "Skill.h"

#include "enums.h"

Skill::Skill(skillType skillType) : _skillType(skillType)
{
    _abilityType = EnumToAbilityType(skillType);
    _ranks = 0;
    _miscMod = 0;
    _isClassSkill = false;
    _isTrainedOnly = false;
}

short Skill::Total(short abilityMod)
{
    if (_isClassSkill && _ranks > 0)
    {
        return abilityMod + _ranks + _miscMod + 3;
    }
    else
    {
        return abilityMod + _ranks + _miscMod;
    }
}

skillType Skill::SkillType()
{
    return _skillType;
}

abilityType Skill::AbilityType()
{
    return _abilityType;
}

short Skill::Ranks()
{
    return _ranks;
}

short Skill::MiscMod()
{
    return _miscMod;
}

bool Skill::IsClassSkill()
{
    return _isClassSkill;
}

void Skill::Ranks(short ranks)
{
    _ranks = ranks;
}

void Skill::IsClassSkill(bool isClassSkill)
{
    _isClassSkill = isClassSkill;
}