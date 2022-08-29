#include "../../../include/classes/gui/CreatorApplication.h"
#include <climits>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include "../../../include/classes/gui/CharacterApplication.h"
#include <iostream>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <vector>

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
                             { root()->removeWidget(begin);
                                SetAbilityScores(); });
    _inputField->setHidden(true);
    begin->setFocus();
}

void CreatorApplication::SetAbilityScores()
{
    vector<WLineEdit *> scores;
    vector<WText *> warnings;
    for (short i = 0; i < 6; i++)
    {
        warnings.emplace_back(root()->addWidget(make_unique<WText>("<div style=\"font-size: 1rem; color: red;\">Please ensure that this field is either empty or contains a number from 3 to 18.</div>", TextFormat::UnsafeXHTML)));
        scores.emplace_back(root()->addWidget(make_unique<WLineEdit>()));
        warnings.at(i)->setTextAlignment(AlignmentFlag::Center);
        warnings.at(i)->setHidden(true);
        scores.at(i)->setWidth(WLength("16%"));
        scores.at(i)->setMargin(WLength("42%"), Side::Left | Side::Right);
        scores.at(i)->setMargin(WLength("1%"), Side::Bottom);
    }

    for (short i = 0; i < 5; i++)
    {
        scores.at(i)->enterPressed().connect([this, scores, i]
                                             { scores.at(i + 1)->setFocus(); });
    }

    scores.at(0)->setFocus();

    WPushButton *enterScores = root()->addWidget(make_unique<WPushButton>("<div style=\"font-size: 2rem\">Enter Scores!</div>", TextFormat::UnsafeXHTML));
    _promptText->setText("<div style=\"font-size: 2rem\">First up: ability scores!</div><br><div style=\"font-size: 2rem\">Roll 4 six-sided dice and take away the lowest die, then add up the remaining 3 dice to get an ability score!</div><br><div style=\"font-size: 2rem\">Write that ability score on a piece of paper and repeat 5 more times so that you have 6 ability scores written down, ranging from 3 to 18 in value.</div><br><div style=\"font-size: 2rem\">Figure out which scores you want to use each number for (strength, dexterity, constitution, intelligence, wisdom, and charisma) or you can do them in the order you rolled them.</div><br><div style=\"font-size: 2rem\">If you just want random ability scores then don't enter anything and I'll generate them for you.</div><br><div style=\"font-size: 2rem\">Once you are ready just click the button and I'll add them to your character sheet!</div>");

    scores.at(0)->setPlaceholderText("Strength");
    scores.at(1)->setPlaceholderText("Dexterity");
    scores.at(2)->setPlaceholderText("Constitution");
    scores.at(3)->setPlaceholderText("Intelligence");
    scores.at(4)->setPlaceholderText("Wisdom");
    scores.at(5)->setPlaceholderText("Charisma");

    scores.at(5)->enterPressed().connect([this, enterScores]
                                         { enterScores->setFocus(); });

    enterScores->setWidth(WLength("16%"));
    enterScores->setMargin(WLength("42%"), Side::Left | Side::Right);
    enterScores->clicked().connect([this, scores, warnings, enterScores]
                                   { CheckAbilityScores(scores, warnings, enterScores); });
}

void CreatorApplication::SetRace()
{
    vector<WCheckBox *> scoreCheckboxes;
    for (short i = 0; i < 18; i++)
    {

        if (i % 3 == 0)
        {
            WText *label = root()->addWidget(make_unique<WText>());
            label->setMargin(WLength("45%"), Side::Left);
            switch (i)
            {
            case 0:
                label->setText("Str:");
                label->setMargin(WLength("1.4%"), Side::Right);
                break;
            case 3:
                label->setText("Dex:");
                label->setMargin(WLength("1%"), Side::Right);
                break;
            case 6:
                label->setText("Con:");
                label->setMargin(WLength("1%"), Side::Right);
                break;
            case 9:
                label->setText("Int:");
                label->setMargin(WLength("1.4%"), Side::Right);
                break;
            case 12:
                label->setText("Wis:");
                label->setMargin(WLength("1%"), Side::Right);
                break;
            case 15:
                label->setText("Cha:");
                label->setMargin(WLength("1%"), Side::Right);
                break;
            default:
                break;
            }
            root()->addWidget(make_unique<WText>("-2: "));
        }
        else if (i % 3 == 1)
            root()->addWidget(make_unique<WText>(" 0: "));
        else
            root()->addWidget(make_unique<WText>(" +2: "));

        scoreCheckboxes.emplace_back(root()->addWidget(make_unique<WCheckBox>()));

        if ((i + 1) % 3 == 0)
            root()
                ->addWidget(make_unique<WBreak>());
    }

    for (short i = 0; i < 18; i++)
    {
        if (i % 3 == 0)
            scoreCheckboxes.at(i)->checked().connect([this, scoreCheckboxes, i]
                                                     { scoreCheckboxes.at(i + 1)->setUnChecked();
                                                       scoreCheckboxes.at(i + 2)->setUnChecked();
                                                       scoreCheckboxes.at(i)->setDisabled(true);
                                                       scoreCheckboxes.at(i + 1)->setDisabled(false);
                                                       scoreCheckboxes.at(i + 2)->setDisabled(false); });
        else if (i % 3 == 1)
        {
            scoreCheckboxes.at(i)->setChecked();
            scoreCheckboxes.at(i)->setDisabled(true);
            scoreCheckboxes.at(i)->checked().connect([this, scoreCheckboxes, i]
                                                     { scoreCheckboxes.at(i - 1)->setUnChecked();
                                                       scoreCheckboxes.at(i + 1)->setUnChecked();
                                                       scoreCheckboxes.at(i)->setDisabled(true);
                                                       scoreCheckboxes.at(i - 1)->setDisabled(false);
                                                       scoreCheckboxes.at(i + 1)->setDisabled(false); });
        }
        else
            scoreCheckboxes.at(i)->checked().connect([this, scoreCheckboxes, i]
                                                     { scoreCheckboxes.at(i - 2)->setUnChecked();
                                                       scoreCheckboxes.at(i - 1)->setUnChecked();
                                                       scoreCheckboxes.at(i)->setDisabled(true);
                                                       scoreCheckboxes.at(i - 2)->setDisabled(false);
                                                       scoreCheckboxes.at(i - 1)->setDisabled(false); });
    }

    _promptText->setText("<div style=\"font-size: 2rem\">Now that that's done, it's time to pick your race!</div><br><div style=\"font-size: 2rem\">Look in the Pathfinder Core Rulebook and decide which race suits your character most.</div><br><div style=\"font-size: 2rem\">Then I'll ask you for all the information about the race and add it to your character sheet!</div><br><div style=\"font-size: 2rem\">Let's get a name for your race: </div>");
}

void CreatorApplication::CheckAbilityScores(vector<WLineEdit *> scores, vector<WText *> warnings, WPushButton *enterScores)
{
    bool allValid = true;
    for (short i = 0; i < 6; i++)
    {
        try
        {
            if (stoi(scores.at(i)->valueText()) < 3 || stoi(scores.at(i)->valueText()) > 18)
            {
                allValid = false;
                scores.at(i)->setValueText("");
                warnings.at(i)->setHidden(false);
            }
            else if (stoi(scores.at(i)->valueText()) >= 3 || stoi(scores.at(i)->valueText()) <= 18)
                warnings.at(i)->setHidden(true);
        }
        catch (const std::invalid_argument &e)
        {
            if (scores.at(i)->valueText() != "")
            {
                allValid = false;
                scores.at(i)->setValueText("");
                warnings.at(i)->setHidden(false);
            }
            else
                warnings.at(i)->setHidden(true);
        }
        catch (const std::out_of_range &e)
        {
            allValid = false;
            scores.at(i)->setValueText("");
            warnings.at(i)->setHidden(false);
        }
    }
    if (allValid)
    {
        short abilityScores[6];
        for (short i = 0; i < 6; i++)
        {
            if (scores.at(i)->valueText() == "")
            {
                ushort rolls[4];
                rolls[0] = (rand() % 6) + 1;
                rolls[1] = (rand() % 6) + 1;
                rolls[2] = (rand() % 6) + 1;
                rolls[3] = (rand() % 6) + 1;
                sort(begin(rolls), end(rolls));
                abilityScores[i] = rolls[1] + rolls[2] + rolls[3];
            }
            else
            {
                abilityScores[i] = stoi(scores.at(i)->valueText());
            }
        }
        _character->AbilityScores(abilityScores);
        for (auto &&score : scores)
        {
            root()->removeWidget(score);
        }
        for (auto &&warning : warnings)
        {
            root()->removeWidget(warning);
        }
        root()->removeWidget(enterScores);
        SetRace();
    }
    else
        scores.at(0)->setFocus();
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