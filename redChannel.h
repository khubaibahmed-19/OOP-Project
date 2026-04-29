#pragma once
#include "filter.h"
class redChannel : public filter {
public:
    redChannel(int ID, string name, bool isEnabled);
    image* apply(image* img) override;
    ~redChannel();
};
