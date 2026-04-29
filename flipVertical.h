#pragma once
#include "filter.h"
class flipVertical : public filter {
public:
    flipVertical(int ID, string name, bool isEnabled);
    image* apply(image* img) override;
    ~flipVertical();
};
