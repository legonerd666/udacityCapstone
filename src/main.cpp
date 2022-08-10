#include <iostream>

#include "character.h"
#include "enums.h"
#include "creator.h"
#include <memory>
#include <ctime>

/**
 * \mainpage
 * @brief A program that creates a custom Pathfinder 1e Character Sheet
 *
 * Uses the console to gather info from the user to populate a character sheet for Pathfinder 1e and then prints the fully created character sheet to the console.
 *
 * Good places to start:
 * character
 * creator
 */

int main()
{
    srand(time(0));
    std::shared_ptr<character> testCharacter = make_shared<character>();
    creator Creator = creator(testCharacter);
    Creator.CreateCharacter();
    std::cout << testCharacter->ToStringForConsole();
    return 0;
}