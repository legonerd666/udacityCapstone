#include "../../../include/classes/gui/CreatorApplication.h"
#include <climits>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include "../../../include/classes/gui/CharacterApplication.h"
#include <iostream>
#include <Wt/WText.h>

using namespace std;
using namespace Wt;
CreatorApplication::CreatorApplication(const WEnvironment &env, shared_ptr<Character> character) : WApplication(env), _character(character)
{
    setTitle("Pathfinder 1e Character Creator");
    _promptText = root()->addWidget(make_unique<WText>(""));
    _inputField = root()->addWidget(make_unique<WLineEdit>());
    CreateCharacter();
}

template <typename T>
bool CreatorApplication::IsValidNumber(T min, T max)
{
    try
    {
        if (stoi(_inputField->valueText()) >= min && stoi(_inputField->valueText()) <= max)
            return true;
        else
            _inputField->setValueText("");
    }
    catch (const std::invalid_argument &e)
    {
        _inputField->setValueText("");
    }
    catch (const std::out_of_range &e)
    {
        _inputField->setValueText("");
    }
    return false;
}

void CreatorApplication::CreateCharacter()
{
    SetAge();
}

void CreatorApplication::SetAge()
{
    _promptText->setText("What is your character's age? ");
    _inputField->setFocus();
    _inputField->enterPressed().connect([this]
                                        {
                                            if (IsValidNumber<short>(SHRT_MIN, SHRT_MAX))
                                            {
                                                _character->Characteristics(LG, "Jonathan Joestar", "Pharasma", "Sandpoint", "Male", stoi(_inputField->valueText()), 0, 0, "Brown", "Brown", "Jimothy");
                                                _inputField->setValueText("");
                                                SetHeight();
                                            } });
}

void CreatorApplication::SetHeight()
{
    _promptText->setText("What is your character's height? ");
    root()->removeWidget(_inputField);
    _inputField = root()->addWidget(make_unique<WLineEdit>());
    _inputField->setFocus();
    _inputField->enterPressed().connect([this]
                                        {
                                            if (IsValidNumber<short>(SHRT_MIN, SHRT_MAX))
                                            {
                                                _character->Characteristics(LG, "Jonathan Joestar", "Pharasma", "Sandpoint", "Male", _character->Age(), stoi(_inputField->valueText()), 0, "Brown", "Brown", "Jimothy");
                                                _inputField->setValueText("");
                                                SetWeight();
                                            } });
}

void CreatorApplication::SetWeight()
{
    _promptText->setText("What is your character's weight? ");
    root()->removeWidget(_inputField);
    _inputField = root()->addWidget(make_unique<WLineEdit>());
    _inputField->setFocus();
    _inputField->enterPressed().connect([this]
                                        {
                                            if (IsValidNumber<short>(SHRT_MIN, SHRT_MAX))
                                            {
                                                _character->Characteristics(LG, "Jonathan Joestar", "Pharasma", "Sandpoint", "Male", _character->Age(), _character->Height(), stoi(_inputField->valueText()), "Brown", "Brown", "Jimothy");
                                                _inputField->setValueText("");
                                                setTitle("Pathfinder 1e Character!");
                                                root()->clear();
                                                root()->addWidget(make_unique<WText>(_character->ToStringForWeb(), TextFormat::UnsafeXHTML));
                                            } });
}