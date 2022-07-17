#include <iostream>

#include "classes/character.h"
#include "enums.h"

int main() {
    character testCharacter;
    std::cout << testCharacter.ToStringForConsole() << std::endl;
    return 0;
}