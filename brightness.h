#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class brightness:public filter{
    int brighntess;
    public:
    brightness(int ID, string name, bool isEnabled);
    image * apply(image*img)override;
    ~brightness();
};