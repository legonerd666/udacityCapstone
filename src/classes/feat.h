#ifndef FEAT_H
#define FEAT_H

#include <string>

using namespace std;

class feat
{
public:
    feat();

    //Getters
    string ToString();

    //Setters
    void Prerequisites(string newPrerequisites);
    void Benefit(string Benefit);
    
private:
    string _prerequisites;
    string _benefit;
};


#endif