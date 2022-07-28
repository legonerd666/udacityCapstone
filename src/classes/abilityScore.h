#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

#include "../enums.h"

class abilityScore
{
public:
    abilityScore();
    abilityScore(short score);

    // Getters
    short Score();
    short AdjustedScore();
    short Modifier();
    short AdjustedModifier();

    // Setters
    //  void Type(abilityType newType);
    //  void Score(short newScore);
    //  void AdjustedScore(short newAdjustedScore);

private:
    short _score;
    short _adjustedScore;
};

#endif