#pragma once
#include "filter.h"
class blueChannel : public filter {
public:
    blueChannel(int ID, string name, bool isEnabled);
    image* apply(image* img) override;
    ~blueChannel();
};
