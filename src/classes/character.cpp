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
    _armorClass = make_unique<armorClass>();
    for (int i = 0; i < 3; i++) {
        _saves[i] = make_unique<save>();
    }
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
    character += "|-----------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Characteristics: ";
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

    #pragma endregion Characteristics

    #pragma region HitPoints

    character += "|-----------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Hit Points: ";
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

    character += "|-----------------------------------------------------------------------------------------------------";
    character += "\n";

    #pragma endregion HitPoints

    #pragma region Speed

    character += "| Speed: ";
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

    #pragma endregion Speed

    #pragma region AbilityScores

    character += "|-----------------------------------------------------------------------------------------------------";
    character += "\n";

    character += "| Ability Scores: ";
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
    character += "\n";

    #pragma endregion Charisma

    #pragma endregion AbilityScores

    return character;
}