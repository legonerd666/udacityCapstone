#include "enums.h"

#include <string>

string EnumToString(alignment alignment){
    switch (alignment)
    {
    case LG:
        return "LG";
    case NG:
        return "NG";
    case CG:
        return "CG";
    case LN:
        return "LN";
    case TN:
        return "TN";
    case CN:
        return "CN";
    case LE:
        return "LE";
    case NE:
        return "NE";
    case CE:
        return "CE";
    default:
        return "Error: Invalid Alignment Enum";
    }
}

string EnumToString(die die) {
    switch (die)
    {
    case d4:
        return "d4";
    case d6:
        return "d6";
    case d8:
        return "d8";
    case d10:
        return "d10";
    case d12:
        return "d12";
    case d20:
        return "d20";
    default:
        return "Error: Invalid Die Enum";
    }
}