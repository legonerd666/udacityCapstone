#include "../../../include/classes/gui/CreatorApplication.h"
#include <climits>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include "../../../include/classes/gui/CharacterApplication.h"
#include <iostream>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

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
    Intro();
}

void CreatorApplication::Intro()
{
    _promptText->setText("<div style=\"font-size: 2rem\">Welcome to the character creator, I will walk you through creating a character in Pathfinder 1e right here on this site!</div><br><div style=\"font-size: 2rem\">What will happen is as follows: I will ask you questions about the next section in the character sheet, and you will type an appropriate response in the field and press *enter*. Then we repeat this step for the next field.</div><br><div style=\"font-size: 2rem\">After all the required steps have been completed I will do a bit of math and fill out any other fields that don't need your input and display your character sheet here for you to use!</div>");
    _promptText->setTextFormat(TextFormat::UnsafeXHTML);
    _promptText->setTextAlignment(AlignmentFlag::Center);
    WPushButton *begin = root()->addWidget(make_unique<WPushButton>("<div style=\"font-size: 2rem\">Click here to begin!</div>", TextFormat::UnsafeXHTML));
    begin->setWidth(WLength("16%"));
    begin->setMargin(WLength("42%"), Side::Left | Side::Right);
    begin->clicked().connect([this, begin]
                             { cout << "\n\nSTARTING\n\n"; });
    _inputField->setHidden(true);
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