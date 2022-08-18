#include <string>

#include "Character.h"
#include "enums.h"

#include <climits>

using namespace std;

Character::Character()
{
    _initiative = make_unique<Initiative>();
    _armorClass = make_unique<ArmorClass>();

    _skills.emplace_back(make_unique<Skill>(acrobatics));
    _skills.emplace_back(make_unique<Skill>(appraise));
    _skills.emplace_back(make_unique<Skill>(bluff));
    _skills.emplace_back(make_unique<Skill>(climb));
    _skills.emplace_back(make_unique<Skill>(craft));
    _skills.emplace_back(make_unique<Skill>(diplomacy));
    _skills.emplace_back(make_unique<Skill>(disableDevice));
    _skills.emplace_back(make_unique<Skill>(disguise));
    _skills.emplace_back(make_unique<Skill>(escapeArtist));
    _skills.emplace_back(make_unique<Skill>(fly));
    _skills.emplace_back(make_unique<Skill>(handleAnimal));
    _skills.emplace_back(make_unique<Skill>(heal));
    _skills.emplace_back(make_unique<Skill>(intimidate));
    _skills.emplace_back(make_unique<Skill>(knowArcana));
    _skills.emplace_back(make_unique<Skill>(knowDungeoneering));
    _skills.emplace_back(make_unique<Skill>(knowEngineering));
    _skills.emplace_back(make_unique<Skill>(knowGeography));
    _skills.emplace_back(make_unique<Skill>(knowHistory));
    _skills.emplace_back(make_unique<Skill>(knowLocal));
    _skills.emplace_back(make_unique<Skill>(knowNature));
    _skills.emplace_back(make_unique<Skill>(knowNobility));
    _skills.emplace_back(make_unique<Skill>(knowPlanes));
    _skills.emplace_back(make_unique<Skill>(knowReligion));
    _skills.emplace_back(make_unique<Skill>(linguistics));
    _skills.emplace_back(make_unique<Skill>(perception));
    _skills.emplace_back(make_unique<Skill>(perform));
    _skills.emplace_back(make_unique<Skill>(profession));
    _skills.emplace_back(make_unique<Skill>(ride));
    _skills.emplace_back(make_unique<Skill>(senseMotive));
    _skills.emplace_back(make_unique<Skill>(sleightOfHand));
    _skills.emplace_back(make_unique<Skill>(spellcraft));
    _skills.emplace_back(make_unique<Skill>(stealth));
    _skills.emplace_back(make_unique<Skill>(survival));
    _skills.emplace_back(make_unique<Skill>(swim));
    _skills.emplace_back(make_unique<Skill>(useMagicDevice));

    _spellResistance = 0;

    _currency[0] = make_unique<Currency>(copper, 0);
    _currency[1] = make_unique<Currency>(silver, 0);
    _currency[2] = make_unique<Currency>(gold, 0);
    _currency[3] = make_unique<Currency>(platinum, 0);

    _xp = 0;
    _nextLevelXpAmount = 0;
}

string Character::ToStringForConsole()
{
    unique_lock<mutex> lock(_mutex);

// Adds the characters characteristics to the string
#pragma region Characteristics

    string character = "";
    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Characteristics:";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|     Character Name:                ";
    character += _name;
    character += "\n";

    character += "|     Alignment:                     ";
    character += EnumToString(_alignment);
    character += "\n";

    character += "|     Player:                        ";
    character += _player;
    character += "\n";

    // Formats the charcters roles and adds each to the string
    character += "|     Class(es):                     ";
    for (auto &&role : _roles)
    {
        character += role->Name();
        character += " ";
        character += to_string(role->Level());
        character += ". ";
    }
    character += "\n";

    character += "|     Deity:                         ";
    character += _deity;
    character += "\n";

    character += "|     Homeland:                      ";
    character += _homeland;
    character += "\n";

    character += "|     Race:                          ";
    character += _race->Name();
    character += "\n";

    character += "|     Size:                          ";
    character += EnumToString(_size);
    character += "\n";

    character += "|     Gender:                        ";
    character += _gender;
    character += "\n";

    character += "|     Age:                           ";
    character += to_string(_age);
    character += "\n";

    character += "|     Height:                        ";
    character += to_string(_height);
    character += "\n";

    character += "|     Weight:                        ";
    character += to_string(_weight);
    character += "\n";

    character += "|     Hair:                          ";
    character += _hairColor;
    character += "\n";

    character += "|     Eyes:                          ";
    character += _eyeColor;
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Characteristics

// Adds the characters Hit points and hit dice to the string and if their health would affect their condition it adds said condition to the string next to the stat causing the condition
#pragma region HitPoints

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Hit Points: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|     Total HP:                      ";
    character += to_string(_hitpoints->TotalHP(_abilityScores[2]->AdjustedModifier()));
    character += " (";
    character += to_string(_hitpoints->TotalHP(0));
    character += " + (";
    character += to_string(_abilityScores[2]->AdjustedModifier());
    character += " * ";
    character += to_string(_hitpoints->TotalHitDice());
    character += ")) (Rolled HP + (Constitution * Number of HitDice)) (Min 1)";
    character += "\n";

    character += "|     Hit Dice:                      ";
    for (auto &&hitdie : _hitpoints->HitDice())
    {
        character += hitdie->To_String();
    }
    character += "\n";

    character += "|     Current HP:                    ";
    character += to_string(_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()));
    // If the characters hp is exactly 0 and their non lethal hp doesn't change anything about their condition it displays that this stat is causing them to be disabled
    if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) == 0 && _hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) > -1)
        character += "    You are currently Disabled";
    // Otherwise, if the characters hp is less than 0 but not less than negative their constitution score then it displays that this stat has rendered them unconscious and that they are dying
    else if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Unconscious and Dying";
    // Lastly, if their hitpoints are less than negative their constitution score it displays that they have died
    else if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) <= (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Dead";

    character += "\n";

    character += "|     Current Non-Lethal HP:         ";
    character += to_string(_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()));
    // If the characters Non lethal hit points are exactly 0 and their lethal hitpoints arent affecting them it displays next to this stat that they are staggered
    if (_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) == 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > 0)
        character += "    You are currently Staggered";
    // If the characters non lethal hp is less than 0 it displays next to this stat that they have been knocked out
    else if (_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > -1)
        character += "    You are currently Unconscious";
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion HitPoints

// This adds the characters speeds to the string
#pragma region Speed

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Speed: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|     Base Speed:                    ";
    character += to_string(_speed->Base());
    character += "\n";

    character += "|     Armored Speed:                 ";
    character += to_string(_speed->Armored());
    character += "\n";

    character += "|     Fly Speed:                     ";
    character += to_string(_speed->Fly());
    character += "\n";

    character += "|     Swim Speed:                    ";
    character += to_string(_speed->Swim());
    character += "\n";

    character += "|     Climb Speed:                   ";
    character += to_string(_speed->Climb());
    character += "\n";

    character += "|     Burrow Speed:                  ";
    character += to_string(_speed->Burrow());
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Speed

// This adds the characters ability scores to the string and if the score would affect their characters condition how that stat is affecting them
#pragma region AbilityScores

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Ability Scores: ";
    character += "\n";
    character += "|";
    character += "\n";

#pragma region Strength

    character += "|     Strength: ";
    character += "\n";
    character += "|";
    character += "\n";

    // If either the base or temporary strength score of the Character is 0 or less it displays that this stat is rendering them unconscious and unable to move
    character += "|         Score:                     ";
    character += to_string(_abilityScores[0]->Score());
    if (_abilityScores[0]->Score() < 10 && _abilityScores[0]->Score() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[0]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[0]->Modifier());
    character += ")";
    if (_abilityScores[0]->Score() <= 0)
        character += " You cannot move and are unconscious";

    character += "\n";

    character += "|         Temp Score:                ";
    character += to_string(_abilityScores[0]->AdjustedScore());
    if (_abilityScores[0]->AdjustedScore() < 10 && _abilityScores[0]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[0]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += ")";

    if (_abilityScores[0]->AdjustedScore() <= 0)
        character += " You cannot move and are unconscious";

    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Strength

// If either the base or temporary dexterity score of the Character is 0 or less it displays that this stat is rendering them unable to move
#pragma region Dexterity

    character += "|     Dexterity: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|         Score:                     ";
    character += to_string(_abilityScores[1]->Score());
    if (_abilityScores[1]->Score() < 10 && _abilityScores[1]->Score() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[1]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[1]->Modifier());
    character += ")";
    if (_abilityScores[1]->Score() <= 0)
        character += " You cannot move";

    character += "\n";

    character += "|         Temp Score:                ";
    character += to_string(_abilityScores[1]->AdjustedScore());
    if (_abilityScores[1]->AdjustedScore() < 10 && _abilityScores[1]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[1]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += ")";

    if (_abilityScores[1]->AdjustedScore() <= 0)
        character += " You cannot move";

    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Dexterity

// If either the base or temporary constitution score of the Character is 0 or less it displays that this stat has rendered them dead
#pragma region Constitution

    character += "|     Constitution: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|         Score:                     ";
    character += to_string(_abilityScores[2]->Score());
    if (_abilityScores[2]->Score() < 10 && _abilityScores[2]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[2]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[2]->Modifier());
    character += ")";

    if (_abilityScores[2]->Score() <= 0)
        character += " You are dead";

    character += "\n";

    character += "|         Temp Score:                ";
    character += to_string(_abilityScores[2]->AdjustedScore());
    if (_abilityScores[2]->AdjustedScore() < 10 && _abilityScores[2]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[2]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[2]->AdjustedModifier());
    character += ")";

    if (_abilityScores[2]->AdjustedScore() <= 0)
        character += " You are dead";

    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Constitution

// If either the base or temporary intelligence score of the Character is 0 or less it displays that this stat is rendering them comatose
#pragma region Intelligence

    character += "|     Intelligence: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|         Score:                     ";
    character += to_string(_abilityScores[3]->Score());
    if (_abilityScores[3]->Score() < 10 && _abilityScores[3]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[3]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[3]->Modifier());
    character += ")";

    if (_abilityScores[3]->Score() <= 0)
        character += " You are comatose";

    character += "\n";

    character += "|         Temp Score:                ";
    character += to_string(_abilityScores[3]->AdjustedScore());
    if (_abilityScores[3]->AdjustedScore() < 10 && _abilityScores[3]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[3]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[3]->AdjustedModifier());
    character += ")";

    if (_abilityScores[3]->AdjustedScore() <= 0)
        character += " You are comatose";

    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Intelligence

// If either the base or temporary wisdom score of the Character is 0 or less it displays that this stat is rendering them incapable of rational thought and unconscious
#pragma region Wisdom

    character += "|     Wisdom: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|         Score:                     ";
    character += to_string(_abilityScores[4]->Score());
    if (_abilityScores[4]->Score() < 10 && _abilityScores[4]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[4]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[4]->Modifier());
    character += ")";

    if (_abilityScores[4]->Score() <= 0)
        character += " You are incapable of rational thought and are unconscious";

    character += "\n";

    character += "|         Temp Score:                ";
    character += to_string(_abilityScores[4]->AdjustedScore());
    if (_abilityScores[4]->AdjustedScore() < 10 && _abilityScores[4]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[4]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[4]->AdjustedModifier());
    character += ")";

    if (_abilityScores[4]->AdjustedScore() <= 0)
        character += " You are incapable of rational thought and are unconscious";

    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Wisdom

// If either the base or temporary charisma score of the Character is 0 or less it displays that this stat is rendering them unable of exerting themselves in any manner and unconscious
#pragma region Charisma

    character += "|     Charisma: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|         Score:                     ";
    character += to_string(_abilityScores[5]->Score());
    if (_abilityScores[5]->Score() < 10 && _abilityScores[5]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[5]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[5]->Modifier());
    character += ")";

    if (_abilityScores[5]->Score() <= 0)
        character += " You are unable to exert yourself in any way and are unconscious";

    character += "\n";

    character += "|         Temp Score:                ";
    character += to_string(_abilityScores[5]->AdjustedScore());
    if (_abilityScores[5]->AdjustedScore() < 10 && _abilityScores[5]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[5]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[5]->AdjustedModifier());
    character += ")";

    if (_abilityScores[5]->AdjustedScore() <= 0)
        character += " You are unable to exert yourself in any way and are unconscious";

    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Charisma

#pragma endregion AbilityScores

// Adds the characters saves to the string along with how they are calculated
#pragma region Saves

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Saves:                                (Base + Ability + Magic + Misc + Temp)";
    character += "\n";
    character += "|";
    character += "\n";

    for (auto &&save : _saves)
    {
        character += "|     ";
        character += EnumToString(save->SaveType());
        character += ":";
        character += "\n";
        character += "|";
        character += "\n";
        character += "|         Total Bonus                ";
        if (save->Total(_abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier()) >= 0)
            character += "+";
        character += to_string(save->Total(_abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier()));
        character += " (";
        character += to_string(save->Base());
        character += " + ";
        character += to_string(_abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier());
        character += " + ";
        character += to_string(save->MagicMod());
        character += " + ";
        character += to_string(save->MiscMod());
        character += " + ";
        character += to_string(save->TempMod());
        character += ")";
        character += "\n";
        character += "|";
        character += "\n";
    }

#pragma endregion Saves

// Adds all of the characters skills to the string along with its total bonus, if it is a class skill, and how said bonus is calculated
#pragma region Skills

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Skills:                               (Ability + Ranks + Misc + (3 if you have at least 1 rank and it's a class skill))";
    character += "\n";
    character += "|";
    character += "\n";

    for (auto &&skill : _skills)
    {
        character += "|     ";
        character += EnumToString(skill->SkillType());
        character += ":";
        character += "\n";
        character += "|";
        character += "\n";
        character += "|         Total Bonus:               ";
        if (skill->Total(_abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier()) >= 0)
            character += "+";
        character += to_string(skill->Total(_abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier()));
        character += " (";
        character += to_string(_abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier());
        character += " + ";
        character += to_string(skill->Ranks());
        character += " + ";
        character += to_string(skill->MiscMod());
        if (skill->IsClassSkill() && skill->Ranks() > 0)
            character += " + 3";
        character += ")";
        character += "\n";
        character += "|         Class Skill:               ";
        switch (skill->IsClassSkill())
        {
        case true:
            character += "Yes";
            break;
        default:
            character += "No";
            break;
        }
        character += "\n";
        character += "|";
        character += "\n";
    }

#pragma endregion Skills

// Adds the characters known languages to the string
#pragma region Language

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Languages:                         ";
    character += _languages;
    character += "\n";

#pragma endregion Language

// Adds the characters combat relevant stats to the string (sans hp)
#pragma region Combat

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Combat:";
    character += "\n";
    character += "|";
    character += "\n";

// Adds the characters initiative bonus to the string along with how it is calculated
#pragma region Initiative

    character += "|     Initiative:                    ";
    if (_initiative->Total(_abilityScores[1]->AdjustedModifier()) >= 0)
        character += "+";
    character += to_string(_initiative->Total(_abilityScores[1]->AdjustedModifier()));
    character += " (";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(_initiative->MiscMod());
    character += ") (Dex + Misc)";
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Initiative

// Adds the characters armor class to the string along with how it is calculated and each of its subvalues (flat-footed and touch AC)
#pragma region Armor Class

    character += "|     Armor Class:";
    character += "\n";
    character += "|";
    character += "\n";
    character += "|         AC:                        ";
    character += to_string(_armorClass->Total(_abilityScores[1]->AdjustedModifier(), _size));
    character += " (10 + ";
    character += to_string(_armorClass->Armor());
    character += " + ";
    character += to_string(_armorClass->Shield());
    character += " + ";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size));
    character += " + ";
    character += to_string(_armorClass->NaturalArmor());
    character += " + ";
    character += to_string(_armorClass->DeflectionBonus());
    character += " + ";
    character += to_string(_armorClass->DodgeBonus());
    character += " + ";
    character += to_string(_armorClass->MiscMod());
    character += ")";
    character += " (10 + Armor + Shield + Dex + Size + Natural Armor + Deflection + Dodge + Misc)";
    character += "\n";
    character += "|";
    character += "\n";
    character += "|         Touch AC:                  ";
    character += to_string(_armorClass->TouchArmorClass(_abilityScores[1]->AdjustedModifier(), _size));
    character += " (10 + ";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size));
    character += " + ";
    character += to_string(_armorClass->DeflectionBonus());
    character += " + ";
    character += to_string(_armorClass->DodgeBonus());
    character += " + ";
    character += to_string(_armorClass->MiscMod());
    character += ")";
    character += "             (10 + Dex + Size + Deflection + Dodge + Misc)";
    character += "\n";
    character += "|";
    character += "\n";
    character += "|         Flat-Footed:               ";
    character += to_string(_armorClass->FlatFootedArmorClass(_size));
    character += " (10 + ";
    character += to_string(_armorClass->Armor());
    character += " + ";
    character += to_string(_armorClass->Shield());
    character += " + ";
    character += to_string(EnumToBonus(_size));
    character += " + ";
    character += to_string(_armorClass->NaturalArmor());
    character += " + ";
    character += to_string(_armorClass->DeflectionBonus());
    character += " + ";
    character += to_string(_armorClass->MiscMod());
    character += ")";
    character += "         (10 + Armor + Shield + Size + Natural Armor + Deflection + Misc)";
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion ArmorClass

// Adds the characters combat stats to the string
#pragma region Combat Stats

    // Adds the characters formatted base attack bonuses to the string
    character += "|     Base Attack Bonus:             ";
    if (_baseAttackBonuses.size() == 1)
    {
        character += "+";
        character += to_string(_baseAttackBonuses.front());
    }
    else
    {
        for (auto &&BaB : _baseAttackBonuses)
        {
            character += "+";
            character += to_string(BaB);
            if (BaB != _baseAttackBonuses.back())
                character += "/";
        }
    }

    character += "\n";
    character += "|";
    character += "\n";

    // Adds the characters spell resistance
    character += "|     Spell Resistance:              ";
    character += to_string(_spellResistance);
    character += "%";
    character += "\n";
    character += "|";
    character += "\n";

    // Adds the characters Combat Maneuver Bonus and how it is calculated
    character += "|     CMB:                           ";
    character += to_string(CMB());
    character += " (";
    character += to_string(_baseAttackBonuses.front());
    character += " + ";
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size) * -1);
    character += ")";
    character += " (Base Attack + Strength + Size)";
    character += "\n";
    character += "|";
    character += "\n";

    // Adds the characters Combat Maneuver Defense and how it is calculated
    character += "|     CMD:                           ";
    character += to_string(CMD());
    character += " (";
    character += to_string(_baseAttackBonuses.front());
    character += " + ";
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += " + ";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size) * -1);
    character += " + 10)";
    character += " (Base Attack + Strength + Dexterity + Size + 10)";
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Combat Stats

// Adds all the characters weapons to the string
#pragma region Weapons

    character += "|     Weapons:";
    character += "\n";
    character += "|";
    character += "\n";
    for (auto &&weapon : _weapons)
    {
        character += "|         Name:                      ";
        character += weapon->Name();
        character += "\n";
        character += "|         Attack Bonus:              ";

        // If the characters attack bonus for the Weapon is positive it adds a + to the string
        if ((_baseAttackBonuses.front() + _abilityScores[EnumToIndex(weapon->AbilityType())]->AdjustedModifier() + EnumToBonus(_size)) >= 0)
        {
            character += "+";
        }
        character += to_string(_baseAttackBonuses.front() + _abilityScores[EnumToIndex(weapon->AbilityType())]->AdjustedModifier() + EnumToBonus(_size));
        character += "\n";
        character += "|         Critical:                  ";
        character += weapon->CritRange();
        character += "\n";
        character += "|         Type:                      ";
        character += weapon->DamageType();
        character += "\n";
        character += "|         Range:                     ";
        character += weapon->Range();
        character += " ft.";
        character += "\n";
        character += "|         Ammo:                      ";
        // If the Weapon doesn't use ammo it displays N/A
        if (weapon->Ammo() == -1)
            character += "N/A";
        else
            character += to_string(weapon->Ammo());
        character += "\n";
        character += "|         Damage:                    ";
        character += weapon->Damage();

        // If the Weapon adds the characters strength mod to the damage it display it
        if (weapon->AbilityType() == strength)
        {
            character += "+";
            character += to_string(_abilityScores[0]->AdjustedModifier());
        }

        character += "\n";
        character += "|";
        character += "\n";
    }

#pragma endregion Weapons

// Adds the characters Weapon and armor proficiencies to the string
#pragma region Proficiencies

    character += "|     Proficiencies:                 ";
    character += _proficiencies;
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Proficiencies

#pragma endregion Combat

// Adds the characters equipment to the string
#pragma region Equipment

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Equipment and Gear:";
    character += "\n";
    character += "|";
    character += "\n";

// Adds any items currently worn or wielded by the character that would affect the characters stats to the string
#pragma region ACItems
    character += "|     AC Items:";
    character += "\n";
    character += "|";
    character += "\n";
    {
        // Calculates the totals for each stat affected whilst adding them to the string
        int totalBonus = 0;
        unsigned short maxDexBonus = USHRT_MAX;
        int totalCheckPenalty = 0;
        int totalSpellFailureChance = 0;
        unsigned short baseSpeedAdjustment = _speed->Base();
        int totalWeight = 0;
        for (auto &&acItem : _armorClassItems)
        {
            character += "|         Name:                  ";
            character += acItem->Name();
            character += "\n";
            character += "|         Bonus:                 ";
            character += "+";
            character += to_string(acItem->Bonus());
            character += "\n";
            character += "|         Type:                  ";
            character += acItem->Type();
            character += "\n";
            character += "|         Max Dex Bonus:         ";
            if (acItem->MaxDexBonus() != USHRT_MAX)
            {
                character += "+";
                character += to_string(acItem->MaxDexBonus());
            }
            else
            {
                character += "N/A";
            }
            character += "\n";
            character += "|         Check Penalty:         ";
            character += to_string(acItem->CheckPenalty());
            character += "\n";
            character += "|         Spell Failure %:       ";
            character += to_string(acItem->SpellFailureChance());
            character += "%";
            character += "\n";
            character += "|         Base Speed Adj:        ";
            character += to_string(acItem->BaseSpeedAdjustment());
            character += " ft.";
            character += "\n";
            character += "|         Weight:                ";
            character += to_string(acItem->Weight());
            character += " lbs.";
            character += "\n";
            character += "|         Properties:            ";
            character += acItem->Properties();
            character += "\n";
            character += "|";
            character += "\n";

            totalBonus += acItem->Bonus();
            if (acItem->MaxDexBonus() < maxDexBonus)
            {
                maxDexBonus = acItem->MaxDexBonus();
            }
            totalCheckPenalty += acItem->CheckPenalty() * -1;
            totalSpellFailureChance += acItem->SpellFailureChance();
            if (acItem->BaseSpeedAdjustment() < baseSpeedAdjustment)
            {
                baseSpeedAdjustment = acItem->BaseSpeedAdjustment();
            }
            totalWeight += acItem->Weight();
        }

        // Adds the total stat changes gotten by wearing/wielding all the listed armor items
        character += "|     AC Item Totals:";
        character += "\n";
        character += "|";
        character += "\n";
        character += "|         Bonus:                     ";
        character += "+";
        character += to_string(totalBonus);
        character += "\n";
        character += "|         Max Dex Bonus:             ";
        if (maxDexBonus != USHRT_MAX)
        {
            character += "+";
            character += to_string(maxDexBonus);
        }
        else
        {
            character += "N/A";
        }
        character += "\n";
        character += "|         Check Penalty:             ";
        character += "-";
        character += to_string(totalCheckPenalty);
        character += "\n";
        character += "|         Spell Failure Chance:      ";
        character += to_string(totalSpellFailureChance);
        character += "%";
        character += "\n";
        character += "|         Base Speed Adj:            ";
        character += to_string(baseSpeedAdjustment);
        character += " ft.";
        character += "\n";
        character += "|         Weight:                    ";
        character += to_string(totalWeight);
        character += " lbs.";
        character += " You are wearing a ";
        character += EnumToString(CalcLoad(_abilityScores[0]->AdjustedScore(), totalWeight));
        character += " Load.";
    }
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion ACItems

// Adds the characters Gear to the string
#pragma region Gear

    character += "|     Gear:";
    character += "\n";
    character += "|";
    character += "\n";
    {
        // Calculates the total weight of all the carried Gear and displays if it is a light, medium, or heavy load based on the characters strength score
        int totalWeight = 0;
        for (auto &&item : _gear)
        {
            character += "|         Name:                      ";
            character += item->Name();
            character += "\n";
            character += "|         Description:               ";
            character += item->Description();
            character += "\n";
            character += "|         Weight:                    ";
            character += to_string(item->Weight());
            character += " lbs.";
            character += "\n";
            character += "|";
            character += "\n";
            totalWeight += item->Weight();
        }

        // Displays the type of load the Character is carrying and the characters different lift/carrying stats based of the characters strength
        character += "|     Total Weight:                  ";
        character += to_string(totalWeight);
        character += " lbs.";
        character += " You are carrying a ";
        character += EnumToString(CalcLoad(_abilityScores[0]->AdjustedScore(), totalWeight));
        character += " Load.";
        character += "\n";
        character += "|";
        character += "\n";
        character += "|     Max Carry Weight:";
        character += "\n";
        character += "|";
        character += "\n";
        character += "|         Lift Over Head:            ";
        {
            short maxLoad = CalcMaxLoad(_abilityScores[0]->AdjustedScore());
            character += to_string(maxLoad);
            character += " lbs.";
            character += "\n";
            character += "|         Lift Off Ground:           ";
            character += to_string(maxLoad * 2);
            character += " lbs.";
            character += "\n";
            character += "|         Push/Drag:                 ";
            character += to_string(maxLoad * 5);
            character += " lbs.";
        }
    }
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Gear

// Adds the characters funds to the string
#pragma region Money

    character += "|     Money:";
    character += "\n";
    character += "|";
    character += "\n";
    for (auto &&currency : _currency)
    {
        character += "|         ";
        character += EnumToString(currency->Type());
        character += ":";
        switch (EnumToString(currency->Type()).size())
        {
        case 6:
            character += "                    ";
            break;
        case 4:
            character += "                      ";
            break;
        default:
            character += "                  ";
            break;
        }
        character += to_string(currency->Amount());
        character += "\n";
        character += "|";
        character += "\n";
    }

#pragma endregion Money

#pragma endregion Equipment

// Adds the characters feats to the string
#pragma region Feats

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Feats: ";
    character += "\n";
    character += "|";
    character += "\n";
    for (auto &&feat : _feats)
    {
        character += "|     Name:                          ";
        character += feat->Name();
        character += "\n";
        character += "|     Description:                   ";
        character += feat->Description();
        character += "\n";
        character += "|";
        character += "\n";
    }

#pragma endregion Feats

// Adds the characters racial traits to the string
#pragma region Racial Traits

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Racial Traits: ";
    character += "\n";
    character += "|";
    character += "\n";
    for (auto &&trait : _race->RacialTraits())
    {
        character += "|     Name:                          ";
        character += trait->Name();
        character += "\n";
        character += "|     Description:                   ";
        character += trait->Description();
        character += "\n";
        character += "|";
        character += "\n";
    }

#pragma endregion Racial Traits

// Adds the class features of each Role to the string
#pragma region Class Features

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Class Features: ";
    character += "\n";
    character += "|";
    character += "\n";
    for (auto &&role : _roles)
    {
        if (role->ClassFeatures().size() > 0)
        {
            character += "|     ";
            character += role->Name();
            character += ":";
            character += "\n";
            character += "|";
            character += "\n";

            for (auto &&feature : role->ClassFeatures())
            {
                character += "|         Name:                      ";
                character += feature->Name();
                character += "\n";
                character += "|         Description:               ";
                character += feature->Description();
                character += "\n";
                character += "|";
                character += "\n";
            }
        }
    }

#pragma endregion Class Features

// Adds the characters total exp and how much is required to level up to the string
#pragma region Exp

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Experience Points:                 ";
    character += to_string(_xp);
    character += "\n";
    character += "|";
    character += "\n";
    character += "| Next Level:                        ";
    character += to_string(_nextLevelXpAmount);
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Exp

// Displays all the known spells for each of the characters roles and the stats regarding spell casting provided the Character knows at least a spell from that level
#pragma region Spells

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Spells:";
    character += "\n";
    character += "|";
    character += "\n";
    for (auto &&role : _roles)
    {
        if (role->IsCastingClass())
        {
            character += "|     ";
            character += role->Name();
            character += ":";
            character += "\n";
            character += "|";
            character += "\n";
            character += "|         Stats:";
            character += "\n";
            character += "|";
            character += "\n";
            for (short i = 0; i < 10; i++)
            {
                // If the Character knows at least 1 spell of the given level and has a high enough spell casting ability score to cast spells of that level it displays the spell stats for that level
                if (role->SpellStats()[i]->SpellsKnown() != 0 && _abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedScore() >= 10 + role->SpellStats()[i]->SpellLevel())
                {
                    character += "|             Spell Level:           ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += "\n";
                    character += "|";
                    character += "\n";
                    character += "|                 Spells Known:      ";
                    if (role->SpellStats()[i]->SpellsKnown() == -2)
                    {
                        character += "You can prepare any level ";
                        character += to_string(role->SpellStats()[i]->SpellLevel());
                        character += " spells from the ";
                        character += role->Name();
                        character += " spell list.";
                    }
                    else if (role->SpellStats()[i]->SpellsKnown() == -1)
                    {
                        character += "You know all level ";
                        character += to_string(role->SpellStats()[i]->SpellLevel());
                        character += " spells from the ";
                        character += role->Name();
                        character += " spell list.";
                    }
                    else
                        character += to_string(role->SpellStats()[i]->SpellsKnown());
                    character += "\n";
                    character += "|                 Spell Save DC:     ";
                    character += to_string(role->SpellStats()[i]->SpellDC(_abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedModifier()));
                    character += "\n";
                    character += "|                 Spells Per Day:    ";
                    character += to_string(role->SpellStats()[i]->SpellsPerDay());
                    character += "\n";
                    character += "|                 Bonus Spells:      ";
                    character += to_string(role->SpellStats()[i]->BonusSpells());
                    character += "\n";
                    character += "|";
                    character += "\n";
                    character += "|";
                    character += "\n";
                }
                // Otherwise, if the Character knows at least 1 spell it displays the number of spells known and the Save dc for that level (for if they have spell-like abilities that use that dc) but tells them they arent allowed to cast any spells of that level
                else if (role->SpellStats()[i]->SpellsKnown() != 0 && _abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedScore() < 10 + role->SpellStats()[i]->SpellLevel())
                {

                    character += "|             Spell Level:           ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += "\n";
                    character += "|";
                    character += "\n";
                    character += "|                 Spells Known:      ";
                    character += to_string(role->SpellStats()[i]->SpellsKnown());
                    character += "\n";
                    character += "|                 Spell Save DC:     ";
                    character += to_string(role->SpellStats()[i]->SpellDC(_abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedModifier()));
                    character += "\n";
                    character += "|";
                    character += "\n";
                    character += "|                 You are unable to cast level ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += " spells.";
                    character += "\n";
                    character += "|                 You need at least a";
                    if (10 + role->SpellStats()[i]->SpellLevel() == 11 || 10 + role->SpellStats()[i]->SpellLevel() == 18)
                        character += "n";
                    character += " ";
                    character += to_string(10 + role->SpellStats()[i]->SpellLevel());
                    character += " in ";
                    character += EnumToString(role->SpellStats()[i]->AbilityType());
                    character += " to cast level ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += " spells as a";
                    if (tolower(role->Name()[0]) == 'a' || tolower(role->Name()[0]) == 'e' || tolower(role->Name()[0]) == 'i' || tolower(role->Name()[0]) == 'o' || tolower(role->Name()[0]) == 'u')
                        character += "n";
                    character += " ";
                    character += role->Name();
                    character += ".";
                    character += "\n";
                    character += "|";
                    character += "\n";
                    character += "|";
                    character += "\n";
                }
            }

            // Adds all the spells known in detail to the string
            character += "|         Spells:";
            character += "\n";
            character += "|";
            character += "\n";

            for (auto &&spell : role->Spells())
            {
                character += "|             Name:                  ";
                character += spell->Name();
                character += "\n";
                character += "|";
                character += "\n";
                character += "|                 Magic School:      ";
                character += EnumToString(spell->School());
                character += "\n";
                character += "|                 Level:             ";
                for (auto &&classSpellListItem : spell->Roles())
                {
                    character += EnumToString(classSpellListItem->CasterType());
                    character += " ";
                    character += to_string(classSpellListItem->Level());
                    if (classSpellListItem != spell->Roles().back())
                        character += ", ";
                }
                character += "\n";
                character += "|                 Casting Time:      ";
                character += spell->CastingTime();
                character += "\n";
                character += "|                 Components:        ";
                character += spell->Components();
                character += "\n";
                character += "|                 Range:             ";
                character += spell->Range();
                character += "\n";
                character += "|                 Target:            ";
                character += spell->Target();
                character += "\n";
                character += "|                 Duration:          ";
                character += spell->Duration();
                character += "\n";
                character += "|                 Saving Throw:      ";
                character += spell->SavingThrow();
                character += "\n";
                character += "|                 Spell Resistance:  ";
                switch (spell->SpellResistance())
                {
                case true:
                    character += "yes";
                    break;
                default:
                    character += "no";
                    break;
                }
                character += "\n";
                character += "|                 Description:       ";
                character += spell->Description();
                character += "\n";
                character += "|";
                character += "\n";
            }
        }
    }

#pragma endregion Spells

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    return character;
}

string Character::ToStringForWeb()
{
    unique_lock<mutex> lock(_mutex);

// Adds the characters characteristics to the string
#pragma region Characteristics

    string character = "";
    character += "Characteristics:";
    character += "<br>";
    character += "<br>";

    character += "    Character Name:                ";
    character += _name;
    character += "<br>";

    character += "    Alignment:                     ";
    character += EnumToString(_alignment);
    character += "<br>";

    character += "    Player:                        ";
    character += _player;
    character += "<br>";

    // Formats the charcters roles and adds each to the string
    character += "    Class(es):                     ";
    for (auto &&role : _roles)
    {
        character += role->Name();
        character += " ";
        character += to_string(role->Level());
        character += ". ";
    }
    character += "<br>";

    character += "    Deity:                         ";
    character += _deity;
    character += "<br>";

    character += "    Homeland:                      ";
    character += _homeland;
    character += "<br>";

    character += "    Race:                          ";
    character += _race->Name();
    character += "<br>";

    character += "    Size:                          ";
    character += EnumToString(_size);
    character += "<br>";

    character += "    Gender:                        ";
    character += _gender;
    character += "<br>";

    character += "    Age:                           ";
    character += to_string(_age);
    character += "<br>";

    character += "    Height:                        ";
    character += to_string(_height);
    character += "<br>";

    character += "    Weight:                        ";
    character += to_string(_weight);
    character += "<br>";

    character += "    Hair:                          ";
    character += _hairColor;
    character += "<br>";

    character += "    Eyes:                          ";
    character += _eyeColor;
    character += "<br>";
    character += "<br>";

#pragma endregion Characteristics

// Adds the characters Hit points and hit dice to the string and if their health would affect their condition it adds said condition to the string next to the stat causing the condition
#pragma region HitPoints

    character += "<br>";

    character += "Hit Points: ";
    character += "<br>";
    character += "<br>";

    character += "    Total HP:                      ";
    character += to_string(_hitpoints->TotalHP(_abilityScores[2]->AdjustedModifier()));
    character += " (";
    character += to_string(_hitpoints->TotalHP(0));
    character += " + (";
    character += to_string(_abilityScores[2]->AdjustedModifier());
    character += " * ";
    character += to_string(_hitpoints->TotalHitDice());
    character += ")) (Rolled HP + (Constitution * Number of HitDice)) (Min 1)";
    character += "<br>";

    character += "    Hit Dice:                      ";
    for (auto &&hitdie : _hitpoints->HitDice())
    {
        character += hitdie->To_String();
    }
    character += "<br>";

    character += "    Current HP:                    ";
    character += to_string(_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()));
    // If the characters hp is exactly 0 and their non lethal hp doesn't change anything about their condition it displays that this stat is causing them to be disabled
    if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) == 0 && _hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) > -1)
        character += "    You are currently Disabled";
    // Otherwise, if the characters hp is less than 0 but not less than negative their constitution score then it displays that this stat has rendered them unconscious and that they are dying
    else if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Unconscious and Dying";
    // Lastly, if their hitpoints are less than negative their constitution score it displays that they have died
    else if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) <= (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Dead";

    character += "<br>";

    character += "    Current Non-Lethal HP:         ";
    character += to_string(_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()));
    // If the characters Non lethal hit points are exactly 0 and their lethal hitpoints arent affecting them it displays next to this stat that they are staggered
    if (_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) == 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > 0)
        character += "    You are currently Staggered";
    // If the characters non lethal hp is less than 0 it displays next to this stat that they have been knocked out
    else if (_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > -1)
        character += "    You are currently Unconscious";
    character += "<br>";
    character += "<br>";

#pragma endregion HitPoints

// This adds the characters speeds to the string
#pragma region Speed

    character += "<br>";

    character += "Speed: ";
    character += "<br>";
    character += "<br>";

    character += "    Base Speed:                    ";
    character += to_string(_speed->Base());
    character += "<br>";

    character += "    Armored Speed:                 ";
    character += to_string(_speed->Armored());
    character += "<br>";

    character += "    Fly Speed:                     ";
    character += to_string(_speed->Fly());
    character += "<br>";

    character += "    Swim Speed:                    ";
    character += to_string(_speed->Swim());
    character += "<br>";

    character += "    Climb Speed:                   ";
    character += to_string(_speed->Climb());
    character += "<br>";

    character += "    Burrow Speed:                  ";
    character += to_string(_speed->Burrow());
    character += "<br>";
    character += "<br>";

#pragma endregion Speed

// This adds the characters ability scores to the string and if the score would affect their characters condition how that stat is affecting them
#pragma region AbilityScores

    character += "<br>";

    character += "Ability Scores: ";
    character += "<br>";
    character += "<br>";

#pragma region Strength

    character += "    Strength: ";
    character += "<br>";
    character += "<br>";

    // If either the base or temporary strength score of the Character is 0 or less it displays that this stat is rendering them unconscious and unable to move
    character += "        Score:                     ";
    character += to_string(_abilityScores[0]->Score());
    if (_abilityScores[0]->Score() < 10 && _abilityScores[0]->Score() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[0]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[0]->Modifier());
    character += ")";
    if (_abilityScores[0]->Score() <= 0)
        character += " You cannot move and are unconscious";

    character += "<br>";

    character += "        Temp Score:                ";
    character += to_string(_abilityScores[0]->AdjustedScore());
    if (_abilityScores[0]->AdjustedScore() < 10 && _abilityScores[0]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[0]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += ")";

    if (_abilityScores[0]->AdjustedScore() <= 0)
        character += " You cannot move and are unconscious";

    character += "<br>";
    character += "<br>";

#pragma endregion Strength

// If either the base or temporary dexterity score of the Character is 0 or less it displays that this stat is rendering them unable to move
#pragma region Dexterity

    character += "    Dexterity: ";
    character += "<br>";
    character += "<br>";

    character += "        Score:                     ";
    character += to_string(_abilityScores[1]->Score());
    if (_abilityScores[1]->Score() < 10 && _abilityScores[1]->Score() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[1]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[1]->Modifier());
    character += ")";
    if (_abilityScores[1]->Score() <= 0)
        character += " You cannot move";

    character += "<br>";

    character += "        Temp Score:                ";
    character += to_string(_abilityScores[1]->AdjustedScore());
    if (_abilityScores[1]->AdjustedScore() < 10 && _abilityScores[1]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[1]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += ")";

    if (_abilityScores[1]->AdjustedScore() <= 0)
        character += " You cannot move";

    character += "<br>";
    character += "<br>";

#pragma endregion Dexterity

// If either the base or temporary constitution score of the Character is 0 or less it displays that this stat has rendered them dead
#pragma region Constitution

    character += "    Constitution: ";
    character += "<br>";
    character += "<br>";

    character += "        Score:                     ";
    character += to_string(_abilityScores[2]->Score());
    if (_abilityScores[2]->Score() < 10 && _abilityScores[2]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[2]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[2]->Modifier());
    character += ")";

    if (_abilityScores[2]->Score() <= 0)
        character += " You are dead";

    character += "<br>";

    character += "        Temp Score:                ";
    character += to_string(_abilityScores[2]->AdjustedScore());
    if (_abilityScores[2]->AdjustedScore() < 10 && _abilityScores[2]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[2]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[2]->AdjustedModifier());
    character += ")";

    if (_abilityScores[2]->AdjustedScore() <= 0)
        character += " You are dead";

    character += "<br>";
    character += "<br>";

#pragma endregion Constitution

// If either the base or temporary intelligence score of the Character is 0 or less it displays that this stat is rendering them comatose
#pragma region Intelligence

    character += "    Intelligence: ";
    character += "<br>";
    character += "<br>";

    character += "        Score:                     ";
    character += to_string(_abilityScores[3]->Score());
    if (_abilityScores[3]->Score() < 10 && _abilityScores[3]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[3]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[3]->Modifier());
    character += ")";

    if (_abilityScores[3]->Score() <= 0)
        character += " You are comatose";

    character += "<br>";

    character += "        Temp Score:                ";
    character += to_string(_abilityScores[3]->AdjustedScore());
    if (_abilityScores[3]->AdjustedScore() < 10 && _abilityScores[3]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[3]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[3]->AdjustedModifier());
    character += ")";

    if (_abilityScores[3]->AdjustedScore() <= 0)
        character += " You are comatose";

    character += "<br>";
    character += "<br>";

#pragma endregion Intelligence

// If either the base or temporary wisdom score of the Character is 0 or less it displays that this stat is rendering them incapable of rational thought and unconscious
#pragma region Wisdom

    character += "    Wisdom: ";
    character += "<br>";
    character += "<br>";

    character += "        Score:                     ";
    character += to_string(_abilityScores[4]->Score());
    if (_abilityScores[4]->Score() < 10 && _abilityScores[4]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[4]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[4]->Modifier());
    character += ")";

    if (_abilityScores[4]->Score() <= 0)
        character += " You are incapable of rational thought and are unconscious";

    character += "<br>";

    character += "        Temp Score:                ";
    character += to_string(_abilityScores[4]->AdjustedScore());
    if (_abilityScores[4]->AdjustedScore() < 10 && _abilityScores[4]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[4]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[4]->AdjustedModifier());
    character += ")";

    if (_abilityScores[4]->AdjustedScore() <= 0)
        character += " You are incapable of rational thought and are unconscious";

    character += "<br>";
    character += "<br>";

#pragma endregion Wisdom

// If either the base or temporary charisma score of the Character is 0 or less it displays that this stat is rendering them unable of exerting themselves in any manner and unconscious
#pragma region Charisma

    character += "    Charisma: ";
    character += "<br>";
    character += "<br>";

    character += "        Score:                     ";
    character += to_string(_abilityScores[5]->Score());
    if (_abilityScores[5]->Score() < 10 && _abilityScores[5]->Score() >= 0)
        character += " ";

    character += " (";
    if (_abilityScores[5]->Modifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[5]->Modifier());
    character += ")";

    if (_abilityScores[5]->Score() <= 0)
        character += " You are unable to exert yourself in any way and are unconscious";

    character += "<br>";

    character += "        Temp Score:                ";
    character += to_string(_abilityScores[5]->AdjustedScore());
    if (_abilityScores[5]->AdjustedScore() < 10 && _abilityScores[5]->AdjustedScore() >= 0)
        character += " ";
    character += " (";
    if (_abilityScores[5]->AdjustedModifier() >= 0)
        character += "+";
    character += to_string(_abilityScores[5]->AdjustedModifier());
    character += ")";

    if (_abilityScores[5]->AdjustedScore() <= 0)
        character += " You are unable to exert yourself in any way and are unconscious";

    character += "<br>";
    character += "<br>";

#pragma endregion Charisma

#pragma endregion AbilityScores

// Adds the characters saves to the string along with how they are calculated
#pragma region Saves

    character += "<br>";

    character += "Saves:                                (Base + Ability + Magic + Misc + Temp)";
    character += "<br>";
    character += "<br>";

    for (auto &&save : _saves)
    {
        character += "    ";
        character += EnumToString(save->SaveType());
        character += ":";
        character += "<br>";
        character += "<br>";
        character += "        Total Bonus                ";
        if (save->Total(_abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier()) >= 0)
            character += "+";
        character += to_string(save->Total(_abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier()));
        character += " (";
        character += to_string(save->Base());
        character += " + ";
        character += to_string(_abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier());
        character += " + ";
        character += to_string(save->MagicMod());
        character += " + ";
        character += to_string(save->MiscMod());
        character += " + ";
        character += to_string(save->TempMod());
        character += ")";
        character += "<br>";
        character += "<br>";
    }

#pragma endregion Saves

// Adds all of the characters skills to the string along with its total bonus, if it is a class skill, and how said bonus is calculated
#pragma region Skills

    character += "<br>";

    character += "Skills:                               (Ability + Ranks + Misc + (3 if you have at least 1 rank and it's a class skill))";
    character += "<br>";
    character += "<br>";

    for (auto &&skill : _skills)
    {
        character += "    ";
        character += EnumToString(skill->SkillType());
        character += ":";
        character += "<br>";
        character += "<br>";
        character += "        Total Bonus:               ";
        if (skill->Total(_abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier()) >= 0)
            character += "+";
        character += to_string(skill->Total(_abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier()));
        character += " (";
        character += to_string(_abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier());
        character += " + ";
        character += to_string(skill->Ranks());
        character += " + ";
        character += to_string(skill->MiscMod());
        if (skill->IsClassSkill() && skill->Ranks() > 0)
            character += " + 3";
        character += ")";
        character += "<br>";
        character += "        Class Skill:               ";
        switch (skill->IsClassSkill())
        {
        case true:
            character += "Yes";
            break;
        default:
            character += "No";
            break;
        }
        character += "<br>";
        character += "<br>";
    }

#pragma endregion Skills

// Adds the characters known languages to the string
#pragma region Language

    character += "<br>";
    character += "Languages:                         ";
    character += _languages;
    character += "<br>";

#pragma endregion Language

// Adds the characters combat relevant stats to the string (sans hp)
#pragma region Combat

    character += "<br>";
    character += "Combat:";
    character += "<br>";
    character += "<br>";

// Adds the characters initiative bonus to the string along with how it is calculated
#pragma region Initiative

    character += "    Initiative:                    ";
    if (_initiative->Total(_abilityScores[1]->AdjustedModifier()) >= 0)
        character += "+";
    character += to_string(_initiative->Total(_abilityScores[1]->AdjustedModifier()));
    character += " (";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(_initiative->MiscMod());
    character += ") (Dex + Misc)";
    character += "<br>";
    character += "<br>";

#pragma endregion Initiative

// Adds the characters armor class to the string along with how it is calculated and each of its subvalues (flat-footed and touch AC)
#pragma region Armor Class

    character += "    Armor Class:";
    character += "<br>";
    character += "<br>";
    character += "        AC:                        ";
    character += to_string(_armorClass->Total(_abilityScores[1]->AdjustedModifier(), _size));
    character += " (10 + ";
    character += to_string(_armorClass->Armor());
    character += " + ";
    character += to_string(_armorClass->Shield());
    character += " + ";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size));
    character += " + ";
    character += to_string(_armorClass->NaturalArmor());
    character += " + ";
    character += to_string(_armorClass->DeflectionBonus());
    character += " + ";
    character += to_string(_armorClass->DodgeBonus());
    character += " + ";
    character += to_string(_armorClass->MiscMod());
    character += ")";
    character += " (10 + Armor + Shield + Dex + Size + Natural Armor + Deflection + Dodge + Misc)";
    character += "<br>";
    character += "<br>";
    character += "        Touch AC:                  ";
    character += to_string(_armorClass->TouchArmorClass(_abilityScores[1]->AdjustedModifier(), _size));
    character += " (10 + ";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size));
    character += " + ";
    character += to_string(_armorClass->DeflectionBonus());
    character += " + ";
    character += to_string(_armorClass->DodgeBonus());
    character += " + ";
    character += to_string(_armorClass->MiscMod());
    character += ")";
    character += "             (10 + Dex + Size + Deflection + Dodge + Misc)";
    character += "<br>";
    character += "<br>";
    character += "        Flat-Footed:               ";
    character += to_string(_armorClass->FlatFootedArmorClass(_size));
    character += " (10 + ";
    character += to_string(_armorClass->Armor());
    character += " + ";
    character += to_string(_armorClass->Shield());
    character += " + ";
    character += to_string(EnumToBonus(_size));
    character += " + ";
    character += to_string(_armorClass->NaturalArmor());
    character += " + ";
    character += to_string(_armorClass->DeflectionBonus());
    character += " + ";
    character += to_string(_armorClass->MiscMod());
    character += ")";
    character += "         (10 + Armor + Shield + Size + Natural Armor + Deflection + Misc)";
    character += "<br>";
    character += "<br>";

#pragma endregion ArmorClass

// Adds the characters combat stats to the string
#pragma region Combat Stats

    // Adds the characters formatted base attack bonuses to the string
    character += "    Base Attack Bonus:             ";
    if (_baseAttackBonuses.size() == 1)
    {
        character += "+";
        character += to_string(_baseAttackBonuses.front());
    }
    else
    {
        for (auto &&BaB : _baseAttackBonuses)
        {
            character += "+";
            character += to_string(BaB);
            if (BaB != _baseAttackBonuses.back())
                character += "/";
        }
    }

    character += "<br>";
    character += "<br>";

    // Adds the characters spell resistance
    character += "    Spell Resistance:              ";
    character += to_string(_spellResistance);
    character += "%";
    character += "<br>";
    character += "<br>";

    // Adds the characters Combat Maneuver Bonus and how it is calculated
    character += "    CMB:                           ";
    character += to_string(CMB());
    character += " (";
    character += to_string(_baseAttackBonuses.front());
    character += " + ";
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size) * -1);
    character += ")";
    character += " (Base Attack + Strength + Size)";
    character += "<br>";
    character += "<br>";

    // Adds the characters Combat Maneuver Defense and how it is calculated
    character += "    CMD:                           ";
    character += to_string(CMD());
    character += " (";
    character += to_string(_baseAttackBonuses.front());
    character += " + ";
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += " + ";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(EnumToBonus(_size) * -1);
    character += " + 10)";
    character += " (Base Attack + Strength + Dexterity + Size + 10)";
    character += "<br>";
    character += "<br>";

#pragma endregion Combat Stats

// Adds all the characters weapons to the string
#pragma region Weapons

    character += "    Weapons:";
    character += "<br>";
    character += "<br>";
    for (auto &&weapon : _weapons)
    {
        character += "        Name:                      ";
        character += weapon->Name();
        character += "<br>";
        character += "        Attack Bonus:              ";

        // If the characters attack bonus for the Weapon is positive it adds a + to the string
        if ((_baseAttackBonuses.front() + _abilityScores[EnumToIndex(weapon->AbilityType())]->AdjustedModifier() + EnumToBonus(_size)) >= 0)
        {
            character += "+";
        }
        character += to_string(_baseAttackBonuses.front() + _abilityScores[EnumToIndex(weapon->AbilityType())]->AdjustedModifier() + EnumToBonus(_size));
        character += "<br>";
        character += "        Critical:                  ";
        character += weapon->CritRange();
        character += "<br>";
        character += "        Type:                      ";
        character += weapon->DamageType();
        character += "<br>";
        character += "        Range:                     ";
        character += weapon->Range();
        character += " ft.";
        character += "<br>";
        character += "        Ammo:                      ";
        // If the Weapon doesn't use ammo it displays N/A
        if (weapon->Ammo() == -1)
            character += "N/A";
        else
            character += to_string(weapon->Ammo());
        character += "<br>";
        character += "        Damage:                    ";
        character += weapon->Damage();

        // If the Weapon adds the characters strength mod to the damage it display it
        if (weapon->AbilityType() == strength)
        {
            character += "+";
            character += to_string(_abilityScores[0]->AdjustedModifier());
        }

        character += "<br>";
        character += "<br>";
    }

#pragma endregion Weapons

// Adds the characters Weapon and armor proficiencies to the string
#pragma region Proficiencies

    character += "    Proficiencies:                 ";
    character += _proficiencies;
    character += "<br>";
    character += "<br>";

#pragma endregion Proficiencies

#pragma endregion Combat

// Adds the characters equipment to the string
#pragma region Equipment

    character += "<br>";
    character += "Equipment and Gear:";
    character += "<br>";
    character += "<br>";

// Adds any items currently worn or wielded by the character that would affect the characters stats to the string
#pragma region ACItems
    character += "    AC Items:";
    character += "<br>";
    character += "<br>";
    {
        // Calculates the totals for each stat affected whilst adding them to the string
        int totalBonus = 0;
        unsigned short maxDexBonus = USHRT_MAX;
        int totalCheckPenalty = 0;
        int totalSpellFailureChance = 0;
        unsigned short baseSpeedAdjustment = _speed->Base();
        int totalWeight = 0;
        for (auto &&acItem : _armorClassItems)
        {
            character += "        Name:                  ";
            character += acItem->Name();
            character += "<br>";
            character += "        Bonus:                 ";
            character += "+";
            character += to_string(acItem->Bonus());
            character += "<br>";
            character += "        Type:                  ";
            character += acItem->Type();
            character += "<br>";
            character += "        Max Dex Bonus:         ";
            if (acItem->MaxDexBonus() != USHRT_MAX)
            {
                character += "+";
                character += to_string(acItem->MaxDexBonus());
            }
            else
            {
                character += "N/A";
            }
            character += "<br>";
            character += "        Check Penalty:         ";
            character += to_string(acItem->CheckPenalty());
            character += "<br>";
            character += "        Spell Failure %:       ";
            character += to_string(acItem->SpellFailureChance());
            character += "%";
            character += "<br>";
            character += "        Base Speed Adj:        ";
            character += to_string(acItem->BaseSpeedAdjustment());
            character += " ft.";
            character += "<br>";
            character += "        Weight:                ";
            character += to_string(acItem->Weight());
            character += " lbs.";
            character += "<br>";
            character += "        Properties:            ";
            character += acItem->Properties();
            character += "<br>";
            character += "|";
            character += "<br>";

            totalBonus += acItem->Bonus();
            if (acItem->MaxDexBonus() < maxDexBonus)
            {
                maxDexBonus = acItem->MaxDexBonus();
            }
            totalCheckPenalty += acItem->CheckPenalty() * -1;
            totalSpellFailureChance += acItem->SpellFailureChance();
            if (acItem->BaseSpeedAdjustment() < baseSpeedAdjustment)
            {
                baseSpeedAdjustment = acItem->BaseSpeedAdjustment();
            }
            totalWeight += acItem->Weight();
        }

        // Adds the total stat changes gotten by wearing/wielding all the listed armor items
        character += "    AC Item Totals:";
        character += "<br>";
        character += "<br>";
        character += "        Bonus:                     ";
        character += "+";
        character += to_string(totalBonus);
        character += "<br>";
        character += "        Max Dex Bonus:             ";
        if (maxDexBonus != USHRT_MAX)
        {
            character += "+";
            character += to_string(maxDexBonus);
        }
        else
        {
            character += "N/A";
        }
        character += "<br>";
        character += "        Check Penalty:             ";
        character += "-";
        character += to_string(totalCheckPenalty);
        character += "<br>";
        character += "        Spell Failure Chance:      ";
        character += to_string(totalSpellFailureChance);
        character += "%";
        character += "<br>";
        character += "        Base Speed Adj:            ";
        character += to_string(baseSpeedAdjustment);
        character += " ft.";
        character += "<br>";
        character += "        Weight:                    ";
        character += to_string(totalWeight);
        character += " lbs.";
        character += " You are wearing a ";
        character += EnumToString(CalcLoad(_abilityScores[0]->AdjustedScore(), totalWeight));
        character += " Load.";
    }
    character += "<br>";
    character += "<br>";

#pragma endregion ACItems

// Adds the characters Gear to the string
#pragma region Gear

    character += "    Gear:";
    character += "<br>";
    character += "<br>";
    {
        // Calculates the total weight of all the carried Gear and displays if it is a light, medium, or heavy load based on the characters strength score
        int totalWeight = 0;
        for (auto &&item : _gear)
        {
            character += "        Name:                      ";
            character += item->Name();
            character += "<br>";
            character += "        Description:               ";
            character += item->Description();
            character += "<br>";
            character += "        Weight:                    ";
            character += to_string(item->Weight());
            character += " lbs.";
            character += "<br>";
            character += "|";
            character += "<br>";
            totalWeight += item->Weight();
        }

        // Displays the type of load the Character is carrying and the characters different lift/carrying stats based of the characters strength
        character += "    Total Weight:                  ";
        character += to_string(totalWeight);
        character += " lbs.";
        character += " You are carrying a ";
        character += EnumToString(CalcLoad(_abilityScores[0]->AdjustedScore(), totalWeight));
        character += " Load.";
        character += "<br>";
        character += "<br>";
        character += "    Max Carry Weight:";
        character += "<br>";
        character += "<br>";
        character += "        Lift Over Head:            ";
        {
            short maxLoad = CalcMaxLoad(_abilityScores[0]->AdjustedScore());
            character += to_string(maxLoad);
            character += " lbs.";
            character += "<br>";
            character += "        Lift Off Ground:           ";
            character += to_string(maxLoad * 2);
            character += " lbs.";
            character += "<br>";
            character += "        Push/Drag:                 ";
            character += to_string(maxLoad * 5);
            character += " lbs.";
        }
    }
    character += "<br>";
    character += "<br>";

#pragma endregion Gear

// Adds the characters funds to the string
#pragma region Money

    character += "    Money:";
    character += "<br>";
    character += "<br>";
    for (auto &&currency : _currency)
    {
        character += "        ";
        character += EnumToString(currency->Type());
        character += ":";
        switch (EnumToString(currency->Type()).size())
        {
        case 6:
            character += "                    ";
            break;
        case 4:
            character += "                      ";
            break;
        default:
            character += "                  ";
            break;
        }
        character += to_string(currency->Amount());
        character += "<br>";
        character += "<br>";
    }

#pragma endregion Money

#pragma endregion Equipment

// Adds the characters feats to the string
#pragma region Feats

    character += "<br>";
    character += "Feats: ";
    character += "<br>";
    character += "<br>";
    for (auto &&feat : _feats)
    {
        character += "    Name:                          ";
        character += feat->Name();
        character += "<br>";
        character += "    Description:                   ";
        character += feat->Description();
        character += "<br>";
        character += "<br>";
    }

#pragma endregion Feats

// Adds the characters racial traits to the string
#pragma region Racial Traits

    character += "<br>";
    character += "Racial Traits: ";
    character += "<br>";
    character += "<br>";
    for (auto &&trait : _race->RacialTraits())
    {
        character += "    Name:                          ";
        character += trait->Name();
        character += "<br>";
        character += "    Description:                   ";
        character += trait->Description();
        character += "<br>";
        character += "<br>";
    }

#pragma endregion Racial Traits

// Adds the class features of each Role to the string
#pragma region Class Features

    character += "<br>";
    character += "Class Features: ";
    character += "<br>";
    character += "<br>";
    for (auto &&role : _roles)
    {
        if (role->ClassFeatures().size() > 0)
        {
            character += "    ";
            character += role->Name();
            character += ":";
            character += "<br>";
            character += "|";
            character += "<br>";

            for (auto &&feature : role->ClassFeatures())
            {
                character += "        Name:                      ";
                character += feature->Name();
                character += "<br>";
                character += "        Description:               ";
                character += feature->Description();
                character += "<br>";
                character += "|";
                character += "<br>";
            }
        }
    }

#pragma endregion Class Features

// Adds the characters total exp and how much is required to level up to the string
#pragma region Exp

    character += "<br>";
    character += "Experience Points:                 ";
    character += to_string(_xp);
    character += "<br>";
    character += "<br>";
    character += "Next Level:                        ";
    character += to_string(_nextLevelXpAmount);
    character += "<br>";
    character += "<br>";

#pragma endregion Exp

// Displays all the known spells for each of the characters roles and the stats regarding spell casting provided the Character knows at least a spell from that level
#pragma region Spells

    character += "<br>";
    character += "Spells:";
    character += "<br>";
    character += "<br>";
    for (auto &&role : _roles)
    {
        if (role->IsCastingClass())
        {
            character += "    ";
            character += role->Name();
            character += ":";
            character += "<br>";
            character += "|";
            character += "<br>";
            character += "        Stats:";
            character += "<br>";
            character += "|";
            character += "<br>";
            for (short i = 0; i < 10; i++)
            {
                // If the Character knows at least 1 spell of the given level and has a high enough spell casting ability score to cast spells of that level it displays the spell stats for that level
                if (role->SpellStats()[i]->SpellsKnown() != 0 && _abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedScore() >= 10 + role->SpellStats()[i]->SpellLevel())
                {
                    character += "            Spell Level:           ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                    character += "                Spells Known:      ";
                    if (role->SpellStats()[i]->SpellsKnown() == -2)
                    {
                        character += "You can prepare any level ";
                        character += to_string(role->SpellStats()[i]->SpellLevel());
                        character += " spells from the ";
                        character += role->Name();
                        character += " spell list.";
                    }
                    else if (role->SpellStats()[i]->SpellsKnown() == -1)
                    {
                        character += "You know all level ";
                        character += to_string(role->SpellStats()[i]->SpellLevel());
                        character += " spells from the ";
                        character += role->Name();
                        character += " spell list.";
                    }
                    else
                        character += to_string(role->SpellStats()[i]->SpellsKnown());
                    character += "<br>";
                    character += "                Spell Save DC:     ";
                    character += to_string(role->SpellStats()[i]->SpellDC(_abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedModifier()));
                    character += "<br>";
                    character += "                Spells Per Day:    ";
                    character += to_string(role->SpellStats()[i]->SpellsPerDay());
                    character += "<br>";
                    character += "                Bonus Spells:      ";
                    character += to_string(role->SpellStats()[i]->BonusSpells());
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                }
                // Otherwise, if the Character knows at least 1 spell it displays the number of spells known and the Save dc for that level (for if they have spell-like abilities that use that dc) but tells them they arent allowed to cast any spells of that level
                else if (role->SpellStats()[i]->SpellsKnown() != 0 && _abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedScore() < 10 + role->SpellStats()[i]->SpellLevel())
                {

                    character += "            Spell Level:           ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                    character += "                Spells Known:      ";
                    character += to_string(role->SpellStats()[i]->SpellsKnown());
                    character += "<br>";
                    character += "                Spell Save DC:     ";
                    character += to_string(role->SpellStats()[i]->SpellDC(_abilityScores[EnumToIndex(role->SpellStats()[i]->AbilityType())]->AdjustedModifier()));
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                    character += "                You are unable to cast level ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += " spells.";
                    character += "<br>";
                    character += "                You need at least a";
                    if (10 + role->SpellStats()[i]->SpellLevel() == 11 | 10 + role->SpellStats()[i]->SpellLevel() == 18)
                        character += "n";
                    character += " ";
                    character += to_string(10 + role->SpellStats()[i]->SpellLevel());
                    character += " in ";
                    character += EnumToString(role->SpellStats()[i]->AbilityType());
                    character += " to cast level ";
                    character += to_string(role->SpellStats()[i]->SpellLevel());
                    character += " spells as a";
                    if (tolower(role->Name()[0]) == 'a' | tolower(role->Name()[0]) == 'e' | tolower(role->Name()[0]) == 'i' | tolower(role->Name()[0]) == 'o' | tolower(role->Name()[0]) == 'u')
                        character += "n";
                    character += " ";
                    character += role->Name();
                    character += ".";
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                    character += "|";
                    character += "<br>";
                }
            }

            // Adds all the spells known in detail to the string
            character += "        Spells:";
            character += "<br>";
            character += "|";
            character += "<br>";

            for (auto &&spell : role->Spells())
            {
                character += "            Name:                  ";
                character += spell->Name();
                character += "<br>";
                character += "|";
                character += "<br>";
                character += "                Magic School:      ";
                character += EnumToString(spell->School());
                character += "<br>";
                character += "                Level:             ";
                for (auto &&classSpellListItem : spell->Roles())
                {
                    character += EnumToString(classSpellListItem->CasterType());
                    character += " ";
                    character += to_string(classSpellListItem->Level());
                    if (classSpellListItem != spell->Roles().back())
                        character += ", ";
                }
                character += "<br>";
                character += "                Casting Time:      ";
                character += spell->CastingTime();
                character += "<br>";
                character += "                Components:        ";
                character += spell->Components();
                character += "<br>";
                character += "                Range:             ";
                character += spell->Range();
                character += "<br>";
                character += "                Target:            ";
                character += spell->Target();
                character += "<br>";
                character += "                Duration:          ";
                character += spell->Duration();
                character += "<br>";
                character += "                Saving Throw:      ";
                character += spell->SavingThrow();
                character += "<br>";
                character += "                Spell Resistance:  ";
                switch (spell->SpellResistance())
                {
                case true:
                    character += "yes";
                    break;
                default:
                    character += "no";
                    break;
                }
                character += "<br>";
                character += "                Description:       ";
                character += spell->Description();
                character += "<br>";
                character += "|";
                character += "<br>";
            }
        }
    }

#pragma endregion Spells

    return character;
}

short Character::GetAbilityScore(abilityType abilityType)
{
    unique_lock<mutex> lock(_mutex);
    return _abilityScores[EnumToIndex(abilityType)]->Score();
}

short Character::AbilityMod(abilityType abilityType)
{
    unique_lock<mutex> lock(_mutex);
    return _abilityScores[EnumToIndex(abilityType)]->AdjustedModifier();
}

string Character::Proficiencies()
{
    unique_lock<mutex> lock(_mutex);
    return _proficiencies;
}

int Character::GetCurrencyAmount(currencyType currency)
{
    unique_lock<mutex> lock(_mutex);
    return _currency[EnumToIndex(currency)]->Amount();
}

currencyType Character::CurrencyType(short index)
{

    unique_lock<mutex> lock(_mutex);
    return _currency[index]->Type();
}

short Character::Age()
{
    unique_lock<mutex> lock(_mutex);
    return _age;
}

short Character::Height()
{
    unique_lock<mutex> lock(_mutex);
    return _height;
}

short Character::Weight()
{
    unique_lock<mutex> lock(_mutex);
    return _weight;
}

void Character::AbilityScores(short newAbilityScores[6])
{
    unique_lock<mutex> lock(_mutex);
    for (short i = 0; i < 6; i++)
    {
        _abilityScores[i] = make_unique<AbilityScore>(newAbilityScores[i]);
    }
}

void Character::SetRace(string name)
{
    unique_lock<mutex> lock(_mutex);
    _race = make_unique<Race>(name);
}

void Character::Size(sizeType sizeType)
{
    unique_lock<mutex> lock(_mutex);
    _size = sizeType;
}

void Character::SetSpeed(short baseSpeed)
{
    unique_lock<mutex> lock(_mutex);
    _speed = make_unique<Speed>(baseSpeed);
}

void Character::Proficiencies(string proficiencies)
{
    unique_lock<mutex> lock(_mutex);
    _proficiencies = proficiencies;
}

void Character::Languages(string languages)
{
    unique_lock<mutex> lock(_mutex);
    _languages = languages;
}

void Character::SetHitPoints(die hitdie)
{
    unique_lock<mutex> lock(_mutex);
    _hitpoints = make_unique<HitPoints>(hitdie);
}

void Character::SetRoleToCastingClass(short index, abilityType castingAbility)
{
    unique_lock<mutex> lock(_mutex);
    _roles[index]->SetToCastingClass(castingAbility, _abilityScores[EnumToIndex(castingAbility)]->AdjustedModifier());
}

void Character::SetSpellsKnown(short roleIndex, short spellLevel, short spellsKnown)
{
    unique_lock<mutex> lock(_mutex);
    _roles[roleIndex]->SpellStats()[spellLevel]->SpellsKnown(spellsKnown);
}

void Character::SetSpellsPerDay(short roleIndex, short spellLevel, short spellsPerDay)
{
    unique_lock<mutex> lock(_mutex);
    _roles[roleIndex]->SpellStats()[spellLevel]->SpellsPerDay(spellsPerDay);
}

void Character::BaB(unsigned short BaB)
{
    unique_lock<mutex> lock(_mutex);
    _baseAttackBonuses.clear();
    _baseAttackBonuses.emplace_back(BaB);
    // adds base attack bonuses to the vector at 5 less than the previous until the bonus would be 0 or less
    while (BaB > 5)
    {
        BaB -= 5;
        _baseAttackBonuses.emplace_back(BaB);
    }
}

void Character::SetSave(saveType saveType, unsigned short saveValue)
{
    unique_lock<mutex> lock(_mutex);
    _saves[EnumToIndex(saveType)] = make_unique<Save>(saveType, saveValue);
}

void Character::SetCurrency(currencyType currency, int amount)
{
    unique_lock<mutex> lock(_mutex);
    _currency[EnumToIndex(currency)]->Amount(amount);
}

void Character::ArmoredSpeed(unsigned short speed)
{
    unique_lock<mutex> lock(_mutex);
    // If the adjusted armored speed would raise the speed it won't change the displayed speed
    if (speed < _speed->Armored())
    {
        _speed->Armored(speed);
    }
}

void Character::ArmorBonus(short armorBonus)
{
    unique_lock<mutex> lock(_mutex);
    _armorClass->Armor(_armorClass->Armor() + armorBonus);
}

void Character::ShieldBonus(short shieldBonus)
{
    unique_lock<mutex> lock(_mutex);
    _armorClass->Shield(_armorClass->Shield() + shieldBonus);
}

void Character::MiscACBonus(short miscBonus)
{
    unique_lock<mutex> lock(_mutex);
    _armorClass->MiscMod(_armorClass->MiscMod() + miscBonus);
}

void Character::Characteristics(alignment alignment, string playerName, string deity, string homeland, string gender, short age, short height, short weight, string hair, string eyes, string name)
{
    unique_lock<mutex> lock(_mutex);
    _alignment = alignment;
    _player = playerName;
    _deity = deity;
    _homeland = homeland;
    _gender = gender;
    _age = age;
    _height = height;
    _weight = weight;
    _hairColor = hair;
    _eyeColor = eyes;
    _name = name;
}

void Character::AddRacialTrait(shared_ptr<Feat> &&racialTrait)
{
    unique_lock<mutex> lock(_mutex);
    _race->AddRacialTrait(move(racialTrait));
}

void Character::AddRole(string name)
{
    unique_lock<mutex> lock(_mutex);
    _roles.emplace_back(make_unique<Role>(name));
}

void Character::AddClassSkill(skillType skillType)
{
    unique_lock<mutex> lock(_mutex);
    // For each skill it checks if the skill is the one it is supposed to change and if so marks it as a class skill
    for (auto &&skill : _skills)
    {
        if (skill->SkillType() == skillType)
            skill->IsClassSkill(true);
    }
}

short Character::AddSkillRankToSkill(skillType skillType)
{
    unique_lock<mutex> lock(_mutex);
    // For each skill, if it is the one we want to add a rank to and it doesnt already have one, it adds a rank
    for (auto &&skill : _skills)
    {
        if (skill->SkillType() == skillType && skill->Ranks() < 1)
        {
            skill->Ranks(skill->Ranks() + 1);
            return 0;
        }
    }
    return -1;
}

void Character::AddClassFeature(short roleIndex, string name, string description)
{
    unique_lock<mutex> lock(_mutex);
    _roles[roleIndex]->AddClassFeature(name, description);
}

void Character::AddSpell(short roleIndex, shared_ptr<Spell> &&spell)
{
    unique_lock<mutex> lock(_mutex);
    _roles[roleIndex]->AddSpell(move(spell));
}

void Character::AddFeat(unique_ptr<Feat> &&feat)
{
    unique_lock<mutex> lock(_mutex);
    _feats.emplace_back(move(feat));
}

void Character::AddGear(unique_ptr<Gear> &&gear)
{
    unique_lock<mutex> lock(_mutex);
    _gear.emplace_back(move(gear));
}

void Character::AddWeapon(unique_ptr<Weapon> &&weapon)
{
    unique_lock<mutex> lock(_mutex);
    _weapons.emplace_back(move(weapon));
}

void Character::AddArmor(unique_ptr<ArmorClassItem> &&armor)
{
    unique_lock<mutex> lock(_mutex);
    _armorClassItems.emplace_back(move(armor));
}

short Character::CMB()
{
    return _baseAttackBonuses.front() + _abilityScores[0]->AdjustedModifier() + (EnumToBonus(_size) * -1);
}

short Character::CMD()
{
    return _baseAttackBonuses.front() + _abilityScores[0]->AdjustedModifier() + _abilityScores[1]->AdjustedModifier() + (EnumToBonus(_size) * -1) + 10;
}
