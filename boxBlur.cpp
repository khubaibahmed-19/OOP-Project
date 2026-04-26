#include "boxBlur.h"
boxBlur::boxBlur() {}
boxBlur::~boxBlur() {}
image* boxBlur::apply(image* img) {
    image* copy = new image(*img);
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            int totalR = 0, totalG = 0, totalB = 0;
            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni < 0 || ni >= img->getHeight()) continue;
                    if (nj < 0 || nj >= img->getWidth()) continue;
                    totalR += copy->at(ni, nj).getRed();
                    totalG += copy->at(ni, nj).getGreen();
                    totalB += copy->at(ni, nj).getBlue();
                    count++;
                }
            }
            img->at(i, j).setRed(totalR / count);
            img->at(i, j).setGreen(totalG / count);
            img->at(i, j).setBlue(totalB / count);
        }
    }
    delete copy;
    return img;
}
