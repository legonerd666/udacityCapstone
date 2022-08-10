#include "Currency.h"

#include "enums.h"

Currency::Currency()
{
    _type = gold;
    _amount = 0;
}

Currency::Currency(currencyType type, int amount) : _type(type), _amount(amount) {}

currencyType Currency::Type()
{
    return _type;
}

int Currency::Amount()
{
    return _amount;
}

void Currency::Amount(int newAmount)
{
    _amount = newAmount;
}