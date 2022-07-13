#ifndef ARMORCLASSITEM_H
#define ARMORCLASSITEM_H

#include <string>

using namespace std;

class armorClassItem {
public:
    armorClassItem();

    //Getters
    string ToString();

private:

    string _armorClassItem;
    short _bonus;
    unsigned short _maxDexBonus;
    short _checkPenalty;
    short _spellFailureChance;
    short _baseSpeedAdjustment [2];
    unsigned short _weight;
    string _properties;
};


#endif