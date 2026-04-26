#pragma once
#include "filter.h"
class blueChannel : public filter {
public:
    blueChannel();
    image* apply(image* img) override;
    ~blueChannel();
};
