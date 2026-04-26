#pragma once
#include "filter.h"
class boxBlur : public filter {
public:
    boxBlur();
    image* apply(image* img) override;
    ~boxBlur();
};
