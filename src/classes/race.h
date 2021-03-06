#ifndef RACE_H
#define RACE_H

#include <string>
#include <vector>

#include "specialAbility.h"

using namespace std;

class race  {
public:
    race();
    
    //Getters
    string ToString();

    //Setters
    void Name(string newName);
    void RacialAblities(vector<specialAbility> newRacialAbilities);
private:
    string _name;
    vector<specialAbility> _racialAbilities;
};


#endif