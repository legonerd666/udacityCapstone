#include "abilityScore.h"
#include "../enums.h"

abilityScore::abilityScore() {
    _score = 10;
    _adjustedScore = 10;
}

abilityScore::abilityScore(short score): _score(score), _adjustedScore(score) {}

const short abilityScore::Score() {
    return _score;
}

const short abilityScore::AdjustedScore() {
    return _adjustedScore;
}

const short abilityScore::Modifier() {
    return (_score / 2) - 5;
}

const short abilityScore::AdjustedModifier() {
    return (_adjustedScore / 2) - 5;
}
