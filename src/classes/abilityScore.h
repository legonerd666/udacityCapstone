#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

enum abilityType {strength, dexterity, constitution, intelligence, wisdom, charisma};

class abilityScore {
public:
    abilityScore();
    
    //Getters
    abilityType Type();
    short Score();
    short AdjustedScore();
    short Modifier();
    short AdjustedModifier();

    //Setters
    void Type(abilityType newType);
    void Score(short newScore);
    void AdjustedScore(short newAdjustedScore);

private:
    abilityType _type;
    short _score;
    short _adjustedScore;
};


#endif