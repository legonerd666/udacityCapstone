#include "AbilityScore.h"
#include "enums.h"

AbilityScore::AbilityScore()
{
    _score = 10;
    _adjustedScore = 10;
}

AbilityScore::AbilityScore(short score) : _score(score), _adjustedScore(score) {}

short AbilityScore::Score()
{
    return _score;
}

short AbilityScore::AdjustedScore()
{
    return _adjustedScore;
}

short AbilityScore::Modifier()
{
    return (_score / 2) - 5;
}

short AbilityScore::AdjustedModifier()
{
    return (_adjustedScore / 2) - 5;
}
