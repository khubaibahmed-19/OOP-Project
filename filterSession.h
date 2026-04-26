#pragma once
#include<vector>
#include<string>
#include"image.h"
#include"filter.h"
using namespace std;
class filterSession{
     vector<filter*> pipeline ;
     image* picture;
     string CustomerID;
     string timeStamp;
     public:
     filterSession(string customerID);
     ~filterSession();
     void applyAll();
     void previewASCII();
     filterSession& addfilter(filter* f);
   
};