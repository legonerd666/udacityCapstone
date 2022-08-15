#include "HelloApplication.h"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

HelloApplication::HelloApplication(const WEnvironment &env)
    : WApplication(env)
{
    setTitle("Hello World!");

    root()->addWidget(std::make_unique<WText>("Your name, please? "));
    nameEdit_ = root()->addWidget(std::make_unique<WLineEdit>());
    WPushButton *button = root()->addWidget(std::make_unique<WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<WBreak>());
    greeting_ = root()->addWidget(std::make_unique<WText>());
    auto greet = [this]
    {
        greeting_->setText("Hello there, " + nameEdit_->text() + ".");
    };
    button->clicked().connect(greet);
}