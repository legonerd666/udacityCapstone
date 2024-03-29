#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include "enums.h"

using namespace std;

/**
 * @brief Stores one \ref currencyType "type of currency" for a \ref Character "charater".
 *
 * Stores the \ref currencyType "type" and amount of a currency for a \ref Character "character". \n
 */
class Currency
{
public:
    // Creates a Currency object with dummy values
    Currency();
    // Creates a Currency object with the given values
    Currency(currencyType type, int amount);

    // Getters
    // Returns the type of currency this is
    currencyType Type();
    // Returns the amount of Currency is stored here
    int Amount();

    // Setters
    // Sets the amount of the Currency is stored here to the new value
    void Amount(int newAmount);

private:
    currencyType _type;
    int _amount;
};

#endif