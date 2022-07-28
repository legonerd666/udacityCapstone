#include "creator.h"
#include "classes/character.h"
#include "enums.h"

#include <iostream>
#include <memory>
#include <thread>
#include <climits>

using namespace std;

creator::creator() {}

creator::~creator()
{
    for (auto &&thread : _threads)
    {
        thread.join();
    }
}

void creator::Intro(shared_ptr<character> &&characterSheet)
{
    DelayedCout("Welcome to the character creator, I will walk you through creating a character in Pathfinder 1e right here in the console!");
    DelayedCout("What will happen is as follows: I will ask you questions about the next section in the character sheet, and you will type an appropriate response in the console. Then we repeat this step for the next field.");
    DelayedCout("After all the required steps have been completed I will do a bit of math and fill out any other fields that don't need your input and print your new character sheet to the console for you to use!");
    AbilityScores(move(characterSheet));
}

void creator::AbilityScores(shared_ptr<character> &&characterSheet)
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
    Race(move(characterSheet), move(abilityScores));
}

void creator::Race(shared_ptr<character> &&characterSheet, short abilityScores[6])
{
#pragma region Ability Scores

    {
        short abilityScoreAdjs[6];
        DelayedCout("Now that that's done, it's time to pick your race!");
        DelayedCout("Look in the Pathfinder Core Rulebook and decide which race suits your character most;");
        DelayedCout("Then I'll ask you for all the information about the race and add it to your character sheet!");
        DelayedCout("First things first, races often come with minor adjustments to your ability scores, giving one or more stats +2 bonus or a -2 penalty.");
        DelayedCout("Let's add those now.");
        abilityScoreAdjs[0] = GetScoreAdj(strength);
        abilityScoreAdjs[1] = GetScoreAdj(dexterity);
        abilityScoreAdjs[2] = GetScoreAdj(constitution);
        abilityScoreAdjs[3] = GetScoreAdj(intelligence);
        abilityScoreAdjs[4] = GetScoreAdj(wisdom);
        abilityScoreAdjs[5] = GetScoreAdj(charisma);
        for (short i = 0; i < 6; i++)
        {
            abilityScores[i] += abilityScoreAdjs[i];
        }
    }
    _threads.emplace_back(thread(&character::AbilityScores, characterSheet, move(abilityScores)));

#pragma endregion Ability Scores
#pragma region Size

    DelayedCout("Ok, Now let's write down your size!");
    _threads.emplace_back(thread(&character::Size, characterSheet, move(GetSize())));

#pragma endregion Size
#pragma region Speed

    DelayedCout("Time to enter their speed!");
    _threads.emplace_back(thread(&character::Speed, characterSheet, move(GetSpeed())));

#pragma endregion Speed
}

short creator::GetScore(abilityType abilityType)
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

short creator::GetScoreAdj(abilityType abilityType)
{
    DelayedCout("Is your " + EnumToString(abilityType) + " changed by your race?");
    DelayedCout("Y/n:", false);
    string isChanged;
    getline(cin, isChanged, '\n');
    if (tolower(isChanged.front()) == 'y')
    {
        DelayedCout("How would you like to adjust your " + EnumToString(abilityType) + "?");
        DelayedCout("You can either increase it by 2 or decrease it by 2.");
        DelayedCout("Please enter the adjustment you'd like to make: ", false);
        string adj;
        getline(cin, adj, '\n');
        try
        {
            if (stoi(adj) == 2 || stoi(adj) == -2)
            {
                return stoi(adj);
            }
            else
            {
                DelayedCout("Please only give me an answer of 2 or -2. Let's try that again.");
                return GetScoreAdj(abilityType);
            }
        }
        catch (const std::invalid_argument &e)
        {
            DelayedCout("I'm sorry, but I can only use numbers for this. Please give me either 2 or -2.");
            return GetScoreAdj(abilityType);
        }
    }
    else if (tolower(isChanged.front()) == 'n')
    {
        return 0;
    }
    else
    {
        DelayedCout("I'm sorry, I don't understand. Please try again, but this time answer with Y or n.");
        return GetScoreAdj(abilityType);
    }
}

sizeType creator::GetSize()
{
    DelayedCout("There are 9 sizes your race can be:\n1. Fine\n2. Diminutive\n3. Tiny\n4. Small\n5. Medium\n6. Large\n7. Huge\n8. Gargantuan\n9. Colossal");
    DelayedCout("Please pick the number corresponding to the size of your race: ", false);
    string size;
    getline(cin, size, '\n');
    try
    {
        switch (stoi(size))
        {
        case 1:
            return fine;
        case 2:
            return diminutive;
        case 3:
            return tiny;
        case 4:
            return small;
        case 5:
            return medium;
        case 6:
            return large;
        case 7:
            return huge;
        case 8:
            return gargantuan;
        case 9:
            return colossal;
        default:
            DelayedCout("I'm sorry, but I don't have the size corresponding to that number.");
            DelayedCout("We're gonna go again, but this time make sure you enter a number from the list.");
            return GetSize();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Actually, I need the number corresponding to the size. Please enter the number this time.");
        return GetSize();
    }
}

short creator::GetSpeed()
{
    DelayedCout("The base speed in feet per turn of your race is: ", false);
    string speed;
    getline(cin, speed, '\n');
    try
    {
        if (stoi(speed) >= 0 && stoi(speed) <= USHRT_MAX)
            return stoi(speed);
        else
        {
            DelayedCout("Please unsure your speed entered is at least 0 and at most " + to_string(USHRT_MAX) + ".");
            DelayedCout("Let's go again.");
            return GetSpeed();
        }
    }
    catch (const std::exception &e)
    {
        DelayedCout("I jsut need the number of feet per turn, nothing more or less.");
        DelayedCout("Let's try again but this time just give me the number. (eg. 30)");
        return GetSpeed();
    }
}

void creator::DelayedCout(string &&string)
{
    cout << string << endl;
    this_thread::sleep_for(chrono::milliseconds(1));
}

void creator::DelayedCout(string &&string, bool doNewLine)
{
    if (doNewLine)
    {
        cout << string << endl;
    }
    else
    {
        cout << string;
    }
    this_thread::sleep_for(chrono::milliseconds(1));
}
