#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class stretch:public filter{
    public:
    image* apply(image*img);
    ~stretch();
};