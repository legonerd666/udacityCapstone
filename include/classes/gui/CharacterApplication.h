#ifndef HELLOAPPLICATION_H
#define HELLOAPPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <string>


using namespace Wt;
/**
 * @brief The main window of the program
 * 
 * Holds all the main window code that displays the character sheet.
 */
class CharacterApplication : public WApplication
{
private:

public:
    /**
     * @brief Construct a new Character Application object
     * 
     * @param env 
     * @param character Holds the string of the character sheet with Html formatting
     */
    CharacterApplication(const WEnvironment &env, std::string character);
};

#endif