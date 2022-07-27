#include "spell.h"

spell::spell()
{
    _name = "Example Spell";
    _school = evocation;
    _casterTypes.emplace_back(sorcererWizard);
    _level = 0;
    _castingTime = "Example Casting Time";
    _components = "V, S, M (Example Material Component)";
    _range = "Example Range";
    _target = "Example Target(s)";
    _duration = "Example Duration";
    _savingThrow = fortitude;
    _spellResistance = false;
    _description = "Example Description";
}

string spell::Name() {}

magicSchool spell::School() {}

vector<casterType> spell::Roles() {}

unsigned short spell::Level() {}

string spell::CastingTime() {}

string spell::Components() {}

string spell::Range() {}

string spell::Target() {}

string spell::Duration() {}

saveType spell::SavingThrow() {}

bool spell::SpellResistance() {}

string spell::Description() {}
