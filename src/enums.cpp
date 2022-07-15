#include "enums.h"

string AlignmentToString(alignment alignment) {
    switch (alignment) {
    case LG:
        return "Lawful Good";
    case NG: 
        return "Neutral Good";
    case CG: 
        return "Chaotic Good";
    case LN: 
        return "Lawful Neutral";
    case TN: 
        return "True Neutral";
    case CN: 
        return "Chaotic Neutral";
    case LE: 
        return "Lawful Evil";
    case NE: 
        return "Neutral Evil";
    case CE: 
        return "Chaotic Evil";
    default:
        return "Error: Invalid Alignment Enum";
    }
}