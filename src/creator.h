#ifndef INTRO_H
#define INTRO_H

#include "classes/character.h"
#include "enums.h"

#include <memory>

void Intro(unique_ptr<character> &&character);
void AbilityScores(unique_ptr<character> &&character);
short GetScore(abilityType abilityType);

void DelayedCout(string &&string);
void DelayedCout(string &&string, bool doNewLine);

#endif