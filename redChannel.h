#pragma once
#include "filter.h"
class redChannel : public filter {
public:
    redChannel();
    image* apply(image* img) override;
    ~redChannel();
};
