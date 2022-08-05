#ifndef MONEY_H
#define MONEY_H

#include <string>
#include "../enums.h"

using namespace std;

class currency
{
public:
    // Creates a currency object with dummy values
    currency();
    // Creates a currency object with the given values
    currency(currencyType type, int amount);

    // Getters
    // Returns the type of currency this is
    currencyType Type();
    // Returns the amount of currency is stored here
    int Amount();

    // Setters
    // Sets the amount of the currency is stored here to the new value
    void Amount(int newAmount);

private:
    currencyType _type;
    int _amount;
};

#endif