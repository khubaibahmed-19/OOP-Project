#include"brightness.h"
brightness::brightness(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {
    this->brighntess = 0;
}
image* brightness::apply(image* img){
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
            newval=red+brighntess;
            newval=currentpixel.clamp(newval);
            currentpixel.setRed(newval);
            newval=green+brighntess;
            newval=currentpixel.clamp(newval);
            currentpixel.setGreen(newval);
            newval=blue+brighntess;
            newval=currentpixel.clamp(newval);
            currentpixel.setBlue(newval);
        }
    }
    return img;
}
void brightness::setBrightness(int val) { brighntess = val; }
brightness::~brightness(){

}