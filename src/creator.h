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
    void AbilityScores(shared_ptr<character> &&character);
    short GetScore(abilityType abilityType);

    void DelayedCout(string &&string);
    void DelayedCout(string &&string, bool doNewLine);

private:
    vector<thread> _threads;
};

#endif