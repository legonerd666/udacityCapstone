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
    return "Hello World!";
}