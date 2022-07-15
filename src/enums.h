#ifndef ENUMS_H
#define ENUMS_H

#include <string>

using namespace std;

enum alignment {LG, NG, CG, LN, TN, CN, LE, NE, CE};

enum abilityType {strength, dexterity, constitution, intelligence, wisdom, charisma};

enum die {d4, d6, d8, d10, d12, d20};

enum saveType {fortitude, reflex, will};

enum skillType {acrobatics, appraise, bluff, climb, craft, diplomacy, disableDevice, disguise, escapeArtist, fly, handleAnimal, heal, intimidate, knowArcana, knowDungeoneering, knowEngineering, knowGeography, knowHistory, knowLocal, knowNature, knowNobility, knowPlanes, knowReligion, linguistics, perception, perform, profession, ride, senseMotive, sleightOfHand, spellcraft, stealth, survival, swim, useMagicDevice};

enum damageType {piercing, slashing, bludgeoning};

enum currencyType {copper, silver, gold, platinum};

enum magicSchool {abjuration, conjuration, divination, enchantment, evocation, illusion, necromancy, transmutation, universal};

enum casterType {bard, cleric, druid, paladin, sorcererWizard};

#endif