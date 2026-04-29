#pragma once
#include<vector>
#include<fstream>
#include"filter.h"
using namespace std;
class catalogManager{
    public:
    vector<filter> loadCatalog(string filepath);
    void saveCatalog(filter filters);
    void toggleFilter(int id,bool v);
    
    };
