#include "creator.h"
#include "classes/character.h"
#include "enums.h"

#include <iostream>
#include <memory>
#include <thread>

using namespace std;

void Intro(unique_ptr<character> &&character)
{
    DelayedCout("Welcome to the character creator, I will walk you through creating a character in Pathfinder 1e right here in the console!");
    DelayedCout("What will happen is as follows: I will ask you questions about the next section in the character sheet, and you will type an appropriate response in the console. Then we repeat this step for the next field.");
    DelayedCout("After all the required steps have been completed I will do a bit of math and fill out any other fields that don't need your input and print your new character sheet to the console for you to use!");
    AbilityScores(move(character));
}

void AbilityScores(unique_ptr<character> &&character)
{
    short abilityScores[6];
    DelayedCout("First up: ability scores!");
    DelayedCout("Roll 4 six-sided dice and take away the lowest die, then add up the remaining 3 dice to get an ability score!");
    DelayedCout("Write that ability score on a piece of paper and repeat 5 more times so that you have 6 ability scores written down, ranging from 3 to 18 ion value.");
    DelayedCout("Figure out which scores you want to use each number for (strength, dexterity, constitution, intelligence, wisdom, and charisma) or you can do them in the order you rolled them.");
    DelayedCout("Now that you've chosen the order to use them in:");
    abilityScores[0] = GetScore(strength);
    abilityScores[1] = GetScore(dexterity);
    abilityScores[2] = GetScore(constitution);
    abilityScores[3] = GetScore(intelligence);
    abilityScores[4] = GetScore(wisdom);
    abilityScores[5] = GetScore(charisma);
    character->AbilityScores(abilityScores);
}

short GetScore(abilityType abilityType)
{
    DelayedCout("What do you want your " + EnumToString(abilityType) + " to be: ", false);
    string score;
    getline(cin, score, '\n');
    try
    {
        if (stoi(score) >= 3 && stoi(score) <= 18)
        {
            return stoi(score);
        }
        else
        {
            DelayedCout("Sorry, but the answer you gave wasn't a number from 3 to 18, let's start over. This time please give me a number from 3 to 18.");
            return GetScore(abilityType);
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Sorry, but the answer you gave wasn't a number, let's start over. This time please give me a number.");
        return GetScore(abilityType);
    }
}

void DelayedCout(string &&string)
{
    cout << string << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void DelayedCout(string &&string, bool doNewLine)
{
    if (doNewLine)
    {
        cout << string << endl;
    }
    else
    {
        cout << string;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}