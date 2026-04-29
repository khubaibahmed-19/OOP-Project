#pragma once
#include "filter.h"
class boxBlur : public filter {
public:
    boxBlur(int ID, string name, bool isEnabled);
    image* apply(image* img) override;
    ~boxBlur();
};
