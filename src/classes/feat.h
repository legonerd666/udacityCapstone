#ifndef FEAT_H
#define FEAT_H

#include <string>

using namespace std;

class feat
{
public:
    feat();
    feat(string name, string description);

    // Getters
    string Name();
    string Description();

private:
    string _name;
    string _description;
};

#endif