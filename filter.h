#pragma once
#include<string>
#include"image.h"
using namespace std;
class filter{
    string name;
    int ID;
    bool isEnabled;
    public:
    filter(int ID,string name,bool isEnabled);
    virtual ~filter();
    virtual image* apply(image* img) = 0;
    string getName();
    int getID()const;
    bool getStatus();
    void setEnabled(bool v);
};