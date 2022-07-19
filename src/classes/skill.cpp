#include "skill.h"

#include "../enums.h"

skill::skill(skillType skillType): _skillType(skillType) {
    _abilityType = EnumToAbilityType(skillType);
    _ranks = 0;
    _miscMod = 0;
    _isClassSkill = false;
    _isTrainedOnly = false;
}

short skill::Total(short abilityMod){
    if (_isClassSkill && _ranks > 0){
        return abilityMod + _ranks + _miscMod + 3;
    } else {
        return abilityMod + _ranks + _miscMod;
    }
}

skillType skill::SkillType() {
    return _skillType;
}

abilityType skill::AbilityType() {
    return _abilityType;
}

short skill::Ranks() {
    return _ranks;
}

short skill::MiscMod() {
    return _miscMod;
}

bool skill::IsClassSkill() {
    return _isClassSkill;
}