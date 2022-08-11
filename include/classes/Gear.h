#ifndef GEAR_H
#define GEAR_H

#include <string>

using namespace std;

/**
 * @brief Stores the info of a piece of \ref Gear "gear"
 *
 * Stores all relevant info for an \ref Gear "item" or \ref Gear "piece of gear". \n
 */
class Gear
{
public:
    // Creates a Gear item with dummy values
    Gear();
    // Creates a Gear item with the provided values
    Gear(string name, string description, unsigned short weight);

    // Getters
    // Returns the name of the piece of Gear
    string Name();
    // Returns the description of the piece of Gear
    string Description();
    // Returns the gears' weight
    unsigned short Weight();

private:
    string _name;
    string _description;
    unsigned short _weight;
};

#endif