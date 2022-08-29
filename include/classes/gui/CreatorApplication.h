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
     * Creates input fields for all six ability scores and adds them to the character object.
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
    /**
     * @brief Ensures the ability scores are set to proper values before entering them into the Character object
     *
     * Checks if each ability score is either blank (will be set to a random number from 3-18) or contains a number from 3-18
     * and if an ability score field is not valid it sets the warning text of that score to show and clears the field.
     * then it sets the focus to the first ability score field.
     * If/Once all the scores are valid, it sets the Character objects ability scores to the given values and calculates a random value for blank ones.
     * @param scores pointers to the input fields for each ability in the order of: str, dex, con, int, wis, cha.
     * @param warnings pointers to the hidden warning text above each field.
     */
    void CheckAbilityScores(vector<WLineEdit *> scores, vector<WText *> warnings, WPushButton *enterScoresBtn);
    /**
     * @brief Set the age of the character
     *
     */
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