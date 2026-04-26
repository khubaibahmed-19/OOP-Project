#include"filter.h"
#include"image.h"
class grayscale:public filter{
    public:
    void apply(image img);
    ~grayscale();
};