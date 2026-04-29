#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class grayscale:public filter{
    public:
    grayscale(int ID, string name, bool isEnabled);
    image* apply(image* img)override;
    ~grayscale();
};