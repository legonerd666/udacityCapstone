## Dependencies:

    -Wt: https://redmine.webtoolkit.eu/projects/wt/wiki/Wt_Installation
    -Cmake: 3.7
    -Boost Library (for wt)

## How to build and run this program on linux:

    1. Clone Repo
    2. Install Dependencies
    3. Open terminal in the cloned directory
    4. mkdir build
    5. cd build
    6. cmake ..
    7. make
    8. ./CharacterCreator --docroot . --http-address 0.0.0.0 --http-port 9090
    9. Enjoy! :]

## What this program does:

    This program uses a class "creator" to fill in the fields of a large class "character" to create a character sheet for the RPG Pathfinder 1e.
    It asks the user of the program for info using the console and takes the data inputed by the user and stores it in the character class and once all the field have been filled the program starts a local webpage of to display the character.
    The text is displayed in a way that makes it much more readable by adding a delay to the text display.
    The program text is also designed to not be robotic in its phrasing and has its own personality!

## File Structure:

    All the relevant code is in the src and include directories
    src/:
        classes/
            gui/
                CharacterApplication.cpp
            AbilityScore.cpp
            ArmorClass.cpp
            ArmorClassItem.cpp
            Character.cpp
            ClassSpellListItem.cpp
            Creator.cpp
            Currency.cpp
            Feat.cpp
            Gear.cpp
            HitDie.cpp
            HitPoints.cpp
            Initiative.cpp
            Race.cpp
            Role.cpp
            Save.cpp
            Skill.cpp
            Speed.cpp
            Spell.cpp
            SpellStat.cpp
            Weapon.cpp
        enums.cpp
        main.cpp

    include/:
        classes/
            gui/
                CharacterApplication.h
            AbilityScore.h
            ArmorClass.h
            SrmorClassItem.h
            Character.h
            ClassSpellListItem.h
            Creator.h
            Currency.h
            Feat.h
            Gear.h
            HitDie.h
            HitPoints.h
            Initiative.h
            Race.h
            Role.h
            Save.h
            Skill.h
            Speed.h
            Spell.h
            SpellStat.h
            Weapon.h
        enums.h

## Class Structure:

    Creator:
        vector<threads> _threads
    Character:
        string _name
        alignment _alignment
            enum
        string _player
        vector<unique_ptr<Role>> _roles
            Role:
                string _name
                unsigned short _level
                vector<shared_ptr<Feat>> _classFeatures
                    Feat:
                        string _name
                        string _description
                shared_ptr<SpellStat> _spellStats[10]
                    SpellStat:
                        unsigned short _spellLevel
                        short _spellsKnown
                        abilityType _abilityType
                            enum
                        short _spellsPerDay
                        short _bonusSpells
                vector<shared_ptr<Spell>> _spells
                    Spell:
                        string _name
                        magicSchool _school
                            enum
                        vector<shared_ptr<ClassSpellListItem>> _roles
                            ClassSpellListItem:
                                casterType _casterType
                                    enum
                                unsigned short _level
                        string _castingTime
                        string _components
                        string _range
                        string _target
                        string _duration
                        string _savingThrow
                        bool _spellResistance
                        string _description
                bool _isCastingClass
        string _deity
        string _homeland
        unique_ptr<Race> _race
            Race:
                string _name
                vector<shared_ptr<Feat>> _racialTraits
                    Feat:
                        string _name
                        string _description
        sizeType _size
            enum
        string _gender
        short _age
        short _height
        short _weight
        string _hairColor
        string _eyeColor

        unique_ptr<HitPoints> _hitpoints
            Hitpoints:
                short _totalHP
                short _currentDamage
                short _nonLethalDamage
                vector<unique_ptr<HitDie>> _hitdice
                    HitDie:
                        die _hitDie
                            enum
                        short _numberOfHitDice
        unique_ptr<AbilityScore> _abilityScores[6]
            AbilityScore:
                short _score
                short _adjustedScore
        unique_ptr<Speed> _speed
            Speed:
                unsigned short _base
                unsigned short _baseTempMod
                unsigned short _armored
                unsigned short _armoredTempMod
                unsigned short _fly
                unsigned short _flyTempMod
                unsigned short _swim
                unsigned short _swimTempMod
                unsigned short _climb
                unsigned short _climbTempMod
                unsigned short _burrow
                unsigned short _burrowTempMod
        unique_ptr<Initiative> _initiative
            Initiative:
                short _miscMod
        unique_ptr<ArmorClass> _armorClass
            ArmorClass:
                short _armor
                short _shield
                short _naturalArmor
                short _deflectionBonus
                short _dodgeBonus
                short _miscMod
        unique_ptr<Save> _saves[3]
            Save:
                saveType _type
                    enum
                abilityType _abilityType
                    enum
                unsigned short _base
                short _magicMod
                short _miscMod
                short _tempMod
        vector<unique_ptr<Skill>> _skills
            Skill:
                skillType _skillType
                    enum
                abilityType _abilityType
                    enum
                short _ranks
                short _miscMod
                bool _isClassSkill
                bool _isTrainedOnly
        string _languages

        vector<unsigned short> _baseAttackBonuses
        short _spellResistance
        vector<unique_ptr<Weapon>> _weapons
            Weapon:
                string _name
                string _criticalRange
                string _damageType
                string _range
                short _ammo
                die _damageDie
                    enum
                short _numberOfDamageDice
                abilityType _abiliyType
                    enum
        string _proficiencies

        vector<unique_ptr<ArmorClassItem>> _armorClassItems
            ArmorClassItem:
                string _name
                string _type
                unsigned short _bonus
                unsigned short _maxDexBonus
                short _checkPenalty
                unsigned short _spellFailureChance
                unsigned short _baseSpeedAdjustment
                unsigned short _weight
                string _properties
        vector<unique_ptr<Gear>> _gear
            Gear:
                string _name
                string _description
                unsigned short _weight
        unique_ptr<Currency> _currency[4]
            Currency:
                currencyType _type
                    enum
                int _amount

        vector<unique_ptr<Feat>> _feats
            Feat:
                string _name
                string _description

        unsigned int _xp
        unsigned int _nextLevelXpAmount

        mutex _mutex

## In-depth Documentation:

    To view the in-depth docs for this program follow these steps:
        1. Clone the repo
        2. Install Doxygen and its dependencies (Flex and Bison)
        3. In the terminal run "doxygen doxygenConfig"
        4. Open the html folder generated by doxygen
        5. Open index.html in your browser

## Rubric Items:

    The project requires I include at least 5 rubric items in my code. My code implements all rubrics items except 5. Enjoy.

#### Loops, Functions, I/O:

        1. For lots of examples: Creator.cpp and character.cpp eg. (Creator.cpp ln 47, 65, 156, 191, 198, 212, 258)
        2. N/A
        3. Lots in Creator.cpp eg. (Creator.cpp ln 72, 129, 141, 161, 175, 219)

#### OOP:

        1. All files in src/classes are classes
        2. All files in src/classes are classes and are sorted accordingly eg. (Character.h ln 30, 108. Gear.h 10, 24)
        3. Almost any class file eg. (Feat.cpp ln 9. Gear.cpp ln 10)
        4. Check any header file eg. (Creator.h ln 14-150)
        5. All class files eg. (Character.cpp ln 1466)
        6. Open almost any file (Character.h ln 112, 115, 124-129)
        7. Lots of examples in enums.h/enums.cpp eg. (enums.h ln 152, 155, 158, 161, 164, 167)
        8. N/A
        9. N/A

#### Memory Management:

        1. If r-value references and pointers count, Character.h and Creator.h have tons of examples. If not HitPoints.h line 27 has 1, and Creator.h has 1 on line 19 and 1 on line 21
        2. Creator.h has a destructor that joins threads eg. (Creator.cpp ln 16)
        3. Creator.h and Character.cpp ToStringForConsole() eg. (Character.cpp ln 858)
        4. Creator.h eg. (Creator.h ln 19-27)
        5. Creator.h/Creator.cpp and Character.h/Character.cpp eg. (Creator.cpp ln 404, 1213, 1275)
        6. Just open any of my code, dude. They are everywhere eg. (Character.h ln 124-129)

#### Concurrency:

        1. Creator.cpp eg. (Creator.cpp ln 73, 106, 113, 150, 162, 166)
        2. N/A
        3. Character.cpp/Character.h (Character.cpp ln 64, 1349, 1355, 1361, 1367, 1374)
        4. N/A
