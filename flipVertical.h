#pragma once
#include "filter.h"
class flipVertical : public filter {
public:
    flipVertical();
    image* apply(image* img) override;
    ~flipVertical();
};
