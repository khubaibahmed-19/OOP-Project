#pragma once
#include "filter.h"
class greenChannel : public filter {
public:
    greenChannel();
    image* apply(image* img) override;
    ~greenChannel();
};
