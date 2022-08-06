##How to build and run this program on linux:
1. Clone Repo
2. Open terminal in the cloned directory
3. mkdir build
4. cd build
5. cmake ..
6. make
8. ./CharacterCreator
9. Enjoy! :]

##What this program does:
This program uses a class "creator" to fill in the fields of a large class "character" to create a character sheet for the RPG Pathfinder 1e.
It asks the user of the program for info using the console and takes the data inputed by the user and stores it in the character class and once all the field have been filled the program prints the completed character sheet to the console as a large formatted string.

##File Structure:
All the relevant code is in the src directory
-src/:
 -classes/
 -creator.cpp
 -enums.cpp
 -main.cpp
 -creator.h
 -enums.h
-src/classes/:
 -abilityScore.cpp
 -armorClass.cpp
 -armorClassItem.cpp
 -character.cpp
 -classSpellListItem.cpp
 -currency.cpp
 -feat.cpp
 -gear.cpp
 -hitDie.cpp
 -hitPoints.cpp
 -initiative.cpp
 -race.cpp
 -role.cpp
 -save.cpp
 -skill.cpp
 -speed.cpp
 -spell.cpp
 -spellStat.cpp
 -weapon.cpp
 -abilityScore.h
 -armorClass.h
 -armorClassItem.h
 -character.h
 -classSpellListItem.h
 -currency.h
 -feat.h
 -gear.h
 -hitDie.h
 -hitPoints.h
 -initiative.h
 -race.h
 -role.h
 -save.h
 -skill.h
 -speed.h
 -spell.h
 -spellStat.h
 -weapon.h

##Class Structure:
    -creator:
     -vector<threads> _threads
    -character:
     -string _name
     -alignment _alignment
      -enum
     -string _player
     -vector<unique_ptr<role>> _roles
      -role:
       -string _name
       -unsigned short _level
       -vector<shared_ptr<feat>> _classFeatures
        -feat:
         -string _name
         -string _description
       -shared_ptr<spellStat> _spellStats[10]
        -spellStat:
         -unsigned short _spellLevel
         -short _spellsKnown
         -abilityType _abilityType
          -enum
         -short _spellsPerDay
         -short _bonusSpells
       -vector<shared_ptr<spell>> _spells
        -spell:
         -string _name
         -magicSchool _school
          -enum
         -vector<shared_ptr<classSpellListItem>> _roles
          -classSpellListItem:
           -casterType _casterType
            -enum
           -unsigned short _level
         -string _castingTime
         -string _components
         -string _range
         -string _target
         -string _duration
         -string _savingThrow
         -bool _spellResistance
         -string _description
       -bool _isCastingClass
     -string _deity
     -string _homeland
     -unique_ptr<race> _race
      -race:
       -string _name
       -vector<shared_ptr<feat>> _racialTraits
        -feat:
         -string _name
         -string _description
     -sizeType _size
      -enum
     -string _gender
     -short _age
     -short _height
     -short _weight
     -string _hairColor
     -string _eyeColor

     -unique_ptr<hitPoints> _hitpoints
      -hitpoints:
       -short _totalHP
       -short _currentDamage
       -short _nonLethalDamage
       -vector<unique_ptr<hitDie>> _hitdice
        -hitDie:
         -die _hitDie
          -enum
         -short _numberOfHitDice
     -unique_ptr<abilityScore> _abilityScores[6]
      -abilityScore:
       -short _score
       -short _adjustedScore
     -unique_ptr<speed> _speed
      -speed:
       -unsigned short _base
       -unsigned short _baseTempMod
       -unsigned short _armored
       -unsigned short _armoredTempMod
       -unsigned short _fly
       -unsigned short _flyTempMod
       -unsigned short _swim
       -unsigned short _swimTempMod
       -unsigned short _climb
                unsigned short _climbTempMod
                unsigned short _burrow
                unsigned short _burrowTempMod
        unique_ptr<initiative> _initiative
            initiative:
                short _miscMod
        unique_ptr<armorClass> _armorClass
            armorClass:
                short _armor
                short _shield
                short _naturalArmor
                short _deflectionBonus
                short _dodgeBonus
                short _miscMod
        unique_ptr<save> _saves[3]
            save:
                saveType _type
                    enum
                abilityType _abilityType
                    enum
                unsigned short _base
                short _magicMod
                short _miscMod
                short _tempMod
        vector<unique_ptr<skill>> _skills
            skill:
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
        vector<unique_ptr<weapon>> _weapons
            weapon:
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

        vector<unique_ptr<armorClassItem>> _armorClassItems
            armorClassItem:
                string _name
                string _type
                unsigned short _bonus
                unsigned short _maxDexBonus
                short _checkPenalty
                unsigned short _spellFailureChance
                unsigned short _baseSpeedAdjustment
                unsigned short _weight
                string _properties
        vector<unique_ptr<gear>> _gear
            gear:
                string _name
                string _description
                unsigned short _weight
        unique_ptr<currency> _currency[4]
            currency:
                currencyType _type
                    enum
                int _amount

        vector<unique_ptr<feat>> _feats
            feat:
                string _name
                string _description

        unsigned int _xp
        unsigned int _nextLevelXpAmount

        mutex _mutex

##Rubric Items:
    I'm not gonna spend the next month finding line numbers in files for each rubric item if it has it EVERYWHERE. If you'd like to check I will be giving some recommended files to look in for each though most rubric items that have been filled have been filled in tons of files so I won't be listing them all.
    ####Loops, Functions, I/O:
        1. For lots of examples: creator.cpp and character.cpp
        2. N/A
        3. Lots in creator.cpp
    ####OOP:
        1. Open any file except main
        2. Open any file except main
        3. Open any file except main and creator
        4. Open any file except main
        5. Open any file except main
        6. Open almost any file
        7. Lots of examples in enums.h/enums.cpp
        8. N/A
        9. N/A
    ####Memory Management:
        1. If r-value references and pointers count, character.h and creator.h have tons of examples. If not hitPoints.h line 27 has 1, and creator.h has 1 on line 19 and 1 on line 21
        2. creator.h has a destructor that joins threads
        3. creator.h and character.cpp ToStringForConsole()
        4. creator.h
        5. creator.h/creator.cpp and character.h/character.cpp
        6. Just open any of my code, dude. They are everywhere
    ####Concurrency:
        1. creator.cpp
        2. N/A
        3. character.cpp/character.h
        4. N/A
    The project requires I include at least 5 rubric items in my code. My code implements all rubrics items except 5. Enjoy.
