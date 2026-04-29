#include "blueChannel.h"
blueChannel::blueChannel(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {}
blueChannel::~blueChannel() {}
image* blueChannel::apply(image* img) {
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Pixel& p = img->at(i, j);
            p.setRed(0);
            p.setGreen(0);
        }
    }
    return img;
}
