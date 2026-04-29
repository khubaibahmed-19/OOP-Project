#include "grayscale.h"
grayscale::grayscale(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {}
image* grayscale::apply(image* img) {
    int red = 0;
    int blue = 0;
    int green = 0;
    int newval = 0;
    for(int i = 0; i < img->getHeight(); i++){
        for(int j = 0; j < img->getWidth(); j++){
            Pixel& currentpixel = img->at(i,j);
            red = currentpixel.getRed();
            green = currentpixel.getGreen();
            blue = currentpixel.getBlue();
            newval = (red + blue + green) / 3;
            currentpixel.setRed(newval);
            currentpixel.setGreen(newval);
            currentpixel.setBlue(newval);
        }
    }
    return img;
}