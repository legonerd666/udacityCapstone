#ifndef ARMORCLASS_H
#define ARMORCLASS_H

class armorClass
{
public:
    armorClass();

    //Getters
    short ArmorClass(short dexMod, short sizeMod);
    short TouchArmorClass(short dexMod, short sizeMod);
    short FlatFootedArmorClass(short sizeMod);

    //Setters
    void Armor(short newArmor);
    void Shield(short newShield);
    void NaturalArmor(short newNaturalArmor);
    void DeflectionMod(short newDeflectionMod);
    void MiscMod(short NewMiscMod);


private:
    short _armor;
    short _shield;
    short _naturalArmor;
    short _deflectionMod;
    short _miscMod;

};

#endif