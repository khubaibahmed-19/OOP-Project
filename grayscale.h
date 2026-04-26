#pragma once
#include"filter.h"
#include"image.h"
#include"pixel.h"
class grayscale:public filter{
    public:
    image* apply(image* img)override;
    ~grayscale();
};