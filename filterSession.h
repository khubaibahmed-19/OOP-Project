#pragma once
#include <vector>
#include <string>
#include "image.h"
#include "filter.h"
using namespace std;
class image;
class filterSession {
    friend class image;
    vector<filter*> pipeline;
    image* picture;
    string customerID;
    string timestamp;
public:
     void setImage(image* img);
    filterSession(string customerID, string timestamp);
    ~filterSession();
    filterSession& addFilter(filter* f);
    void applyAll();
    void previewASCII();
    bool saveResult(string filepath);
    string getPipeline();
};