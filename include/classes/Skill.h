#ifndef SKILL_H
#define SKILL_H

#include "enums.h"

/**
 * @brief Stores the data about one of a \ref Character "characters'" \ref skillType "skills" and can calculate the \ref Total() "total bonus" they get on a skill check of that type.
 *
 */
class Skill
{
public:
    // Creates a Skill based off the given type, sets the proper ability it is based on, and sets all other values to either 0 or false
    Skill(skillType skillType);

    // Getters
    // Returns the total bonus based off the appropriate ability modifier
    short Total(short abilityMod);
    // Returns the skills' type
    skillType SkillType();
    // Returns the ability modifier this Skill uses as its' bonus
    abilityType AbilityType();
    // Returns the skills' total ranks
    short Ranks();
    // Returns the skills' miscellaneous modifier
    short MiscMod();
    // Returns a bool based off if this Skill is a characters class Skill
    bool IsClassSkill();

    // Setters
    // Sets the skills' total ranks
    void Ranks(short ranks);
    // Sets if this Skill is a class skill or not
    void IsClassSkill(bool isClassSkill);

private:
    skillType _skillType;
    abilityType _abilityType;
    short _ranks;
    short _miscMod;
    bool _isClassSkill;
    bool _isTrainedOnly;
};

#endif