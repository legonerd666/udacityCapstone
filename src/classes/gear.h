#ifndef GEAR_H
#define GEAR_H

#include <string>

using namespace std;

class gear
{
public:
    gear();
    gear(string name, string description, unsigned short weight);

    // Getters
    string Name();
    string Description();
    unsigned short Weight();

private:
    string _name;
    string _description;
    unsigned short _weight;
};

#endif