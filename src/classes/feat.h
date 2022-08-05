#ifndef FEAT_H
#define FEAT_H

#include <string>

using namespace std;

class feat
{
public:
    // Creates a feat with dummy values
    feat();
    // Creates a feat with the given values
    feat(string name, string description);

    // Getters
    // Returns the name of the feat
    string Name();
    // Return the feats' description
    string Description();

private:
    string _name;
    string _description;
};

#endif