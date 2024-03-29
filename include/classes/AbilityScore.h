#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

#include "enums.h"

/**
 * @brief Stores an \ref AbilityScore "ability score" for a Character
 *
 * Stores an \ref AbilityScore "ability score" for a Character with all the required info of an \ref AbilityScore "ability score" in Pathfinder 1e. \n
 */
class AbilityScore
{
public:
    // Creates an ability score and sets the base and temporary score to 10.
    AbilityScore();

    // Creates an ability score and sets both the score and adjusted score to the same value
    AbilityScore(short score);

    // Getters
    // Returns the base score of the ability score
    short Score();
    // Returns the temporary score of the ability
    short AdjustedScore();
    // Calculates and returns the modifier based on the base score
    short Modifier();
    // Calculates and returns the modifier based on the temporary score
    short AdjustedModifier();

private:
    short _score;
    short _adjustedScore;
};

#endif