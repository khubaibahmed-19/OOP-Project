#include "flipHorizontal.h"
flipHorizontal::flipHorizontal(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {}
flipHorizontal::~flipHorizontal() {}
image* flipHorizontal::apply(image* img) {
    int w = img->getWidth();
    int h = img->getHeight();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w / 2; j++) {
            Pixel& left = img->at(i, j);
            Pixel& right = img->at(i, w - 1 - j);
            int tempR = left.getRed();
            int tempG = left.getGreen();
            int tempB = left.getBlue();
            left.setRed(right.getRed());
            left.setGreen(right.getGreen());
            left.setBlue(right.getBlue());
            right.setRed(tempR);
            right.setGreen(tempG);
            right.setBlue(tempB);
        }
    }
    return img;
}
