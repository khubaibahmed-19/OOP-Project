#pragma once
#include <iostream>
using namespace std;
class Pixel{
    private:
    int r;
    int g;
    int b;
    public:
    Pixel();
    Pixel(int r,int g, int b);
    ~Pixel();
    int getRed();
    int getGreen();
    int  getBlue();
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    int getBrightness() const;
    char getASCII() const;
    static int clamp(int value);
    friend ostream& operator<<(ostream& os, const Pixel& p); 
    Pixel operator+(const Pixel& p) const;

};