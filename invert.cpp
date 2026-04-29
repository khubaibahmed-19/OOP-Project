#include"invert.h"
invert::invert(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {}
image* invert::apply(image*img){
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
            newval=255-red;
            currentpixel.setRed(newval);
            newval=255-green;
            currentpixel.setGreen(newval);
            newval=255-blue;
            currentpixel.setBlue(newval);
        }
    }
    return img;
    
}