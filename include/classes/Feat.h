#ifndef FEAT_H
#define FEAT_H

#include <string>

using namespace std;

/**
 * @brief Stores a \ref Character "characters" \ref Character::_feats "feats", \ref Race::_racialTraits "traits", and \ref Role::_classFeatures "features".
 *
 * Stores the \ref Name() "name" and \ref Description() "description" of a \ref Feat "feat", \ref Race::_racialTraits "trait", or \ref Role::_classFeatures "feature".
 */
class Feat
{
public:
    // Creates a Feat with dummy values
    Feat();
    // Creates a Feat with the given values
    Feat(string name, string description);

    // Getters
    // Returns the name of the Feat
    string Name();
    // Return the feats' description
    string Description();

private:
    string _name;
    string _description;
};

#endif