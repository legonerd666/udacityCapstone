#include <iostream>

#include "character.h"
#include "enums.h"
#include "creator.h"
#include <memory>
#include <ctime>

int main()
{
    srand(time(0));
    std::shared_ptr<character> testCharacter = make_shared<character>();
    creator Creator = creator(testCharacter);
    Creator.CreateCharacter();
    std::cout << testCharacter->ToStringForConsole();
    return 0;
}