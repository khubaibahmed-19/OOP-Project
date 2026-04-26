#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class brightness:public filter{
    int brighntess;
    public:
    image * apply(image*img , int brightness);
    ~brightness();
};