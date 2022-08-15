#ifndef HELLOAPPLICATION_H
#define HELLOAPPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>


using namespace Wt;
/**
 * @brief The main window of the program
 * 
 * Holds all the main window code that displays the text, textinput, button, and response.
 */
class HelloApplication : public WApplication
{
private:
    /**
     * @brief Text box for the user to input their name
     * 
     */
    WLineEdit *nameEdit_;
    /**
     * @brief Text that holds the full greeting for when the button is clicked
     * 
     */
    WText *greeting_;

public:
    /**
     * @brief Construct a new Hello Application object
     * 
     * @param env 
     */
    HelloApplication(const WEnvironment &env);
};

#endif