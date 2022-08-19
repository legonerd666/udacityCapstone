#ifndef CREATORAPPLICATION_H
#define CREATORAPPLICATION_H

#include <Wt/WApplication.h>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>

#include "../Character.h"

using namespace std;
using namespace Wt;

class CreatorApplication : public WApplication
{
private:
    // Member Variables
    /**
     * @brief Stores a pointer to the character object we are gonna change.
     *
     */
    shared_ptr<Character> _character;

    WText *_promptText;
    WLineEdit *_inputField;

    // Member Functions
    /**
     * @brief Checks if the value of the string in \ref CreatorApplication::_inputField "_inputField" is valid.
     *
     * Checks if the value of inputField is within the min and max values allowed by the raw type and is also a number.
     * @tparam T The type of number we want to validate.
     * @param min The lowest value T can hold
     * @param max The maximum value T can hold
     * @return bool on if it is a valid number
     */
    template <typename T>
    bool IsValidNumber(T min, T max);

    /**
     * @brief Starts the character creation process
     *
     */
    void CreateCharacter();
    /**
     * @brief Gives the user an intro and then runs the ability scores section
     *
     */
    void Intro();
    /**
     * @brief Sets the Ability Scores of the Character object
     *
     */
    void SetAbilityScores();
    /**
     * @brief Sets all the stats of the Character object dictated by their Race
     *
     */
    void SetRace();
    /**
     * @brief Set the Role and all related stats of the Character object
     *
     */
    void SetRole();
    /**
     * @brief Set the Feats of the Character
     *
     */
    void SetFeats();
    /**
     * @brief Set the Equipment of the Character.
     *
     */
    void SetEquipment();
    /**
     * @brief Set the Characteristics of the Character
     *
     */
    void SetCharacteristics();
    void SetAge();
    void SetHeight();
    void SetWeight();

public:
    /**
     * @brief Construct a new Creator Application object with a shared pointer to the character.
     *
     * Creates a new Creator Application object with a shared pointer to the character we will edit
     * in the webapp
     *
     * @param env
     */
    CreatorApplication(const WEnvironment &env, shared_ptr<Character> character);
};
#endif