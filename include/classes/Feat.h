#ifndef FEAT_H
#define FEAT_H

#include <string>

using namespace std;

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