#include "redChannel.h"
redChannel::redChannel() {}
redChannel::~redChannel() {}
image* redChannel::apply(image* img) {
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Pixel& p = img->at(i, j);
            p.setGreen(0);
            p.setBlue(0);
        }
    }
    return img;
}
