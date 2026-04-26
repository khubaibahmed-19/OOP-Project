#include"pixel.h"
Pixel::Pixel(){
    r=0;g=0;b=0;
}
Pixel::Pixel(int r,int g ,int b ){
    this->r=r;
    this->g=g;
    this->b=b;
}
Pixel::~Pixel(){}
int Pixel::getRed(){
    return r;
}
int Pixel::getBlue(){
    return b;
}
int Pixel::getGreen(){
    return g;
}
void Pixel::setBlue(int b){
    this->b=b;
}
void Pixel::setGreen(int g){this->g=g;}
void Pixel::setRed(int r){this->r=r;}
int Pixel::getBrightness() const {return (r+g+b)/3;}
char Pixel::getASCII ()const {
    int brightness=this->getBrightness();
    if (brightness < 64) {
        return ' ';
    } 
    else if (brightness < 128) {
        return ':';
    } 
    else if (brightness < 192) {
        return '+';
    } 
    else {
        return '#'; 
    }
}
int Pixel::clamp(int value){
    if(value>255){
        value=255;
    }if(value<0){
        value=0;
    }
    return value;
}
Pixel Pixel:: operator+(const Pixel& p) const{
    int newR=this->r+p.r;
    int newG=this->g+p.g;
    int newB=this->b+p.b;
    newR = clamp(newR);
    newG = clamp(newG);
    newB = clamp(newB);
    return Pixel(newR, newG, newB);
}

ostream& operator<<(ostream& os, const Pixel& p){
    os<<p.getASCII();
    return os;
}


