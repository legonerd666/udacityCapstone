#ifndef RACE_H
#define RACE_H

#include <string>
#include <vector>
#include <memory>

#include "specialAbility.h"

using namespace std;

class race  {
public:
    race();
    
    //Getters
    //string ToString();

    //Setters
    //void Name(string newName);
    //void RacialAblities(vector<unique_ptr<specialAbility>>&& newRacialAbilities);
private:
    string _name;
    vector<unique_ptr<specialAbility>> _racialAbilities;
};


#endif