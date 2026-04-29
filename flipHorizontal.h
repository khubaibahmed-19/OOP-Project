#pragma once
#include "filter.h"
class flipHorizontal : public filter {
public:
    flipHorizontal(int ID, string name, bool isEnabled);
    image* apply(image* img) override;
    ~flipHorizontal();
};
