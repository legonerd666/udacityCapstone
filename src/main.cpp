#include <iostream>

#include "classes/character.h"
#include "enums.h"
#include "creator.h"
#include <memory>

int main()
{
    std::shared_ptr<character> testCharacter = make_shared<character>();
    creator Creator = creator(testCharacter);
    std::cout << testCharacter->ToStringForConsole();
    return 0;
}