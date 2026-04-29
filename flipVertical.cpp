#include "flipVertical.h"
flipVertical::flipVertical(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {}
flipVertical::~flipVertical() {}
image* flipVertical::apply(image* img) {
    int w = img->getWidth();
    int h = img->getHeight();
    for (int i = 0; i < h / 2; i++) {
        for (int j = 0; j < w; j++) {
            Pixel& top = img->at(i, j);
            Pixel& bottom = img->at(h - 1 - i, j);
            int tempR = top.getRed();
            int tempG = top.getGreen();
            int tempB = top.getBlue();
            top.setRed(bottom.getRed());
            top.setGreen(bottom.getGreen());
            top.setBlue(bottom.getBlue());
            bottom.setRed(tempR);
            bottom.setGreen(tempG);
            bottom.setBlue(tempB);
        }
    }
    return img;
}
