#include <string>

#include "character.h"
#include "../enums.h"

#include <climits>

using namespace std;

character::character()
{
    _name = "Example Name";
    _alignment = LG;
    _player = "Example Player";
    _deity = "Example Deity";
    _homeland = "Example Homeland";
    _gender = "Example Gender";
    _age = 0;
    _height = 0;
    _weight = 0;
    _hairColor = "Example Hair Color";
    _eyeColor = "Example Eye Color";
    _initiative = make_unique<initiative>();
    _armorClass = make_unique<armorClass>();

    _saves[0] = make_unique<save>(fortitude);
    _saves[1] = make_unique<save>(reflex);
    _saves[2] = make_unique<save>(will);

    _skills.emplace_back(make_unique<skill>(acrobatics));
    _skills.emplace_back(make_unique<skill>(appraise));
    _skills.emplace_back(make_unique<skill>(bluff));
    _skills.emplace_back(make_unique<skill>(climb));
    _skills.emplace_back(make_unique<skill>(craft));
    _skills.emplace_back(make_unique<skill>(diplomacy));
    _skills.emplace_back(make_unique<skill>(disableDevice));
    _skills.emplace_back(make_unique<skill>(disguise));
    _skills.emplace_back(make_unique<skill>(escapeArtist));
    _skills.emplace_back(make_unique<skill>(fly));
    _skills.emplace_back(make_unique<skill>(handleAnimal));
    _skills.emplace_back(make_unique<skill>(heal));
    _skills.emplace_back(make_unique<skill>(intimidate));
    _skills.emplace_back(make_unique<skill>(knowArcana));
    _skills.emplace_back(make_unique<skill>(knowDungeoneering));
    _skills.emplace_back(make_unique<skill>(knowEngineering));
    _skills.emplace_back(make_unique<skill>(knowGeography));
    _skills.emplace_back(make_unique<skill>(knowHistory));
    _skills.emplace_back(make_unique<skill>(knowLocal));
    _skills.emplace_back(make_unique<skill>(knowNature));
    _skills.emplace_back(make_unique<skill>(knowNobility));
    _skills.emplace_back(make_unique<skill>(knowPlanes));
    _skills.emplace_back(make_unique<skill>(knowReligion));
    _skills.emplace_back(make_unique<skill>(linguistics));
    _skills.emplace_back(make_unique<skill>(perception));
    _skills.emplace_back(make_unique<skill>(perform));
    _skills.emplace_back(make_unique<skill>(profession));
    _skills.emplace_back(make_unique<skill>(ride));
    _skills.emplace_back(make_unique<skill>(senseMotive));
    _skills.emplace_back(make_unique<skill>(sleightOfHand));
    _skills.emplace_back(make_unique<skill>(spellcraft));
    _skills.emplace_back(make_unique<skill>(stealth));
    _skills.emplace_back(make_unique<skill>(survival));
    _skills.emplace_back(make_unique<skill>(swim));
    _skills.emplace_back(make_unique<skill>(useMagicDevice));
    _baseAttackBonuses.emplace_back(0);
    _spellResistance = 0;

    _currency[0] = make_unique<currency>(copper, 0);
    _currency[1] = make_unique<currency>(silver, 0);
    _currency[2] = make_unique<currency>(gold, 0);
    _currency[3] = make_unique<currency>(platinum, 0);

    _xp = 0;
    _nextLevelXpAmount = 0;
}

// Outputs the character data as a nicely formatted string
string character::ToStringForConsole()
{
    unique_lock<mutex> lock(_mutex);

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
    if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) == 0 && _hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) > -1)
        character += "    You are currently Disabled";
    else if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Unconscious and Dying";
    else if (_hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) <= (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Dead";

    character += "\n";

    character += "|     Current Non-Lethal HP:         ";
    character += to_string(_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()));
    if (_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) == 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > 0)
        character += "    You are currently Staggered";
    else if (_hitpoints->CurrentNonLethalHP(_abilityScores[2]->AdjustedModifier()) < 0 && _hitpoints->CurrentHP(_abilityScores[2]->AdjustedModifier()) > -1)
        character += "    You are currently Unconscious";
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion HitPoints

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

#pragma region Language

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Languages:                         ";
    character += _languages;
    character += "\n";

#pragma endregion Language

#pragma region Combat

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Combat:";
    character += "\n";
    character += "|";
    character += "\n";

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

#pragma region Combat Stats

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

    character += "|     Spell Resistance:              ";
    character += to_string(_spellResistance);
    character += "%";
    character += "\n";
    character += "|";
    character += "\n";

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
        if (_baseAttackBonuses.front() + _abilityScores[EnumToIndex(weapon->AbilityType())]->AdjustedModifier() + EnumToBonus(_size) >= 0)
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
        character += "\n";
        character += "|         Ammo:                      ";
        character += to_string(weapon->Ammo());
        character += "\n";
        character += "|         Damage:                    ";
        character += weapon->Damage();
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

#pragma region Proficiencies

    character += "|     Proficiencies:                 ";
    character += _proficiencies;
    character += "\n";
    character += "|";
    character += "\n";

#pragma endregion Proficiencies

#pragma endregion Combat

#pragma region Equipment

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Equipment and Gear:";
    character += "\n";
    character += "|";
    character += "\n";

#pragma region ACItems
    character += "|     AC Items:";
    character += "\n";
    character += "|";
    character += "\n";
    {
        unsigned short totalBonus = 0;
        unsigned short maxDexBonus = USHRT_MAX;
        unsigned short totalCheckPenalty = 0;
        unsigned short totalSpellFailureChance = 0;
        unsigned short baseSpeedAdjustment = _speed->Base();
        unsigned short totalWeight = 0;
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

#pragma region Gear

    character += "|     Gear:";
    character += "\n";
    character += "|";
    character += "\n";
    {
        unsigned short totalWeight = 0;
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
                if (role->SpellStats()[i]->SpellsKnown() > 0)
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
                    character += "|                 Spells Per Day:    ";
                    character += to_string(role->SpellStats()[i]->SpellsPerDay());
                    character += "\n";
                    character += "|                 Bonus Spells:      ";
                    character += to_string(role->SpellStats()[i]->BonusSpells());
                    character += "\n";
                    character += "|";
                    character += "\n";
                }
            }

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

short character::AbilityMod(abilityType abilityType)
{
    unique_lock<mutex> lock(_mutex);
    return _abilityScores[EnumToIndex(abilityType)]->AdjustedModifier();
}

string character::Proficiencies()
{
    unique_lock<mutex> lock(_mutex);
    return _proficiencies;
}

void character::AbilityScores(short newAbilityScores[6])
{
    unique_lock<mutex> lock(_mutex);
    for (short i = 0; i < 6; i++)
    {
        _abilityScores[i] = make_unique<abilityScore>(newAbilityScores[i]);
    }
}

void character::Race(string name)
{
    unique_lock<mutex> lock(_mutex);
    _race = make_unique<race>(name);
}

void character::Size(sizeType sizeType)
{
    unique_lock<mutex> lock(_mutex);
    _size = sizeType;
}

void character::Speed(short baseSpeed)
{
    unique_lock<mutex> lock(_mutex);
    _speed = make_unique<speed>(baseSpeed);
}

void character::Proficiencies(string proficiencies)
{
    unique_lock<mutex> lock(_mutex);
    _proficiencies = proficiencies;
}

void character::Languages(string languages)
{
    unique_lock<mutex> lock(_mutex);
    _languages = languages;
}

void character::HitPoints(die hitdie)
{
    unique_lock<mutex> lock(_mutex);
    _hitpoints = make_unique<hitPoints>(hitdie);
}

void character::AddRacialTrait(shared_ptr<feat> &&racialTrait)
{
    unique_lock<mutex> lock(_mutex);
    _race->AddRacialTrait(move(racialTrait));
}

void character::AddRole(string name)
{
    unique_lock<mutex> lock(_mutex);
    _roles.emplace_back(make_unique<role>(name));
}

void character::AddClassSkill(skillType skillType)
{
    unique_lock<mutex> lock(_mutex);
    for (auto &&skill : _skills)
    {
        if (skill->SkillType() == skillType)
            skill->IsClassSkill(true);
    }
}

short character::AddSkillRankToSkill(skillType skillType)
{
    unique_lock<mutex> lock(_mutex);
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

short character::CMB()
{
    return _baseAttackBonuses.front() + _abilityScores[0]->AdjustedModifier() + (EnumToBonus(_size) * -1);
}

short character::CMD()
{
    return _baseAttackBonuses.front() + _abilityScores[0]->AdjustedModifier() + _abilityScores[1]->AdjustedModifier() + (EnumToBonus(_size) * -1) + 10;
}
