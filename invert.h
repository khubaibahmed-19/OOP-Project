#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class invert:public filter{
    public:
    invert(int ID, string name, bool isEnabled);
    image * apply(image* img)override;
    ~invert();
};