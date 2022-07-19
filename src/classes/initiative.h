#ifndef INITIATIVE_H
#define INITIATIVE_H

class initiative {
public:
    initiative();

    //Getters
    short Total(short dexMod);
    short MiscMod();

private:
    short _miscMod;
};

#endif