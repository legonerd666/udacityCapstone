#include <iostream>

#include "classes/character.h"
#include "enums.h"
#include "creator.h"
#include <memory>

int main()
{
    std::unique_ptr<character> testCharacter = make_unique<character>();
    Intro(std::move(testCharacter));
    return 0;
}