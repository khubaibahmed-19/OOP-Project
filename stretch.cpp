#include"stretch.h"
stretch::stretch(int ID, string name, bool isEnabled) : filter(ID, name, isEnabled) {}
stretch::~stretch(){}
image* stretch::apply(image* img){
    int max=255;
    int min=0;
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Pixel& p = img->at(i, j);
            if (p.getRed() < min) min = p.getRed();
            if (p.getRed() > max) max = p.getRed();
            if (p.getGreen() < min) min = p.getGreen();
            if (p.getGreen() > max) max = p.getGreen();
            if (p.getBlue() < min) min = p.getBlue();
            if (p.getBlue() > max) max = p.getBlue();
        }
        
    }
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Pixel& p = img->at(i, j);

            float rNew =(p.getRed() - min) / (max - min)* 255; 
            float gNew = (p.getGreen()-min)/(max-min)*255;
            float bNew = (p.getBlue()-min)/(max-min)*255;
            rNew=p.clamp(rNew);
            gNew=p.clamp(gNew);
            bNew=p.clamp(bNew);
            p.setBlue(bNew);
            p.setGreen(gNew);
            p.setRed(rNew);
        }
    }
    return img;
}