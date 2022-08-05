#ifndef INITIATIVE_H
#define INITIATIVE_H

class initiative
{
public:
    // Creates an initiative object with its values set to 0
    initiative();

    // Getters
    //  Returns the total initiative bonus based off the characters dexterity modifier
    short Total(short dexMod);
    // Returns the miscellaneous modifier to initiative
    short MiscMod();

private:
    short _miscMod;
};

#endif