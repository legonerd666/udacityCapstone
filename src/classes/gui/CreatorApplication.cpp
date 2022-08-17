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
    GetNumber<short>("What age do you want to be? ", SHRT_MIN, SHRT_MAX);
}

CreatorApplication::~CreatorApplication()
{
    for (auto &&thread : _threads)
    {
        thread.join();
    }
}

template <typename T>
void CreatorApplication::GetNumber(string text, T min, T max)
{
    _isValidInput = false;
    _promptText = root()->addWidget(make_unique<WText>(text));
    _inputField = root()->addWidget(make_unique<WLineEdit>());
    _inputField->setFocus();
    _inputField->enterPressed().connect([this, min, max]
                                        { 
                                            try
                                            {
                                                if (stoi(_inputField->valueText()) >= min && stoi(_inputField->valueText()) <= max){
                                                _character->Characteristics(LG, "Jonathan Joestar", "Pharasma", "Sandpoint", "Male", stoi(_inputField->valueText()), 0, 0, "Brown", "Brown", "Jimothy");
                                                cout << _character->ToStringForConsole();}
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
                                            } });
}