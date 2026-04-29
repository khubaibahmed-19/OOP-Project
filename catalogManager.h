#pragma once
#include<vector>
#include<fstream>
#include"filter.h"
#include"grayscale.h"
#include"invert.h"
#include"brightness.h"
#include"stretch.h"
#include"redChannel.h"
#include"greenChannel.h"
#include"blueChannel.h"
#include"boxBlur.h"
#include"flipHorizontal.h"
#include"flipVertical.h"
using namespace std;
class catalogManager{
    public:
    vector<filter*> loadCatalog(string filepath);
    void saveCatalog(vector<filter*> filters, string filepath);
    void toggleFilter(vector<filter*>& filters, int id, bool v, string filepath);

    };

