#pragma once
#include<string>
#include"pixel.h"
using namespace std;
class image{
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