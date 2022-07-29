#ifndef INTRO_H
#define INTRO_H

#include "classes/character.h"
#include "enums.h"

#include <memory>
#include <vector>
#include <thread>

class creator
{
public:
    creator();
    ~creator();

    void Intro(shared_ptr<character> &&character);

    void DelayedCout(string &&string);
    void DelayedCout(string &&string, bool doNewLine);

private:
    void AbilityScores(shared_ptr<character> &&character);
    void Race(shared_ptr<character> &&character, short abilityScores[6]);

    short GetScore(abilityType abilityType);
    short GetScoreAdj(abilityType abilityType);
    sizeType GetSize();
    short GetSpeed();
    void RacialTraits(shared_ptr<character> character);
    void ExtraLanguages(shared_ptr<character> character, string languages);

    vector<thread> _threads;
};

#endif