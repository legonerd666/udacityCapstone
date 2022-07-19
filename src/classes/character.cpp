#include <string>

#include "character.h"
#include "../enums.h"

using namespace std;

character::character() {

    _name = "Example Name";
    _alignment = LG;
    _player = "Example Player";
    _deity = "Example Deity";
    _homeland = "Example Homeland";
    _race = make_unique<race>();
    _gender = "Example Gender";
    _age = 0;
    _height = 0;
    _weight = 0;
    _hairColor = "Example Hair Color";
    _eyeColor = "Example Eye Color";

    for (int i = 0; i < 6; i++) {
        _abilityScores[i] = make_unique<abilityScore>();
    }
    _hitpoints = make_unique<hitPoints>();
    _speed = make_unique<speed>();
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
    _languages = "Example Languages";

    _baseAttackBonuses;
    _spellResistance = 0;
    _proficiencies = "Example Proficiencies";

    for (int i = 0; i < 4; i++) {
        _currency[i] = make_unique<currency>();
    }

    _xp = 0;
    _nextLevelXpAmount = 0;

}

//Outputs the character data as a nicely formatted string
string character::ToStringForConsole()   {

    #pragma region Characteristics

    string character = "";
    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Characteristics: ";
    character += "\n";
    character += "|";
    character += "\n";

    character += "|     Character Name:            ";
    character += _name;
    character += "\n";

    character += "|     Alignment:                 ";
    character += EnumToString(_alignment);
    character += "\n";

    character += "|     Player:                    ";
    character += _player;
    character += "\n";

    character += "|     Class(es):                 ";
    for (auto &&role : _roles) {
        character += role->ToString();
    }
    character += "\n";

    character += "|     Deity:                     ";
    character += _deity;
    character += "\n";

    character += "|     Homeland:                  ";
    character += _homeland;
    character += "\n";

    character += "|     Race:                      ";
    character += _race->ToString();
    character += "\n";

    character += "|     Gender:                    ";
    character += _gender;
    character += "\n";

    character += "|     Age:                       ";
    character += to_string(_age);
    character += "\n";

    character += "|     Height:                    ";
    character += to_string(_height);
    character += "\n";

    character += "|     Weight:                    ";
    character += to_string(_weight);
    character += "\n";

    character += "|     Hair:                      ";
    character += _hairColor;
    character += "\n";

    character += "|     Eyes:                      ";
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

    character += "|     Total HP:                  ";
    character += to_string(_hitpoints->TotalHP());
    character += "\n";

    character += "|     Hit Dice:                  ";
    for (auto &&hitdie : _hitpoints->HitDice()){
        character += hitdie->To_String();
    }
    character += "\n";

    character += "|     Current HP:                ";
    character += to_string(_hitpoints->CurrentHP());
    if (_hitpoints->CurrentHP() == 0 && _hitpoints->CurrentNonLethalHP() > -1)
        character += "    You are currently Disabled";
    else if (_hitpoints->CurrentHP() < 0 && _hitpoints->CurrentHP() > (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Unconscious and Dying";
    else if (_hitpoints->CurrentHP() < 0 && _hitpoints->CurrentHP() <= (_abilityScores[2]->AdjustedScore() * -1))
        character += "    You are Dead";
    
    character += "\n";

    character += "|     Current Non-Lethal HP:     ";
    character += to_string(_hitpoints->CurrentNonLethalHP());
    if (_hitpoints->CurrentNonLethalHP() == 0 && _hitpoints->CurrentHP() > 0)
        character += "    You are currently Staggered";
    else if (_hitpoints->CurrentNonLethalHP() < 0 && _hitpoints->CurrentHP() > -1)
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

    character += "|     Base Speed:                ";
    character += to_string(_speed->Base());
    character += "\n";

    character += "|     Armored Speed:             ";
    character += to_string(_speed->Armored());
    character += "\n";

    character += "|     Fly Speed:                 ";
    character += to_string(_speed->Fly());
    character += "\n";

    character += "|     Swim Speed:                ";
    character += to_string(_speed->Swim());
    character += "\n";

    character += "|     Climb Speed:               ";
    character += to_string(_speed->Climb());
    character += "\n";

    character += "|     Burrow Speed:              ";
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

    character += "|          Score:                ";
    character += to_string(_abilityScores[0]->Score());
    if (_abilityScores[0]->Score() < 10 && _abilityScores[0]->Score() >= 0){
        character += " ";
    }
    
    character += " (";
    if (_abilityScores[0]->Modifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[0]->Modifier());
    character += ")";

    if (_abilityScores[0]->Score() <= 0){
        character += " You cannot move and are unconscious";
    }
    

    character += "\n";

    character += "|          Temp Score:           ";
    character += to_string(_abilityScores[0]->AdjustedScore());
    if (_abilityScores[0]->AdjustedScore() < 10 && _abilityScores[0]->AdjustedScore() >= 0){
        character += " ";
    }
    character += " (";
    if (_abilityScores[0]->AdjustedModifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[0]->AdjustedModifier());
    character += ")";

    if (_abilityScores[0]->AdjustedScore() <= 0){
        character += " You cannot move and are unconscious";
    }

    character += "\n";
    character += "|";
    character += "\n";

    #pragma endregion Strength

    #pragma region Dexterity

    character += "|     Dexterity: ";
    character += "\n";

    character += "|          Score:                ";
    character += to_string(_abilityScores[1]->Score());
    if (_abilityScores[1]->Score() < 10 && _abilityScores[1]->Score() >= 0){
        character += " ";
    }
    
    character += " (";
    if (_abilityScores[1]->Modifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[1]->Modifier());
    character += ")";

    if (_abilityScores[1]->Score() <= 0){
        character += " You cannot move";
    }
    
    character += "\n";

    character += "|          Temp Score:           ";
    character += to_string(_abilityScores[1]->AdjustedScore());
    if (_abilityScores[1]->AdjustedScore() < 10 && _abilityScores[1]->AdjustedScore() >= 0){
        character += " ";
    }
    character += " (";
    if (_abilityScores[1]->AdjustedModifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += ")";

    if (_abilityScores[1]->AdjustedScore() <= 0){
        character += " You cannot move";
    }
    
    character += "\n";
    character += "|";
    character += "\n";

    #pragma endregion Dexterity

    #pragma region Constitution

    character += "|     Constitution: ";
    character += "\n";

    character += "|          Score:                ";
    character += to_string(_abilityScores[2]->Score());
    if (_abilityScores[2]->Score() < 10 && _abilityScores[2]->Score() >= 0){
        character += " ";
    }
    
    character += " (";
    if (_abilityScores[2]->Modifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[2]->Modifier());
    character += ")";

    if (_abilityScores[2]->Score() <= 0){
        character += " You are dead";
    }
    
    character += "\n";

    character += "|          Temp Score:           ";
    character += to_string(_abilityScores[2]->AdjustedScore());
    if (_abilityScores[2]->AdjustedScore() < 10 && _abilityScores[2]->AdjustedScore() >= 0){
        character += " ";
    }
    character += " (";
    if (_abilityScores[2]->AdjustedModifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[2]->AdjustedModifier());
    character += ")";

    if (_abilityScores[2]->AdjustedScore() <= 0){
        character += " You are dead";
    }
    
    character += "\n";
    character += "|";
    character += "\n";

    #pragma endregion Constitution

    #pragma region Intelligence

    character += "|     Intelligence: ";
    character += "\n";

    character += "|          Score:                ";
    character += to_string(_abilityScores[3]->Score());
    if (_abilityScores[3]->Score() < 10 && _abilityScores[3]->Score() >= 0){
        character += " ";
    }
    
    character += " (";
    if (_abilityScores[3]->Modifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[3]->Modifier());
    character += ")";

    if (_abilityScores[3]->Score() <= 0){
        character += " You are comatose";
    }
    
    character += "\n";

    character += "|          Temp Score:           ";
    character += to_string(_abilityScores[3]->AdjustedScore());
    if (_abilityScores[3]->AdjustedScore() < 10 && _abilityScores[3]->AdjustedScore() >= 0){
        character += " ";
    }
    character += " (";
    if (_abilityScores[3]->AdjustedModifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[3]->AdjustedModifier());
    character += ")";

    if (_abilityScores[3]->AdjustedScore() <= 0){
        character += " You are comatose";
    }

    character += "\n";
    character += "|";
    character += "\n";

    #pragma endregion Intelligence

    #pragma region Wisdom

    character += "|     Wisdom: ";
    character += "\n";

    character += "|          Score:                ";
    character += to_string(_abilityScores[4]->Score());
    if (_abilityScores[4]->Score() < 10 && _abilityScores[4]->Score() >= 0){
        character += " ";
    }
    
    character += " (";
    if (_abilityScores[4]->Modifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[4]->Modifier());
    character += ")";

    if (_abilityScores[4]->Score() <= 0){
        character += " You are incapable of rational thought and are unconscious";
    }

    character += "\n";

    character += "|          Temp Score:           ";
    character += to_string(_abilityScores[4]->AdjustedScore());
    if (_abilityScores[4]->AdjustedScore() < 10 && _abilityScores[4]->AdjustedScore() >= 0){
        character += " ";
    }
    character += " (";
    if (_abilityScores[4]->AdjustedModifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[4]->AdjustedModifier());
    character += ")";

    if (_abilityScores[4]->AdjustedScore() <= 0){
        character += " You are incapable of rational thought and are unconscious";
    }

    character += "\n";
    character += "|";
    character += "\n";

    #pragma endregion Wisdom

    #pragma region Charisma

    character += "|     Charisma: ";
    character += "\n";

    character += "|          Score:                ";
    character += to_string(_abilityScores[5]->Score());
    if (_abilityScores[5]->Score() < 10 && _abilityScores[5]->Score() >= 0){
        character += " ";
    }
    
    character += " (";
    if (_abilityScores[5]->Modifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[5]->Modifier());
    character += ")";

    if (_abilityScores[5]->Score() <= 0){
        character += " You are unable to exert yourself in any way and are unconscious";
    }

    character += "\n";

    character += "|          Temp Score:           ";
    character += to_string(_abilityScores[5]->AdjustedScore());
    if (_abilityScores[5]->AdjustedScore() < 10 && _abilityScores[5]->AdjustedScore() >= 0){
        character += " ";
    }
    character += " (";
    if (_abilityScores[5]->AdjustedModifier() >= 0){
       character += "+";
    }
    character += to_string(_abilityScores[5]->AdjustedModifier());
    character += ")";

    if (_abilityScores[5]->AdjustedScore() <= 0){
        character += " You are unable to exert yourself in any way and are unconscious";
    }

    character += "\n";
    character += "|";
    character += "\n";

    #pragma endregion Charisma

    #pragma endregion AbilityScores

    #pragma region Saves

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Saves:                            (Base + Ability + Magic + Misc + Temp)";
    character += "\n";
    character += "|";
    character += "\n";

    for (auto &&save : _saves) {
        character += "|     ";
        character += EnumToString(save->SaveType());
        character += ":";
        character += "\n";
        character += "|          Total Bonus           ";
        {
            short bonus = _abilityScores[EnumToIndex(save->AbilityType())]->AdjustedModifier();
            if (save->Total(bonus) >= 0){
                character += "+";
            }
            character += to_string(save->Total(bonus));
            character += " (";
            character += to_string(save->Base());
            character += " + ";
            character += to_string(bonus);
        }
        character += " + ";
        character += to_string(save->MagicMod());
        character += " + ";
        character += to_string(save->MiscMod());
        character += " + ";
        character += to_string(save->TempMod());
        character += " )";
        character += "\n";
        character += "|";
        character += "\n";
    }
    

    #pragma endregion Saves

    #pragma region Skills

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Skills:                           (Ability + Ranks + Misc + (3 if you have at least 1 rank and it's a class skill))";
    character += "\n";
    character += "|";
    character += "\n";

    for (auto &&skill : _skills) {
        character += "|    ";
        character += EnumToString(skill->SkillType());
        character += ":";
        character += "\n";
        character += "|          Total Bonus:          ";
        {
            short bonus = _abilityScores[EnumToIndex(skill->AbilityType())]->AdjustedModifier();
            if (skill->Total(bonus) >= 0) {
                character += "+";
            }
            character += to_string(skill->Total(bonus));
            character += " (";
            character += to_string(bonus);
        }
        character += " + ";
        character += to_string(skill->Ranks());
        character += " + ";
        character += to_string(skill->MiscMod());
        if (skill->IsClassSkill() && skill->Ranks() > 0) {
            character += " + 3";
        }
        character += ")";
        character += "\n";
        character += "|";
        character += "\n";
    }
    

    #pragma endregion Skills

    #pragma region Combat

    character += "|--------------------------------------------------------------------------------------------------------------------";
    character += "\n";
    character += "| Combat:";
    character += "\n";
    character += "|";
    character += "\n";

    #pragma region Initiative
    
    character += "|     Initiative:                ";
    if (_initiative->Total(_abilityScores[1]->AdjustedModifier()) >= 0) {
        character += "+";
    }
    character += to_string(_initiative->Total(_abilityScores[1]->AdjustedModifier()));
    character += " (";
    character += to_string(_abilityScores[1]->AdjustedModifier());
    character += " + ";
    character += to_string(_initiative->MiscMod());
    character += ") (Dex + Misc)";
    character += "\n";

    #pragma endregion Initiative

    #pragma endregion Combat

    return character;
}