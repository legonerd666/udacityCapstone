#include "currency.h"

#include "enums.h"

currency::currency()
{
    _type = gold;
    _amount = 0;
}

currency::currency(currencyType type, int amount) : _type(type), _amount(amount) {}

currencyType currency::Type()
{
    return _type;
}

int currency::Amount()
{
    return _amount;
}

void currency::Amount(int newAmount)
{
    _amount = newAmount;
}