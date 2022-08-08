#ifndef GEAR_H
#define GEAR_H

#include <string>

using namespace std;

class gear
{
public:
    // Creates a gear item with dummy values
    gear();
    // Creates a gear item with the provided values
    gear(string name, string description, unsigned short weight);

    // Getters
    // Returns the name of the piece of gear
    string Name();
    // Returns the description of the piece of gear
    string Description();
    // Returns the gears' weight
    unsigned short Weight();

private:
    string _name;
    string _description;
    unsigned short _weight;
};

#endif