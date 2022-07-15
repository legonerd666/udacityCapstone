#include "abilityScore.h"
#include "../enums.h"

abilityScore::abilityScore() {
    _type = strength;
    _score = 0;
    _adjustedScore = 0;
}

short abilityScore::AdjustedScore() {
    return _adjustedScore;
}