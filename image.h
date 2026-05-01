#pragma once
#include<string>
#include"pixel.h"
using namespace std;
class filterSession;
class image{
    friend class filterSession;
    Pixel**images;
    int width;
    int height;
    public:
    image(int w,int h);
    image(const image& img );
    ~image();
    Pixel& at(int row,int col);
    int getWidth();
    int getHeight();
    bool loadfromFile(string path);
    bool save(string path);
    void displayASCII();
};