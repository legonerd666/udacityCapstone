#ifndef GEAR_H
#define GEAR_H

#include <string>

using namespace std;

class gear
{
public:
    gear();

    //Getters
    short Weight();
    string ToString();

    //Setters
    void Name(string newName);
    void Weight(unsigned short newWeight);
    void Description(string newDescription);

private:
    string _name;
    unsigned short _weight;
    string _description;
};


#endif