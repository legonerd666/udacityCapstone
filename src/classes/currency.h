#ifndef MONEY_H
#define MONEY_H

#include <string>
#include "../enums.h"

using namespace std;

class currency {
public:
    currency();

    //Getters
    // string ToString();

    //Setters
    // void Type(currencyType newType);
    // void Amount(int newAmount);

private:
    currencyType _type;
    int _amount;
};

#endif