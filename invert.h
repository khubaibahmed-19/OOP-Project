#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class invert:public filter{
    image * apply(image* img)override;
    ~invert();
};