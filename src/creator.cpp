#include "creator.h"
#include "classes/character.h"
#include "enums.h"

#include <iostream>
#include <memory>
#include <thread>
#include <climits>

using namespace std;

creator::creator(shared_ptr<character> character) : _character(character)
{
    Intro();
    AbilityScores();
    Race();
    Role();
    Feats();
    Equipment();
    Characteristics();
}

creator::~creator()
{
    for (auto &&thread : _threads)
    {
        thread.join();
    }
}

void creator::Intro()
{
    DelayedCout("Welcome to the character creator, I will walk you through creating a character in Pathfinder 1e right here in the console!");
    DelayedCout("What will happen is as follows: I will ask you questions about the next section in the character sheet, and you will type an appropriate response in the console. Then we repeat this step for the next field.");
    DelayedCout("After all the required steps have been completed I will do a bit of math and fill out any other fields that don't need your input and print your new character sheet to the console for you to use!");
}

void creator::AbilityScores()
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

    _character->AbilityScores(move(abilityScores));
}

void creator::Race()
{
    DelayedCout("Now that that's done, it's time to pick your race!");
    DelayedCout("Look in the Pathfinder Core Rulebook and decide which race suits your character most;");
    DelayedCout("Then I'll ask you for all the information about the race and add it to your character sheet!");
    DelayedCout("Let's get a name for your race: ", false);
    string name;
    getline(cin, name, '\n');
    _threads.emplace_back(thread(&character::Race, _character, move(name)));
#pragma region Ability Scores

    short abilityScores[6];
    abilityScores[0] = _character->AbilityScore(strength);
    abilityScores[1] = _character->AbilityScore(dexterity);
    abilityScores[2] = _character->AbilityScore(constitution);
    abilityScores[3] = _character->AbilityScore(intelligence);
    abilityScores[4] = _character->AbilityScore(wisdom);
    abilityScores[5] = _character->AbilityScore(charisma);
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
    _character->AbilityScores(move(abilityScores));

#pragma endregion Ability Scores

#pragma region Size

    DelayedCout("Ok, Now let's write down your size!");
    _threads.emplace_back(thread(&character::Size, _character, move(GetSize())));

#pragma endregion Size

#pragma region Speed

    DelayedCout("Time to enter their speed!");
    _threads.emplace_back(thread(&character::Speed, _character, move(GetSpeed())));

#pragma endregion Speed

#pragma region Racial Traits

    DelayedCout("Now you get to enter any racial traits!");
    RacialTraits();

#pragma endregion Racial Traits

#pragma region Weapon Familiarity

    DelayedCout("Races often get familiarity with some weapons, I'll give you a prompt to write down any and all weapons that you gain proficiency with due to you race.");
    DelayedCout("Weapons: ", false);
    string weapons;
    getline(cin, weapons, '\n');
    _character->Proficiencies(weapons);

#pragma endregion Weapon Familiarity

#pragma region Languages

    DelayedCout("Each race knows a number of languages by default, you also can pick a number of extra languages based on your intelligence modifier.");
    DelayedCout("These extra languages are chosen from a list given under the races langauges in the Pathfinder 1e Core Rulebook");
    DelayedCout("What languages do you speak by default?");
    DelayedCout("Languages: ", false);
    string languages;
    getline(cin, languages, '\n');
    // Lets you pick a number of extra languages based on your intelligence modifier
    if (_character->AbilityMod(intelligence) > 0)
    {
        DelayedCout("You get to choose " + to_string(_character->AbilityMod(intelligence)) + " extra languages from your race list!");
        ExtraLanguages(move(languages));
    }
    else
    {
        _threads.emplace_back(thread(&character::Languages, _character, move(languages)));
    }

#pragma endregion Languages
}

void creator::Role()
{
    DelayedCout("Time to select your class! Look in the Pathfinder 1e Core Rulebook for which class you want to play and then I will get that info from you and write it in your character sheet!");
    DelayedCout("Figured out your class? What's it called: ", false);
    string name;
    getline(cin, name, '\n');
    // Initializes your role
    _threads.emplace_back(thread(&character::AddRole, _character, move(name)));
    DelayedCout("Great! Now what hit die does this class use?");
    // Adds Hitpoints
    _threads.emplace_back(thread(&character::HitPoints, _character, move(GetHitDie())));
    DelayedCout("Now I need the skills that are class skills for you.");
    // Sets Class Skills
    SetClassSkills();
    // Sets Skill Ranks
    SetSkillRanks();
    DelayedCout("Classes give you proficiency with different weapons and armors, please input those proficiencies.");
    DelayedCout("Proficiencies: ", false);
    string proficiencies;
    getline(cin, proficiencies, '\n');
    // Sets Proficiencies
    _character->Proficiencies(_character->Proficiencies() + " " + proficiencies);
    // Sets class as casting class if desired
    IsCastingClass();
    // Sets Base Attack Bonuses
    _threads.emplace_back(thread(&character::BaB, _character, GetBaB()));
    // Sets Saves
    _threads.emplace_back(thread(&character::Save, _character, fortitude, GetSave(fortitude)));
    _threads.emplace_back(thread(&character::Save, _character, reflex, GetSave(reflex)));
    _threads.emplace_back(thread(&character::Save, _character, will, GetSave(will)));
    DelayedCout("Ok, time for the final step of choosing your class: Entering in your class features!");
    // Sets Class Features
    AddClassFeatures();
}

void creator::Feats()
{
    DelayedCout("Ok now we are gonna go through and add your feats. All characters start at level 1 with 1 feat. Some races and classes may get extras.");
    // Sets Feats
    AddFeat();
}

void creator::Equipment()
{
    DelayedCout("Great, we are nearing the finish line!");
    DelayedCout("Time to choose your starting equipment!");
    // Sets Gold
    SetGold();
    // Sets Weapons
    AddWeapon();
    // Sets Armor
    AddArmor();
    // Sets Gear
    AddGear();
}

void creator::Characteristics()
{
    DelayedCout("Great Job!! We are now on the last step!");
    DelayedCout("Just fill in your characters characteristics and we will be all done and ready to play!");
    alignment alignment = GetAlignment();
    string playerName;
    DelayedCout("What is the name of the person who plans to play this character (probably your name): ", false);
    getline(cin, playerName, '\n');
    string deity;
    DelayedCout("What is the name of the deity your character believes in (if any): ", false);
    getline(cin, deity, '\n');
    string homeland;
    DelayedCout("What is the name of your characters homeland: ", false);
    getline(cin, homeland, '\n');
    string gender;
    DelayedCout("What gender is your character: ", false);
    getline(cin, gender, '\n');
    short age = GetAge();
    short height = GetHeight();
    short weight = GetWeight();
    string hair;
    DelayedCout("What is your characters hair color: ", false);
    getline(cin, hair, '\n');
    string eyes;
    DelayedCout("What is your characters eye color: ", false);
    getline(cin, eyes, '\n');
    string name;
    DelayedCout("And finally...");
    DelayedCout("What is your characters...");
    DelayedCout("Name: ", false);
    getline(cin, name, '\n');
    // Sets All Characteristics
    _threads.emplace_back(thread(&character::Characteristics, _character, move(alignment), move(playerName), move(deity), move(homeland), move(gender), move(age), move(height), move(weight), move(hair), move(eyes), move(name)));
    DelayedCout("Ok, great, lemme just fill out everything else.");
    DelayedCout("...");
    DelayedCout("...");
    DelayedCout("...");
    DelayedCout("...");
    DelayedCout("...");
    DelayedCout("Ok, all done, whenever you are ready I will display your new character!");
    DelayedCout("Click <Enter> To View Your Character");
    string enter;
    getline(cin, enter, '\n');
    return;
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
        if (stoi(speed) >= 0 && stoi(speed) < SHRT_MAX)
            return stoi(speed);
        else
        {
            DelayedCout("Please unsure your speed entered is at least 0 and at most " + to_string(SHRT_MAX - 1) + ".");
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

void creator::RacialTraits()
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
        _threads.emplace_back(&character::AddRacialTrait, _character, move(make_shared<feat>(name, description)));
        RacialTraits();
    }
    else if (tolower(addTrait.front()) == 'n')
    {
        return;
    }
    else
    {
        DelayedCout("Please answer either Y or n.");
        RacialTraits();
    }
    return;
}

void creator::ExtraLanguages(string languages)
{
    for (short i = 0; i < _character->AbilityMod(intelligence); i++)
    {
        DelayedCout("Please enter an extra language from your list: ", false);
        string language;
        getline(cin, language, '\n');
        languages += " ";
        languages += language;
    }
    _threads.emplace_back(thread(&character::Languages, _character, languages));
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

void creator::SetClassSkills()
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
    CheckClassSkills(move(skillTypes));
}

void creator::CheckClassSkills(vector<skillType> skillTypes)
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
            _threads.emplace_back(thread(&character::AddClassSkill, _character, skillT));
        }
    }
    else if (tolower(isCorrect[0]) == 'n')
    {
        DelayedCout("Ok, I'll let you enter them again, make sure this time that they are all spelled correctly and that knowledge skills are written \"knowledge (category)\" (eg. \"knowledge (arcana) or knowledge (all)\")");
        SetClassSkills();
    }
    else
    {
        DelayedCout("Not sure what you mean by that, let's try again.");
        CheckClassSkills(move(skillTypes));
    }
}

void creator::SetSkillRanks()
{
    DelayedCout("Ok, now you will need to tell me how many skill ranks your class starts with and then put them into your skills");
    DelayedCout("How many skill ranks does your class start with: ", false);
    string ranks;
    getline(cin, ranks, '\n');
    try
    {
        // This if statement ensures they can't have more ranks than skills which would cause the following for loop to be unable to finish due to the fact that only one rank can be put in each skill
        if (stoi(ranks) + _character->AbilityMod(intelligence) > 35)
        {
            ranks = "35";
        }

        for (int i = stoi(ranks) + _character->AbilityMod(intelligence) - 1; i >= 0; i--)
        {
            AddSkillRankToSkill(i + 1);
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("So, FYI, usually when someone asks for an amount, they are asking for a number.");
        DelayedCout("It's fine, I'll let you enter it again, but this time, please give me the number of skill ranks your class starts with.");
        SetSkillRanks();
    }
}

void creator::AddSkillRankToSkill(short ranks)
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
        if (_character->AddSkillRankToSkill(acrobatics) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" appraise") != string::npos)
    {
        if (_character->AddSkillRankToSkill(appraise) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" bluff") != string::npos)
    {
        if (_character->AddSkillRankToSkill(bluff) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" climb") != string::npos)
    {
        if (_character->AddSkillRankToSkill(climb) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" craft") != string::npos)
    {
        if (_character->AddSkillRankToSkill(craft) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" diplomacy") != string::npos)
    {
        if (_character->AddSkillRankToSkill(diplomacy) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" disable device") != string::npos)
    {
        if (_character->AddSkillRankToSkill(disableDevice) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" disguise") != string::npos)
    {
        if (_character->AddSkillRankToSkill(disguise) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" escape artist") != string::npos)
    {
        if (_character->AddSkillRankToSkill(escapeArtist) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" fly") != string::npos)
    {
        if (_character->AddSkillRankToSkill(fly) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" handle animal") != string::npos)
    {
        if (_character->AddSkillRankToSkill(handleAnimal) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" heal") != string::npos)
    {
        if (_character->AddSkillRankToSkill(heal) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" intimidate") != string::npos)
    {
        if (_character->AddSkillRankToSkill(intimidate) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (arcana)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowArcana) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (dungeoneering)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowDungeoneering) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (engineering)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowEngineering) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (geography)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowGeography) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (history)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowHistory) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (local)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowLocal) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (nature)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowNature) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (nobility)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowNobility) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (planes)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowPlanes) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" knowledge (religion)") != string::npos)
    {
        if (_character->AddSkillRankToSkill(knowReligion) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" linguistics") != string::npos)
    {
        if (_character->AddSkillRankToSkill(linguistics) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" perception") != string::npos)
    {
        if (_character->AddSkillRankToSkill(perception) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" perform") != string::npos)
    {
        if (_character->AddSkillRankToSkill(perform) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" profession") != string::npos)
    {
        if (_character->AddSkillRankToSkill(profession) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" ride") != string::npos)
    {
        if (_character->AddSkillRankToSkill(ride) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" sense motive") != string::npos)
    {
        if (_character->AddSkillRankToSkill(senseMotive) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" sleight of hand") != string::npos)
    {
        if (_character->AddSkillRankToSkill(sleightOfHand) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" spellcraft") != string::npos)
    {
        if (_character->AddSkillRankToSkill(spellcraft) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" stealth") != string::npos)
    {
        if (_character->AddSkillRankToSkill(stealth) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" survival") != string::npos)
    {
        if (_character->AddSkillRankToSkill(survival) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" swim") != string::npos)
    {
        if (_character->AddSkillRankToSkill(swim) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else if (skill.find(" use magic device") != string::npos)
    {
        if (_character->AddSkillRankToSkill(useMagicDevice) == -1)
        {
            DelayedCout("I'm sorry, but you can't put more ranks in a skill than you character level and since we are creating a 1st level character that means only 1 skill rank per skill.");
            DelayedCout("You'll have to pick a different skill.");
            AddSkillRankToSkill(ranks);
        }
    }
    else
    {
        DelayedCout("I don't know what skill you mean, could you enter it again please and make sure you spelled it properly? (knowledge skills should be written as such: knowledge (category) eg. knowledge (nature))");
        AddSkillRankToSkill(ranks);
    }
}

void creator::IsCastingClass()
{
    DelayedCout("Ok, now I need to know if your class is a casting class.");
    DelayedCout("Is this a casting class? Y/n: ", false);
    string isCastingClass;
    getline(cin, isCastingClass, '\n');
    if (tolower(isCastingClass[0]) == 'y')
    {
        // Sets role to casting class and sets up spellstats with bonus spells
        _character->SetRoleToCastingClass(0, GetCastingAbility());
        DelayedCout("Each spell casting class has a description of how spells work for that class under a class feature named \"Spells\".");
        DelayedCout("So, please give me the description (or a shortened version if you'd prefer) of how spells work in your class and I'll write them down in a class feature named spells.");
        DelayedCout("Spells Description: ", false);
        string spellsDesc;
        getline(cin, spellsDesc, '\n');
        // Adds class feature for spell casting
        _threads.emplace_back(thread(&character::AddClassFeature, _character, 0, "Spells", move(spellsDesc)));
        // Sets spells known and spells per day for spell levels 0 and 1
        SetSpellsKnown(0);
        SetSpellsKnown(1);
        SetSpellsPerDay(0);
        SetSpellsPerDay(1);
        // Adds all the characters spells to the character
        AddSpell();
    }
    else if (tolower(isCastingClass[0]) != 'n')
    {
        DelayedCout("I don't understand. Please answer Y or n.");
        IsCastingClass();
    }
}

abilityType creator::GetCastingAbility()
{
    DelayedCout("What ability score is your class's casting tied to?");
    DelayedCout("1. Intelligence\n2. Wisdom\n3. Charisma");
    DelayedCout("Please enter the number corrensponding to the ability score: ", false);
    string castingAbility;
    getline(cin, castingAbility, '\n');
    try
    {
        // Only allows mental ability to be selected as a casting ability
        if (stoi(castingAbility) == 1)
            return intelligence;
        else if (stoi(castingAbility) == 2)
            return wisdom;
        else if (stoi(castingAbility) == 3)
            return charisma;
        else
        {
            DelayedCout("That wasn't one of the options.");
            return GetCastingAbility();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetCastingAbility();
    }
}

void creator::SetSpellsKnown(short spellLevel)
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
        // Sets spells known to a number which is then used to dynamically display the spells known in the characters ToStringForConsole function
        if (spellsKnown == "n/a" || spellsKnown == "prepare")
            _threads.emplace_back(thread(&character::SetSpellsKnown, _character, 0, move(spellLevel), -2));
        else if (spellsKnown == "all")
            _threads.emplace_back(thread(&character::SetSpellsKnown, _character, 0, move(spellLevel), -1));
        else if (stoi(spellsKnown) >= 0)
            _threads.emplace_back(thread(&character::SetSpellsKnown, _character, 0, move(spellLevel), stoi(spellsKnown)));
        else if (stoi(spellsKnown) < 0)
        {
            DelayedCout("Dude, you can't know negative spells. How would that even work?");
            DelayedCout("We'll go again, and this time, give my a positive number or one of the words I gave you.");
            SetSpellsKnown(move(spellLevel));
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I'm sorry, but the options are: A number, \"all\", \"N/A\", and \"Prepare\". Not whatever you just said.");
        DelayedCout("Please try that again.");
        SetSpellsKnown(move(spellLevel));
    }
}

void creator::SetSpellsPerDay(short spellLevel)
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
            _threads.emplace_back(thread(&character::SetSpellsPerDay, _character, 0, move(spellLevel), stoi(spellsPerDay)));
        else if (stoi(spellsPerDay) < 0)
        {
            DelayedCout("Your class should either be able to cast a positive number or 0 spells per day. Check to make sure you read it correctly.");
            DelayedCout("We'll go again, and this time, give my a positive number.");
            SetSpellsPerDay(move(spellLevel));
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I'm gonna need the number of spells per day, please.");
        DelayedCout("Let's try that again.");
        SetSpellsPerDay(move(spellLevel));
    }
}

void creator::AddSpell()
{
    DelayedCout("Let's add all your known spells! (For the sake of brevity I won't be explaining much about each field, I'll simply ask for what you'd like it to be.)");
    DelayedCout("All the fields are explained in the Pathfinder 1e Core Rulebook in the chapter on spells.");
    DelayedCout("Would you like to add a spell?");
    DelayedCout("Y/n: ", false);
    string addSpell;
    getline(cin, addSpell, '\n');
    if (tolower(addSpell[0]) == 'y')
    {
        DelayedCout("What is the spell called: ", false);
        string name;
        getline(cin, name, '\n');
        magicSchool school = GetSchool();
        DelayedCout("Ok, now I need you to tell me which classes can utilize this spell and what level spell it is for that class.");
        vector<shared_ptr<classSpellListItem>> roles;
        GetRoles(roles);
        if (roles.size() == 0)
        {
            roles.emplace_back(make_shared<classSpellListItem>());
        }
        DelayedCout("What is the spells casting time: ", false);
        string castingTime;
        getline(cin, castingTime, '\n');
        DelayedCout("What are the spells components: ", false);
        string components;
        getline(cin, components, '\n');
        DelayedCout("What is the spells range: ", false);
        string range;
        getline(cin, range, '\n');
        DelayedCout("What is the spells target: ", false);
        string target;
        getline(cin, target, '\n');
        DelayedCout("What is the spells duration: ", false);
        string duration;
        getline(cin, duration, '\n');
        DelayedCout("What is the spells saving throw: ", false);
        string savingThrow;
        getline(cin, savingThrow, '\n');
        bool spellResistance = GetSpellResistance();
        DelayedCout("What is the spells description: ", false);
        string description;
        getline(cin, description, '\n');
        // Adds a spell object with all its member variables to the character
        _threads.emplace_back(thread(&character::AddSpell, _character, 0, move(make_shared<spell>(move(name), move(school), move(roles), move(castingTime), move(components), move(range), move(target), move(duration), move(savingThrow), move(spellResistance), move(description)))));
        AddSpell();
    }
    else if (tolower(addSpell[0] != 'n'))
    {
        DelayedCout("I need you to answer Y or n.");
        AddSpell();
    }
}

magicSchool creator::GetSchool()
{
    DelayedCout("What is the magic school of this spell?");
    DelayedCout("1. Abjuration\n2. Conjuration\n3. Divination\n4. Enchantment\n5. Evocation\n6. Illusion\n7. Necromancy\n8. Transmutation\n9. Universal");
    DelayedCout("Please enter the number corresponding to the spells magic school: ", false);
    string school;
    getline(cin, school, '\n');
    try
    {
        switch (stoi(school))
        {
        case 1:
            return abjuration;
        case 2:
            return conjuration;
        case 3:
            return divination;
        case 4:
            return enchantment;
        case 5:
            return evocation;
        case 6:
            return illusion;
        case 7:
            return necromancy;
        case 8:
            return transmutation;
        case 9:
            return universal;
        default:
            DelayedCout("I need one of the numbers listed above.");
            return GetSchool();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need you to enter a number.");
        return GetSchool();
    }
}

void creator::GetRoles(vector<shared_ptr<classSpellListItem>> &roles)
{
    DelayedCout("Would you like to add a class?");
    DelayedCout("Y/n: ", false);
    string addRole;
    getline(cin, addRole, '\n');
    if (tolower(addRole[0]) == 'y')
    {
        casterType casterType = GetCasterType();
        unsigned short level = GetLevel();
        auto role = make_shared<classSpellListItem>(move(casterType), move(level));
        roles.emplace_back(move(role));
        GetRoles(roles);
    }
    else if (tolower(addRole[0]) != 'n')
    {
        DelayedCout("I don't know what you want me to do.");
        GetRoles(roles);
    }
}

casterType creator::GetCasterType()
{
    DelayedCout("What is the casting class spell list that you would like to enter?");
    DelayedCout("1. Bard\n2. Cleric\n3. Druid\n4. Paladin\n5. Ranger\n6. Sorcerer/Wizard");
    DelayedCout("Please enter the number corresponding to the casting class spell list: ", false);
    string castingClass;
    getline(cin, castingClass, '\n');
    try
    {
        switch (stoi(castingClass))
        {
        case 1:
            return bard;
        case 2:
            return cleric;
        case 3:
            return druid;
        case 4:
            return paladin;
        case 5:
            return ranger;
        case 6:
            return sorcererWizard;
        default:
            DelayedCout("I need one of the numbers listed above.");
            return GetCasterType();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need you to enter a number.");
        return GetCasterType();
    }
}

unsigned short creator::GetLevel()
{

    DelayedCout("What is the level of the spell in the spell list of the class you just entered: ", false);
    string level;
    getline(cin, level, '\n');
    try
    {
        if (stoi(level) >= 0 && stoi(level) <= 9)
            return stoi(level);
        else
        {
            DelayedCout("You can't enter a negative level or a level above 9.");
            return GetLevel();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need you to enter a number.");
        return GetLevel();
    }
}

bool creator::GetSpellResistance()
{
    DelayedCout("Is this spell affected by spell resistance?");
    DelayedCout("Y/n: ", false);
    string spellResistance;
    getline(cin, spellResistance, '\n');
    if (tolower(spellResistance[0]) == 'y')
        return true;
    else if (tolower(spellResistance[0]) == 'n')
        return false;
    else
    {
        DelayedCout("Please answer Y or n.");
        return GetSpellResistance();
    }
}

unsigned short creator::GetBaB()
{
    DelayedCout("Now I need your base attack bonus.");
    DelayedCout("What is your class's base attack bonus: ", false);
    string BaB;
    getline(cin, BaB, '\n');
    try
    {
        if (stoi(BaB) >= 0 && stoi(BaB) < USHRT_MAX)
            return stoi(BaB);
        else
        {
            DelayedCout("You aren't allowed a negative or exceptionally large Base Attack Bonus.");
            DelayedCout("Please give me a positive value.");
            return GetBaB();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetBaB();
    }
}

unsigned short creator::GetSave(saveType saveType)
{
    DelayedCout("Now I need your base " + EnumToString(saveType) + " save.");
    DelayedCout("What is your class's base save: ", false);
    string save;
    getline(cin, save, '\n');
    try
    {
        if (stoi(save) >= 0 && stoi(save) < USHRT_MAX)
            return stoi(save);
        else
        {
            DelayedCout("You aren't allowed a negative or exceptionally large base save.");
            DelayedCout("Please give me a positive value.");
            return GetSave(saveType);
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetSave(saveType);
    }
}

void creator::AddClassFeatures()
{
    DelayedCout("Would you like to add a class feature?");
    DelayedCout("Y/n: ", false);
    string addClassFeature;
    getline(cin, addClassFeature, '\n');
    if (tolower(addClassFeature[0]) == 'y')
    {
        DelayedCout("Please tell me the name of the class feature: ", false);
        string name;
        getline(cin, name, '\n');
        DelayedCout("Ok, now the description: ", false);
        string description;
        getline(cin, description, '\n');
        _threads.emplace_back(thread(&character::AddClassFeature, _character, 0, move(name), move(description)));
        AddClassFeatures();
    }
    else if (tolower(addClassFeature[0]) != 'n')
    {
        DelayedCout("Not sure how to respond to that...");
        AddClassFeatures();
    }
}

void creator::AddFeat()
{
    DelayedCout("Is there a feat you want to add?");
    DelayedCout("Y/n: ", false);
    string addFeat;
    getline(cin, addFeat, '\n');
    if (tolower(addFeat[0] == 'y'))
    {
        string name;
        string description;
        DelayedCout("What is the name of the feat: ", false);
        getline(cin, name, '\n');
        DelayedCout("What is its description: ", false);
        getline(cin, description, '\n');
        _threads.emplace_back(thread(&character::AddFeat, _character, make_unique<feat>(name, description)));
        AddFeat();
    }
    else if (tolower(addFeat[0]) != 'n')
    {
        DelayedCout("Could. Not. Parse. An-swer.");
        DelayedCout("Lol, just kidding, its not like I'm some sort of weird robot or smth.");
        DelayedCout("...");
        DelayedCout("Aaaaaaaaaaaanyway...");
        DelayedCout("Ima need you to answer either Y or n.");
        AddFeat();
    }
}

void creator::SetGold()
{
    DelayedCout("All characters start out with a random amount of gold to spend based on their class.");
    DelayedCout("So what you'll do is look in the Pathfinder 1e Core Rulebook and on the first page it will list a number of a specific sided die to roll and then multiply that number by 10.");
    DelayedCout("That's how many gold pieces you have to spend on equipment!");
    DelayedCout("So roll those dice and multiply the result by 10 and enter it here and I'll add it to your gold reserves to spend on gear.");
    DelayedCout("Gold Pieces: ", false);
    string goldPieces;
    getline(cin, goldPieces, '\n');
    try
    {
        stoi(goldPieces);
        _character->Currency(gold, stoi(goldPieces));
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the amount of gold as a number.");
        SetGold();
    }
}

string creator::FormattedCurrencies()
{
    string currencies = "You currently have: ";
    for (short i = 0; i < 4; i++)
    {
        currencies += to_string(_character->Currency(_character->CurrencyType(i)));
        currencies += " ";
        currencies += EnumToString(_character->CurrencyType(i));
        currencies += " piece";
        if (_character->Currency(_character->CurrencyType(i)) != 1)
            currencies += "s";
        if (i < 3)
            currencies += ", ";
        else
            currencies += ".";
    }
    return currencies;
}

void creator::AddWeapon()
{
    DelayedCout("Great! Now that you have all your money set up lets purchase some weaponry!");
    DelayedCout(FormattedCurrencies());
    DelayedCout("Would you like to purchase a weapon?");
    DelayedCout("Y/n: ", false);
    string addWeapon;
    getline(cin, addWeapon, '\n');
    if (tolower(addWeapon[0]) == 'y')
    {
        currencyType costType = GetCurrencyType();
        int cost = GetCost();
        // Ensures that the user has enough funds to purchase the weapon
        if (SubtractCost(move(costType), move(cost)) == -1)
        {
            DelayedCout("You can't afford that.");
            AddWeapon();
        }
        else
        {
            string name;
            DelayedCout("Ok, and what's the name of the weapon: ", false);
            getline(cin, name, '\n');
            short nOfDice = GetNDice();
            die damageDie = GetDie();
            string critRange;
            DelayedCout("What is the critical range of your weapon: ", false);
            getline(cin, critRange, '\n');
            string range;
            DelayedCout("What is the range increment of your weapon: ", false);
            getline(cin, range, '\n');
            unsigned short weight = GetWeight();
            string damageType;
            DelayedCout("What is the Damage Type of your weapon: ", false);
            getline(cin, damageType, '\n');
            abilityType abilityType = GetAbilityType();
            short ammo = GetAmmo();
            string description;
            DelayedCout("Ok, this is the last thing I'll need you to tell me about your weapon.");
            DelayedCout("Please write down any special properties and/or a description of the weapon: ", false);
            getline(cin, description, '\n');

            // Adds the weapon to both gear and weapons
            _threads.emplace_back(thread(&character::AddGear, _character, make_unique<gear>(name, description, move(weight))));
            _threads.emplace_back(thread(&character::AddWeapon, _character, make_unique<weapon>(move(name), move(critRange), move(damageType), move(range), move(damageDie), move(nOfDice), move(abilityType), move(ammo))));
            AddWeapon();
        }
    }
    else if (tolower(addWeapon[0]) != 'n')
    {
        DelayedCout("Could you run that by me again? Perhaps using one of the response options I asked for?");
        DelayedCout("Thanks.");
        AddWeapon();
    }
}

void creator::AddArmor()
{
    DelayedCout("Great! Now let's purchase the armor you are gonna wear!");
    DelayedCout("Keep in mind this is just what you'll be wearing, you can purchase more armor that you want to bring with but don't wear immediately later.");
    DelayedCout(FormattedCurrencies());
    DelayedCout("Would you like to purchase some armor?");
    DelayedCout("Y/n: ", false);
    string addArmor;
    getline(cin, addArmor, '\n');
    if (tolower(addArmor[0]) == 'y')
    {
        currencyType costType = GetCurrencyType();
        int cost = GetCost();
        // Ensures the user has sufficient funds to purchase the armor
        if (SubtractCost(move(costType), move(cost)) == -1)
        {
            DelayedCout("You can't afford that.");
            AddArmor();
        }
        else
        {
            string name;
            DelayedCout("Ok, and what's the name of the armor: ", false);
            getline(cin, name, '\n');
            string actype;
            DelayedCout("Ok, and is it a piece of armor or a shield: ", false);
            getline(cin, actype, '\n');
            unsigned short aCBonus = GetACBonus();
            unsigned short maxDex = GetMaxDex();
            short checkPenalty = GetCheckPenalty();
            unsigned short spellFailureChance = GetSpellFailureChance();
            unsigned short baseSpeedAdjustment = GetBaseSpeedAdjustment();
            unsigned short weight = GetWeight();
            string description;
            DelayedCout("Ok, this is the last thing I'll need you to tell me about your armor.");
            DelayedCout("Please write down any special properties and/or a description of the armor: ", false);
            getline(cin, description, '\n');

            for (auto &&c : actype)
            {
                c = tolower(c);
            }
            if (actype == "armor")
            {
                _threads.emplace_back(thread(&character::ArmorBonus, _character, aCBonus));
                actype[0] = 'A';
            }
            else if (actype == "shield")
            {
                _threads.emplace_back(thread(&character::ShieldBonus, _character, aCBonus));
                actype[0] = 'S';
            }
            else
            {
                _threads.emplace_back(thread(&character::MiscACBonus, _character, aCBonus));
                actype[0] = toupper(actype[0]);
            }
            // Adds the armor to armor class items and gear and adds its' bonus to the characters' armor class
            _threads.emplace_back(thread(&character::ArmoredSpeed, _character, baseSpeedAdjustment));
            _threads.emplace_back(thread(&character::AddGear, _character, make_unique<gear>(name, description, weight)));
            _threads.emplace_back(thread(&character::AddArmor, _character, make_unique<armorClassItem>(move(name), move(actype), move(aCBonus), move(maxDex), move(checkPenalty), move(spellFailureChance), move(baseSpeedAdjustment), move(weight), move(description))));
            AddArmor();
        }
    }
    else if (tolower(addArmor[0]) != 'n')
    {
        DelayedCout("Could you run that by me again? Perhaps using one of the response options I asked for?");
        DelayedCout("Thanks.");
        AddArmor();
    }
}

void creator::AddGear()
{
    DelayedCout("Almost done with equipment!");
    DelayedCout("Now just enter in any extra gear you'd like to buy including any armor or weapons you didn't add earlier.");
    DelayedCout("You also start with an outfit worth 10 gold or less if you choose so.");
    DelayedCout("If you choose to add that then just enter in the cost as 0");
    DelayedCout(FormattedCurrencies());
    DelayedCout("Would you like to purchase some gear?");
    DelayedCout("Y/n: ", false);
    string addGear;
    getline(cin, addGear, '\n');
    if (tolower(addGear[0]) == 'y')
    {
        currencyType costType = GetCurrencyType();
        int cost = GetCost();
        // Ensures the user has enough money to afford the piece of gear
        if (SubtractCost(move(costType), move(cost)) == -1)
        {
            DelayedCout("You can't afford that.");
            AddGear();
        }
        else
        {
            string name;
            DelayedCout("Ok, and what's the name of the gear: ", false);
            getline(cin, name, '\n');
            unsigned short weight = GetWeight();
            string description;
            DelayedCout("Ok, this is the last thing I'll need you to tell me about your gear.");
            DelayedCout("Please write down any special properties and/or a description of the gear: ", false);
            getline(cin, description, '\n');
            // Adds the item to gear
            _threads.emplace_back(thread(&character::AddGear, _character, make_unique<gear>(name, description, weight)));
            AddGear();
        }
    }
    else if (tolower(addGear[0]) != 'n')
    {
        DelayedCout("*wails uncontrollably* I- Don't- Understaaaaaand");
        AddGear();
    }
}

currencyType creator::GetCurrencyType()
{
    DelayedCout("First things first: Does this cost Copper, Silver, Gold, Or Platinum: ", false);
    string costType;
    getline(cin, costType, '\n');
    for (auto &&c : costType)
    {
        c = tolower(c);
    }
    if (costType == "copper")
        return copper;
    else if (costType == "silver")
        return silver;
    else if (costType == "gold")
        return gold;
    else if (costType == "platinum")
        return platinum;
    else
    {
        DelayedCout("I don't know that currency, please choose one of those listed above and make sure to spell it properly.");
        return GetCurrencyType();
    }
}

int creator::GetCost()
{
    DelayedCout("What's its cost in the aforementioned currency: ", false);
    string cost;
    getline(cin, cost, '\n');
    try
    {
        if (stoi(cost) >= 0)
            return stoi(cost);
        else
        {
            DelayedCout("You can't have an item cost a negative amount.");
            return GetCost();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I'm sorry, but I asked for a number. Not whatever that ridiculousness was.");
        return GetCost();
    }
}

int creator::SubtractCost(currencyType &&currencyType, int &&cost)
{
    if (_character->Currency(currencyType) < cost)
    {
        int CPs = _character->Currency(copper);
        int SPs = _character->Currency(silver);
        int GPs = _character->Currency(gold);
        int PPs = _character->Currency(platinum);

        switch (currencyType)
        {
        case copper:
            while (CPs < cost)
            {
                if (SPs > 0)
                {
                    SPs--;
                    CPs += 10;
                }
                else if (GPs > 0)
                {
                    GPs--;
                    SPs += 9;
                    CPs += 10;
                }
                else if (PPs > 0)
                {
                    PPs--;
                    GPs += 9;
                    SPs += 9;
                    CPs += 10;
                }
                else
                {
                    return -1;
                }
            }
            _character->Currency(copper, CPs - cost);
            _character->Currency(silver, SPs);
            _character->Currency(gold, GPs);
            _character->Currency(platinum, PPs);
            return 0;
        case silver:
            while (SPs < cost)
            {
                if (CPs >= 10)
                {
                    CPs -= 10;
                    SPs++;
                }
                else if (GPs > 0)
                {
                    GPs--;
                    SPs += 10;
                }
                else if (PPs > 0)
                {
                    PPs--;
                    GPs += 9;
                    SPs += 10;
                }
                else
                {
                    return -1;
                }
            }
            _character->Currency(copper, CPs);
            _character->Currency(silver, SPs - cost);
            _character->Currency(gold, GPs);
            _character->Currency(platinum, PPs);
            return 0;
        case gold:
            while (GPs < cost)
            {
                if (CPs >= 100)
                {
                    CPs -= 100;
                    GPs++;
                }
                else if (SPs >= 10)
                {
                    SPs -= 10;
                    GPs++;
                }
                else if (PPs > 0)
                {
                    PPs--;
                    GPs += 10;
                }
                else
                {
                    return -1;
                }
            }
            _character->Currency(copper, CPs);
            _character->Currency(silver, SPs);
            _character->Currency(gold, GPs - cost);
            _character->Currency(platinum, PPs);
            return 0;
        case platinum:
            while (PPs < cost)
            {
                if (CPs >= 1000)
                {
                    CPs -= 1000;
                    PPs++;
                }
                else if (SPs >= 100)
                {
                    SPs -= 100;
                    PPs++;
                }
                else if (GPs >= 10)
                {
                    GPs -= 10;
                    PPs++;
                }
                else
                {
                    return -1;
                }
            }
            _character->Currency(copper, CPs);
            _character->Currency(silver, SPs);
            _character->Currency(gold, GPs);
            _character->Currency(platinum, PPs - cost);
            return 0;
        default:
            return -1;
        }
    }
    else
    {
        _character->Currency(currencyType, _character->Currency(currencyType) - cost);
        return 0;
    }
}

short creator::GetNDice()
{
    DelayedCout("How many damage dice are rolled for the weapon: ", false);
    string numberOfDice;
    getline(cin, numberOfDice, '\n');
    try
    {
        if (stoi(numberOfDice) > 0)
            return stoi(numberOfDice);
        else
        {
            DelayedCout("Your weapon must roll at least 1 damage die.");
            return GetNDice();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the number of dice.");
        return GetNDice();
    }
}

die creator::GetDie()
{
    DelayedCout("What damage die does the weapon use (please give me the number corresponding to the sides the die has): ", false);
    string damageDie;
    getline(cin, damageDie, '\n');
    try
    {
        switch (stoi(damageDie))
        {
        case 2:
            return d2;
        case 3:
            return d3;
        case 4:
            return d4;
        case 6:
            return d6;
        case 8:
            return d8;
        case 10:
            return d10;
        case 12:
            return d12;
        case 20:
            return d20;
        default:
            DelayedCout("Please give me a damage die of 2, 3, 4, 6, 8, 10, 12, or 20. (I don't think there are any d20 weapons, but who am I to stop you?).");
            return GetDie();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Sir/Ma'am, I need the number of sides on the damage die your weapon uses.");
        return GetDie();
    }
}

unsigned short creator::GetWeight()
{
    DelayedCout("How much does it weigh in pounds: ", false);
    string weight;
    getline(cin, weight, '\n');
    try
    {
        if (stoi(weight) >= 0 && stoi(weight) <= USHRT_MAX)
            return stoi(weight);
        else
        {
            DelayedCout("Please don't give my a negative weight or a weight above 65535.");
            return GetWeight();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Number!");
        return GetWeight();
    }
}

abilityType creator::GetAbilityType()
{
    DelayedCout("What ability does this use to attack.");
    DelayedCout("Ability Score: ", false);
    string ability;
    getline(cin, ability, '\n');
    for (auto &&c : ability)
    {
        c = tolower(c);
    }

    if (ability == "strength")
        return strength;
    else if (ability == "dexterity")
        return dexterity;
    else if (ability == "constitution")
        return constitution;
    else if (ability == "intelligence")
        return intelligence;
    else if (ability == "wisdom")
        return wisdom;
    else if (ability == "charisma")
        return charisma;
    else
    {
        DelayedCout("...");
        DelayedCout("...");
        DelayedCout("...");
        DelayedCout("I need the name of an ability score...");
        return GetAbilityType();
    }
}

short creator::GetAmmo()
{
    DelayedCout("Does this weapon use ammo?");
    DelayedCout("Y/n: ", false);
    string usesAmmo;
    getline(cin, usesAmmo, '\n');
    if (tolower(usesAmmo[0]) == 'y')
    {
        if (WillBuyAmmo())
        {
            short AmmoAmount = GetAmmoAmount();
            currencyType currency = GetCurrencyType();
            DelayedCout("How much does it cost to buy the amount of that ammo?");
            int cost = GetCost();
            // Ensures they can afford that amount of ammo
            if (SubtractCost(move(currency), move(cost)) == -1)
            {
                DelayedCout("You can't afford that.");
                return GetAmmo();
            }
            else
            {
                DelayedCout("How much does that amount of ammo weigh?");
                unsigned short weight = GetWeight();
                string name;
                DelayedCout("What's this ammo called: ", false);
                getline(cin, name, '\n');
                string description;
                DelayedCout("Please write down any special properties and/or a description of the ammo: ", false);
                getline(cin, description, '\n');
                // Adds it to gear
                _threads.emplace_back(thread(&character::AddGear, _character, make_unique<gear>(move(name + "(" + to_string(AmmoAmount) + ")"), move(description), move(weight))));
                return AmmoAmount;
            }
        }
        else
            return 0;
    }
    else if (tolower(usesAmmo[0]) != 'n')
    {
        DelayedCout("I'll ask again.");
        return GetAmmo();
    }
    return -1;
}

bool creator::WillBuyAmmo()
{
    DelayedCout("Would you like to purchase some ammo?");
    DelayedCout("Y/n: ", false);
    string willBuy;
    getline(cin, willBuy, '\n');
    if (tolower(willBuy[0]) == 'y')
    {
        return true;
    }
    else if (tolower(willBuy[0]) != 'n')
    {
        DelayedCout("IIt's a Yes or No question.");
        return WillBuyAmmo();
    }
    return false;
}

short creator::GetAmmoAmount()
{
    DelayedCout("How much of said ammo would you like to buy: ", false);
    string amount;
    getline(cin, amount, '\n');
    try
    {
        if (stoi(amount) > 0)
            return stoi(amount);
        else
        {
            DelayedCout("I need a number bigger than 0.");
            return GetAmmoAmount();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("The... Umm... Amount...?");
        return GetAmmoAmount();
    }
}

unsigned short creator::GetACBonus()
{
    DelayedCout("What is the armor bonus: ", false);
    string bonus;
    getline(cin, bonus, '\n');
    try
    {
        if (stoi(bonus) > 0)
            return stoi(bonus);
        else
        {
            DelayedCout("Your armor most have a bonus of at least 1.");
            return GetACBonus();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the bonus as a number.");
        return GetACBonus();
    }
}

unsigned short creator::GetMaxDex()
{
    DelayedCout("What is the armors max dex bonus: ", false);
    string bonus;
    getline(cin, bonus, '\n');
    try
    {
        if (stoi(bonus) >= 0)
            return stoi(bonus);
        else
        {
            DelayedCout("Your armors max dex penalty can't be less than 0.");
            return GetMaxDex();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the bonus as a number.");
        return GetMaxDex();
    }
}

short creator::GetCheckPenalty()
{
    DelayedCout("What is the armors check penalty: ", false);
    string penalty;
    getline(cin, penalty, '\n');
    try
    {
        return stoi(penalty);
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the penalty as a number.");
        return GetCheckPenalty();
    }
}

unsigned short creator::GetSpellFailureChance()
{
    DelayedCout("What is the armors spell failure chance: ", false);
    string chance;
    getline(cin, chance, '\n');
    try
    {
        if (stoi(chance) >= 0)
            return stoi(chance);
        else
        {
            DelayedCout("Your armors spell failure chance can't be less than 0.");
            return GetSpellFailureChance();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the chance as a number.");
        return GetSpellFailureChance();
    }
}

unsigned short creator::GetBaseSpeedAdjustment()
{
    DelayedCout("What is the armors base speed adjustment: ", false);
    string speed;
    getline(cin, speed, '\n');
    try
    {
        if (stoi(speed) >= 0)
            return stoi(speed);
        else
        {
            DelayedCout("Your armors base speed adjustment can't be less than 0.");
            return GetBaseSpeedAdjustment();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please give me the adjustment as a number.");
        return GetBaseSpeedAdjustment();
    }
}

alignment creator::GetAlignment()
{
    DelayedCout("Please select the number correspending to your characters alignment.");
    DelayedCout("1. Lawful Good\n2. Neutral Good\n3. Chaotic Good\n4. Lawful Neutral\n5. True Neutral\n6. Chaotic Neutral\n7. Lawful Evil\n8. Neutral Evil\n9. Chaotic Evil");
    DelayedCout("#: ", false);
    string alignment;
    getline(cin, alignment, '\n');
    try
    {
        switch (stoi(alignment))
        {
        case 1:
            return LG;
        case 2:
            return NG;
        case 3:
            return CG;
        case 4:
            return LN;
        case 5:
            return TN;
        case 6:
            return CN;
        case 7:
            return LE;
        case 8:
            return NE;
        case 9:
            return CE;
        default:
            DelayedCout("That wasn't an option.");
            return GetAlignment();
        }
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("Please enter a number.");
        return GetAlignment();
    }
}

short creator::GetAge()
{
    DelayedCout("To determine the age of your character you can either look at the chart in the Additional Rules chapter of the Pathfinder 1e Core Rulebook for how fast your race ages.");
    DelayedCout("Or you can role the dice stated there and multiply it by the given number to get a random age base on your race and class.");
    DelayedCout("Age: ", false);
    string age;
    getline(cin, age, '\n');
    try
    {
        return stoi(age);
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetAge();
    }
}

short creator::GetHeight()
{
    DelayedCout("To determine the height of your character you can either look at the chart in the Additional Rules chapter of the Pathfinder 1e Core Rulebook for how tall your race is on average.");
    DelayedCout("Or you can role the dice stated there and add it to the given number to get a random height based on your race.");
    DelayedCout("Height: ", false);
    string height;
    getline(cin, height, '\n');
    try
    {
        return stoi(height);
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetHeight();
    }
}

short creator::GetCharacterWeight()
{
    DelayedCout("To determine the weight of your character you can either look at the chart in the Additional Rules chapter of the Pathfinder 1e Core Rulebook for how heavy your race is on average.");
    DelayedCout("Or if you rolled dice for your height you can multiply its result by the given number and add it to the other given number to determine a random weight based of your race and height.");
    DelayedCout("Weight: ", false);
    string weight;
    getline(cin, weight, '\n');
    try
    {
        return stoi(weight);
    }
    catch (const std::invalid_argument &e)
    {
        DelayedCout("I need a number.");
        return GetCharacterWeight();
    }
}

void creator::DelayedCout(string &&string)
{
    for (auto &&c : string)
    {
        this_thread::sleep_for(chrono::milliseconds(0));
        cout << c;
        cout.flush();
    }
    cout << endl;
}

void creator::DelayedCout(string &&string, bool doNewLine)
{
    if (doNewLine)
    {
        for (auto &&c : string)
        {
            this_thread::sleep_for(chrono::milliseconds(0));
            cout << c;
            cout.flush();
        }
        cout << endl;
    }
    else
    {
        for (auto &&c : string)
        {
            this_thread::sleep_for(chrono::milliseconds(0));
            cout << c;
            cout.flush();
        }
    }
}
