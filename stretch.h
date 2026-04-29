#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class stretch:public filter{
    public:
    stretch(int ID, string name, bool isEnabled);
    image* apply(image*img);
    ~stretch();
};