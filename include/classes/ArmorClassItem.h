#ifndef ARMORCLASSITEM_H
#define ARMORCLASSITEM_H

#include <string>

using namespace std;

/**
 * @brief Stores the data for an item that when worn or wielded changes the \ref Character "characters'" \ref ArmorClass "armor class".
 *
 * Stores all the relevent data for an item that affects the \ref Character "characters'" \ref ArmorClass "armor class". \n
 */
class ArmorClassItem
{
public:
    // Creates an item with the stats of a piece of armor and gives it dummy values
    ArmorClassItem();
    // Creates an item with the stats of a piece of armor and sets each value to the given values
    ArmorClassItem(string name, string type, unsigned short bonus, unsigned short maxDexBonus, short checkPenalty, unsigned short spellFailureChance, unsigned short baseSpeedAdjustment, unsigned short weight, string properties);

    // Getters
    // Returns the name of the item
    string Name();
    // Returns the type of the item
    string Type();
    // Returns the armor bonus of the item
    unsigned short Bonus();
    // Returns the maximum dex bonus allowed while the item is worn
    unsigned short MaxDexBonus();
    // Returns the penalty to strength and dexterity based checks when wearing this item
    short CheckPenalty();
    // Returns the spell failure chance inflicted by wearing this item
    unsigned short SpellFailureChance();
    // Returns the maximum Base Movement speed allowed when wearing this item
    unsigned short BaseSpeedAdjustment();
    // Returns the weight of this item in pounds
    unsigned short Weight();
    // Returns the properties of this item
    string Properties();

private:
    string _name;
    string _type;
    unsigned short _bonus;
    unsigned short _maxDexBonus;
    short _checkPenalty;
    unsigned short _spellFailureChance;
    unsigned short _baseSpeedAdjustment;
    unsigned short _weight;
    string _properties;
};

#endif