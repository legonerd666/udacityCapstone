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
string character::ToString()   {
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

    
    character += "\n";

    return character;
}