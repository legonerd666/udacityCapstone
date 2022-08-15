#include "../../../include/classes/gui/CharacterApplication.h"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <string>

using namespace std;

CharacterApplication::CharacterApplication(const WEnvironment &env, string character)
    : WApplication(env)
{
    setTitle("Pathfinder 1e Character!");
    auto text = make_unique<WText>(character);
    text->setTextFormat(TextFormat::UnsafeXHTML);
    root()->addWidget(move(text));
}