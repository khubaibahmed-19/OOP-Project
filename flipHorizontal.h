#pragma once
#include "filter.h"
class flipHorizontal : public filter {
public:
    flipHorizontal();
    image* apply(image* img) override;
    ~flipHorizontal();
};
