#ifndef SPECIALABILITY_H
#define SPECIALABILITY_H

#include <string>

using namespace std;

class specialAbility
{
public:
    specialAbility();

    //Getters
    string ToString();

    //Setters
    void Name(string newName);
    void Description(string newDescription);

private:

    string _name;
    string _description;

};


#endif