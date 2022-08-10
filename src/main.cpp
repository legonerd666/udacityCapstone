#include <iostream>

#include "Character.h"
#include "enums.h"
#include "Creator.h"
#include <memory>
#include <ctime>

/**
 * \mainpage
 * @brief A program that creates a custom Pathfinder 1e character sheet
 *
 * Uses the console to gather info from the user to populate a character sheet for Pathfinder 1e and then prints the fully created character sheet to the console.
 *
 * Good places to start: \n
 * Character \n
 * Creator
 */

int main()
{
    srand(time(0));
    std::shared_ptr<Character> testCharacter = make_shared<Character>();
    Creator creator = Creator(testCharacter);
    creator.CreateCharacter();
    std::cout << testCharacter->ToStringForConsole();
    return 0;
}