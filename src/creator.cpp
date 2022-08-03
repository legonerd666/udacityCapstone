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

void creator::Intro(shared_ptr<character> characterSheet)
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
    DelayedCout("Write that ability score on a piece of paper and repeat 5 more times so that you have 6 ability scores written down, ranging from 3 to 18 in value.");
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
    DelayedCout("Now that that's done, it's time to pick your race!");
    DelayedCout("Look in the Pathfinder Core Rulebook and decide which race suits your character most;");
    DelayedCout("Then I'll ask you for all the information about the race and add it to your character sheet!");
    DelayedCout("Let's get a name for your race: ", false);
    string name;
    getline(cin, name, '\n');
    _threads.emplace_back(thread(&character::Race, characterSheet, move(name)));
#pragma region Ability Scores

    {
        short abilityScoreAdjs[6];
        DelayedCout("Since we now have a name, First things first, races often come with minor adjustments to your ability scores, giving one or more stats +2 bonus or a -2 penalty.");
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

#pragma region Racial Traits

    DelayedCout("Now you get to enter any racial traits!");
    RacialTraits(characterSheet);

#pragma endregion Racial Traits

#pragma region Weapon Familiarity

    DelayedCout("Races often get familiarity with some weapons, I'll give you a prompt to write down any and all weapons that you gain proficiency with due to you race.");
    DelayedCout("Weapons: ", false);
    string weapons;
    getline(cin, weapons, '\n');
    _threads.emplace_back(thread([characterSheet, weapons]()
                                 { characterSheet->Proficiencies(weapons); }));

#pragma endregion Weapon Familiarity

#pragma region Languages

    DelayedCout("Each race knows a number of languages by default, you also can pick a number of extra languages based on your intelligence modifier.");
    DelayedCout("These extra languages are chosen from a list given under the races langauges in the Pathfinder 1e Core Rulebook");
    DelayedCout("What languages do you speak by default?");
    DelayedCout("Languages: ", false);
    string languages;
    getline(cin, languages, '\n');
    if (characterSheet->AbilityMod(intelligence) > 0)
    {
        DelayedCout("You get to choose " + to_string(characterSheet->AbilityMod(intelligence)) + " extra languages from your race list!");
        ExtraLanguages(characterSheet, move(languages));
    }
    else
    {
        _threads.emplace_back(thread(&character::Languages, characterSheet, move(languages)));
    }

#pragma endregion Languages

    Role(move(characterSheet));
}

void creator::Role(shared_ptr<character> &&characterSheet)
{
    DelayedCout("Time to select your class! Look in the Pathfinder 1e Core Rulebook for which class you want to play and then I will get that info from you and write it in your character sheet!");
    DelayedCout("Figured out your class? What's it called: ", false);
    string name;
    getline(cin, name, '\n');
    _threads.emplace_back(thread(&character::AddRole, characterSheet, move(name)));
    DelayedCout("Great! Now what hit die does this class use?");
    _threads.emplace_back(thread(&character::HitPoints, characterSheet, move(GetHitDie())));
    DelayedCout("Now I need the skills that are class skills for you.");
    SetClassSkills(characterSheet);
    SetSkillRanks(characterSheet);
    DelayedCout("Classes give you proficiency with different weapons and armors, please input those proficiencies.");
    DelayedCout("Proficiencies: ", false);
    string proficiencies;
    getline(cin, proficiencies, '\n');
    _threads.emplace_back(thread([characterSheet, proficiencies]()
                                 { characterSheet->Proficiencies(characterSheet->Proficiencies() + " " + proficiencies); }));
    IsCastingClass(characterSheet);
    this_thread::sleep_for(chrono::milliseconds(1));
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
    DelayedCout("Y/n: ", false);
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
        if (stoi(speed) >= 0 && stoi(speed) < USHRT_MAX)
            return stoi(speed);
        else
        {
            DelayedCout("Please unsure your speed entered is at least 0 and at most " + to_string(USHRT_MAX - 1) + ".");
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

void creator::RacialTraits(shared_ptr<character> characterSheet)
{
    DelayedCout("Would you like to add a racial trait?");
    DelayedCout("Y/n: ", false);
    string addTrait;
    getline(cin, addTrait, '\n');
    if (tolower(addTrait.front()) == 'y')
    {
        DelayedCout("Lemme know the name of the racial trait and I'll write it down for you: ", false);
        string name;
        getline(cin, name, '\n');
        DelayedCout("Great name! Now you need to tell me what the trait does and then you can make any others if you have more to add.");
        DelayedCout(name + "'s description: ", false);
        string description;
        getline(cin, description, '\n');
        _threads.emplace_back(&character::AddRacialTrait, characterSheet, move(make_shared<feat>(name, description)));
        RacialTraits(move(characterSheet));
    }
    else if (tolower(addTrait.front()) == 'n')
    {
        return;
    }
    else
    {
        DelayedCout("Please answer either Y or n.");
        RacialTraits(move(characterSheet));
    }
    return;
}

void creator::ExtraLanguages(shared_ptr<character> characterSheet, string languages)
{
    for (short i = 0; i < characterSheet->AbilityMod(intelligence); i++)
    {
        DelayedCout("Please enter an extra language from your list: ", false);
        string language;
        getline(cin, language, '\n');
        languages += " ";
        languages += language;
    }
    _threads.emplace_back(thread(&character::Languages, move(characterSheet), languages));
}

die creator::GetHitDie()
{
    DelayedCout("I will give you the option to set your hitdie to one of 4 dice.");
    DelayedCout("The options will be displayed as the letter \"d\" which stands for die.");
    DelayedCout("And then the number which is the highest the die can roll.");
    DelayedCout("For example d4 is a 4-sided die.");
    DelayedCout("1. d6\n2. d8\n3. d10\n4. d12");
    DelayedCout("What is your class's hitdie: ", false);
    string hitdie;
    getline(cin, hitdie, '\n');
    try
    {
        switch (stoi(hitdie))
        {
        case 1:
            return d6;
        case 2:
            return d8;
        case 3:
            return d10;
        case 4:
            return d12;
        default:
            DelayedCout("Umm... I'm gonna need you to give me one of the numbers I showed...");
            DelayedCout("We'll go again, this time answer 1, 2, 3, or 4.");
            return GetHitDie();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Could I maybe get the number of the die you wanted...? Not too sure what you meant by \"" + hitdie + "\"...");
        return GetHitDie();
    }
}

void creator::SetClassSkills(shared_ptr<character> characterSheet)
{
    DelayedCout("Please enter all skills which are class skills for you: ", false);
    string skills;
    getline(cin, skills, '\n');
    skills = " " + skills;
    vector<skillType> skillTypes;
    for (short i = 0; i < skills.size(); i++)
    {
        skills[i] = tolower(skills[i]);
    }
    if (skills.find(" acrobatics") != string::npos)
    {
        skillTypes.emplace_back(acrobatics);
    }
    if (skills.find(" appraise") != string::npos)
    {
        skillTypes.emplace_back(appraise);
    }
    if (skills.find(" bluff") != string::npos)
    {
        skillTypes.emplace_back(bluff);
    }
    if (skills.find(" climb") != string::npos)
    {
        skillTypes.emplace_back(climb);
    }
    if (skills.find(" craft") != string::npos)
    {
        skillTypes.emplace_back(craft);
    }
    if (skills.find(" diplomacy") != string::npos)
    {
        skillTypes.emplace_back(diplomacy);
    }
    if (skills.find(" disable device") != string::npos)
    {
        skillTypes.emplace_back(disableDevice);
    }
    if (skills.find(" disguise") != string::npos)
    {
        skillTypes.emplace_back(disguise);
    }
    if (skills.find(" escape artist") != string::npos)
    {
        skillTypes.emplace_back(escapeArtist);
    }
    if (skills.find(" fly") != string::npos)
    {
        skillTypes.emplace_back(fly);
    }
    if (skills.find(" handle animal") != string::npos)
    {
        skillTypes.emplace_back(handleAnimal);
    }
    if (skills.find(" heal") != string::npos)
    {
        skillTypes.emplace_back(heal);
    }
    if (skills.find(" intimidate") != string::npos)
    {
        skillTypes.emplace_back(intimidate);
    }
    if (skills.find(" knowledge (arcana)") != string::npos)
    {
        skillTypes.emplace_back(knowArcana);
    }
    if (skills.find(" knowledge (dungeoneering)") != string::npos)
    {
        skillTypes.emplace_back(knowDungeoneering);
    }
    if (skills.find(" knowledge (engineering)") != string::npos)
    {
        skillTypes.emplace_back(knowEngineering);
    }
    if (skills.find(" knowledge (geography)") != string::npos)
    {
        skillTypes.emplace_back(knowGeography);
    }
    if (skills.find(" knowledge (history)") != string::npos)
    {
        skillTypes.emplace_back(knowHistory);
    }
    if (skills.find(" knowledge (local)") != string::npos)
    {
        skillTypes.emplace_back(knowLocal);
    }
    if (skills.find(" knowledge (nature)") != string::npos)
    {
        skillTypes.emplace_back(knowNature);
    }
    if (skills.find(" knowledge (nobility)") != string::npos)
    {
        skillTypes.emplace_back(knowNobility);
    }
    if (skills.find(" knowledge (planes)") != string::npos)
    {
        skillTypes.emplace_back(knowPlanes);
    }
    if (skills.find(" knowledge (religion)") != string::npos)
    {
        skillTypes.emplace_back(knowReligion);
    }
    if (skills.find(" knowledge (all)") != string::npos)
    {
        skillTypes.emplace_back(knowArcana);
        skillTypes.emplace_back(knowDungeoneering);
        skillTypes.emplace_back(knowEngineering);
        skillTypes.emplace_back(knowGeography);
        skillTypes.emplace_back(knowHistory);
        skillTypes.emplace_back(knowLocal);
        skillTypes.emplace_back(knowNature);
        skillTypes.emplace_back(knowNobility);
        skillTypes.emplace_back(knowPlanes);
        skillTypes.emplace_back(knowReligion);
    }
    if (skills.find(" linguistics") != string::npos)
    {
        skillTypes.emplace_back(linguistics);
    }
    if (skills.find(" perception") != string::npos)
    {
        skillTypes.emplace_back(perception);
    }
    if (skills.find(" perform") != string::npos)
    {
        skillTypes.emplace_back(perform);
    }
    if (skills.find(" profession") != string::npos)
    {
        skillTypes.emplace_back(profession);
    }
    if (skills.find(" ride") != string::npos)
    {
        skillTypes.emplace_back(ride);
    }
    if (skills.find(" sense motive") != string::npos)
    {
        skillTypes.emplace_back(senseMotive);
    }
    if (skills.find(" sleight of hand") != string::npos)
    {
        skillTypes.emplace_back(sleightOfHand);
    }
    if (skills.find(" spellcraft") != string::npos)
    {
        skillTypes.emplace_back(spellcraft);
    }
    if (skills.find(" stealth") != string::npos)
    {
        skillTypes.emplace_back(stealth);
    }
    if (skills.find(" survival") != string::npos)
    {
        skillTypes.emplace_back(survival);
    }
    if (skills.find(" swim") != string::npos)
    {
        skillTypes.emplace_back(swim);
    }
    if (skills.find(" use magic device") != string::npos)
    {
        skillTypes.emplace_back(useMagicDevice);
    }
    CheckClassSkills(move(characterSheet), move(skillTypes));
}

void creator::CheckClassSkills(shared_ptr<character> characterSheet, vector<skillType> skillTypes)
{
    DelayedCout("To confirm, are these all the skills that are your class skills?");
    for (auto &&skillT : skillTypes)
    {
        DelayedCout(EnumToString(skillT));
    }
    DelayedCout("Y/n: ", false);
    string isCorrect;
    getline(cin, isCorrect, '\n');
    if (tolower(isCorrect[0]) == 'y')
    {
        for (auto &&skillT : skillTypes)
        {
            _threads.emplace_back(thread(&character::AddClassSkill, characterSheet, skillT));
        }
    }
    else if (tolower(isCorrect[0]) == 'n')
    {
        DelayedCout("Ok, I'll let you enter them again, make sure this time that they are all spelled correctly and that knowledge skills are written \"knowledge (category)\" (eg. \"knowledge (arcana) or knowledge (all)\")");
        SetClassSkills(move(characterSheet));
    }
    else
    {
        DelayedCout("Not sure what you mean by that, let's try again.");
        CheckClassSkills(move(characterSheet), move(skillTypes));
    }
}

void creator::SetSkillRanks(shared_ptr<character> characterSheet)
{
    DelayedCout("Ok, now you will need to tell me how many skill ranks your class starts with and then put them into your skills");
    DelayedCout("How many skill ranks does your class start with: ", false);
    string ranks;
    getline(cin, ranks, '\n');
    try
    {
        // This if statement ensures they can't have more ranks than skills which would cause the following for loop to be unable to finish due to the fact that only one rank can be put in each skill
        if (stoi(ranks) + characterSheet->AbilityMod(intelligence) > 35)
        {
            ranks = "35";
        }

        for (int i = stoi(ranks) + characterSheet->AbilityMod(intelligence) - 1; i >= 0; i--)
        {
            AddSkillRankToSkill(characterSheet, i + 1);
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("So, FYI, usually when someone asks for an amount, they are asking for a number.");
        DelayedCout("It's fine, I'll let you enter it again, but this time, please give me the number of skill ranks your class starts with.");
        SetSkillRanks(move(characterSheet));
    }
}

void creator::AddSkillRankToSkill(shared_ptr<character> characterSheet, short ranks)
{
    DelayedCout("You have " + to_string(ranks) + " ranks. Please enter a skill in which you'd like to put a rank: ", false);
    string skill;
    getline(cin, skill, '\n');
    skill = " " + skill;
    for (short i = 0; i < skill.size(); i++)
    {
        skill[i] = tolower(skill[i]);
    }
    if (skill.find(" acrobatics") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(acrobatics) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" appraise") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(appraise) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" bluff") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(bluff) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" climb") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(climb) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" craft") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(craft) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" diplomacy") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(diplomacy) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" disable device") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(disableDevice) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" disguise") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(disguise) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" escape artist") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(escapeArtist) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" fly") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(fly) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" handle animal") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(handleAnimal) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" heal") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(heal) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" intimidate") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(intimidate) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (arcana)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowArcana) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (dungeoneering)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowDungeoneering) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (engineering)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowEngineering) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (geography)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowGeography) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (history)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowHistory) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (local)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowLocal) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (nature)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowNature) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (nobility)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowNobility) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (planes)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowPlanes) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" knowledge (religion)") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(knowReligion) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" linguistics") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(linguistics) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" perception") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(perception) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" perform") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(perform) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" profession") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(profession) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" ride") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(ride) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" sense motive") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(senseMotive) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" sleight of hand") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(sleightOfHand) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" spellcraft") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(spellcraft) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" stealth") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(stealth) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" survival") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(survival) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" swim") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(swim) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else if (skill.find(" use magic device") != string::npos)
    {
        if (characterSheet->AddSkillRankToSkill(useMagicDevice) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(move(characterSheet), ranks);
        }
    }
    else
    {
        DelayedCout("I don't know what skill you mean, could you enter it again please and make sure you spelled it properly? (knowledge skills should be written as such: knowledge (category) eg. knowledge (nature))");
        AddSkillRankToSkill(move(characterSheet), ranks);
    }
}

void creator::IsCastingClass(shared_ptr<character> characterSheet)
{
    DelayedCout("Ok, now I need to know if your class is a casting class.");
    DelayedCout("Is this a casting class? Y/n: ", false);
    string isCastingClass;
    getline(cin, isCastingClass, '\n');
    if (tolower(isCastingClass[0]) == 'y')
    {
        _threads.emplace_back(thread(&character::SetRoleToCastingClass, characterSheet, 0, GetCastingAbility(characterSheet)));
        DelayedCout("Each spell casting class has a description of how spells work for that class under a class feature named \"Spells\".");
        DelayedCout("So, please give me the description (or a shortened version if you'd prefer) of how spells work in your class and I'll write them down in a class feature named spells.");
        DelayedCout("Spells Description: ", false);
        string spellsDesc;
        getline(cin, spellsDesc, '\n');
        _threads.emplace_back(thread(&character::AddClassFeature, characterSheet, 0, "Spells", move(spellsDesc)));
        SetSpellsKnown(characterSheet, 0);
        SetSpellsKnown(characterSheet, 1);
        SetSpellsPerDay(characterSheet, 0);
        SetSpellsPerDay(characterSheet, 1);
    }
    else if (tolower(isCastingClass[0]) != 'n')
    {
        DelayedCout("I don't understand. Please answer Y or n.");
        IsCastingClass(move(characterSheet));
    }
}

abilityType creator::GetCastingAbility(shared_ptr<character> characterSheet)
{
    DelayedCout("What ability score is your class's casting tied to?");
    DelayedCout("1. Intelligence\n2. Wisdom\n3. Charisma");
    DelayedCout("Please enter the number corrensponding to the ability score: ", false);
    string castingAbility;
    getline(cin, castingAbility, '\n');
    try
    {
        if (stoi(castingAbility) == 1)
            return intelligence;
        else if (stoi(castingAbility) == 2)
            return wisdom;
        else if (stoi(castingAbility) == 3)
            return charisma;
        else
        {
            DelayedCout("That wasn't one of the options.");
            return GetCastingAbility(move(characterSheet));
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetCastingAbility(move(characterSheet));
    }
}

void creator::SetSpellsKnown(shared_ptr<character> characterSheet, short spellLevel)
{
    DelayedCout("Now I'll be asking you how many level " + to_string(spellLevel) + " spells you know.");
    DelayedCout("If your class knows all spells of this level please answer \"all\".");
    DelayedCout("If your class doesn't know any spells of this level just answer \"0\".");
    DelayedCout("Some classes (like the wizard) don't have a chart in which you can find your spells known but instead they are written somewhere else (for the wizard it's written in the spellbook section).");
    DelayedCout("Still others do not have spells known and can simply prepare any spell in their spell list (eg. the cleric).");
    DelayedCout("For those just answer \"N/A\" or \"Prepare\".");
    DelayedCout("Lastly some classes (like the wizard) gain extra spells known if the ability they use to cast has a positive modifier.");
    DelayedCout("Make sure to add that number when entering your spells known (never add it if it is a negative modifier).");
    DelayedCout("Keep in mind that this is different from bonus spells which are bonus spells per day not bonus spells known. Those you don't need to worry about as I will enter those for you.");
    DelayedCout("Level " + to_string(spellLevel) + " spells known: ", false);
    string spellsKnown;
    getline(cin, spellsKnown, '\n');
    for (auto &&c : spellsKnown)
    {
        c = tolower(c);
    }
    try
    {
        if (spellsKnown == "n/a" || spellsKnown == "prepare")
            _threads.emplace_back(thread(&character::SetSpellsKnown, characterSheet, 0, move(spellLevel), -2));
        else if (spellsKnown == "all")
            _threads.emplace_back(thread(&character::SetSpellsKnown, characterSheet, 0, move(spellLevel), -1));
        else if (stoi(spellsKnown) >= 0)
            _threads.emplace_back(thread(&character::SetSpellsKnown, characterSheet, 0, move(spellLevel), stoi(spellsKnown)));
        else if (stoi(spellsKnown) < 0)
        {
            DelayedCout("Dude, you can't know negative spells. How would that even work?");
            DelayedCout("We'll go again, and this time, give my a positive number or one of the words I gave you.");
            SetSpellsKnown(move(characterSheet), move(spellLevel));
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I'm sorry, but the options are: A number, \"all\", \"N/A\", and \"Prepare\". Not whatever you just said.");
        DelayedCout("Please try that again.");
        SetSpellsKnown(move(characterSheet), move(spellLevel));
    }
}

void creator::SetSpellsPerDay(shared_ptr<character> characterSheet, short spellLevel)
{
    DelayedCout("Now I'll be asking you how many level " + to_string(spellLevel) + " spells you can cast per day.");
    DelayedCout("All casting classes have their spells per day written in a table with all their other info.");
    DelayedCout("However, some casting classes do not gain the ability to cast spells at level 1.");
    DelayedCout("If your class is one of them then just answer \"0\"");
    DelayedCout("Casting classes also get bonus spells per day based on their casting ability score, don't worry about that as I will handle that for you.");
    DelayedCout("Level " + to_string(spellLevel) + " spells per day: ", false);
    string spellsPerDay;
    getline(cin, spellsPerDay, '\n');
    for (auto &&c : spellsPerDay)
    {
        c = tolower(c);
    }
    try
    {
        if (stoi(spellsPerDay) >= 0)
            _threads.emplace_back(thread(&character::SetSpellsPerDay, characterSheet, 0, move(spellLevel), stoi(spellsPerDay)));
        else if (stoi(spellsPerDay) < 0)
        {
            DelayedCout("Your class should either be able to cast a positive number or 0 spells per day. Check to make sure you read it correctly.");
            DelayedCout("We'll go again, and this time, give my a positive number.");
            SetSpellsPerDay(move(characterSheet), move(spellLevel));
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I'm gonna need the number of spells per day, please.");
        DelayedCout("Let's try that again.");
        SetSpellsPerDay(move(characterSheet), move(spellLevel));
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
