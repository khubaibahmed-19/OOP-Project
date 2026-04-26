#include "greenChannel.h"
greenChannel::greenChannel() {}
greenChannel::~greenChannel() {}
image* greenChannel::apply(image* img) {
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Pixel& p = img->at(i, j);
            p.setRed(0);
            p.setBlue(0);
        }
    }
    return img;
}
