#pragma once
#include "filter.h"
class greenChannel : public filter {
public:
    greenChannel(int ID, string name, bool isEnabled);
    image* apply(image* img) override;
    ~greenChannel();
};
