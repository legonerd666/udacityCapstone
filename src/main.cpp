#include <iostream>
#include <memory>
#include <ctime>
#include <Wt/WApplication.h>

#include "Character.h"
#include "enums.h"
#include "Creator.h"
#include "../include/classes/gui/CharacterApplication.h"
#include "CreatorApplication.h"

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

int main(int argc, char **argv)
{
    srand(time(0));
    std::shared_ptr<Character> testCharacter = make_shared<Character>();
    Creator creator = Creator(testCharacter);
    creator.CreateCharacter();
    return WRun(argc, argv, [testCharacter](const WEnvironment &env)
                { return std::make_unique<CreatorApplication>(env, testCharacter); });
}