#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include"image.h"
image::image(int w,int h){
    width=w;
    height=h;
    images=new Pixel*[height];
    for(int i=0;i<height;i++){
        images[i]=new Pixel[width];
    }
}
image::image(const image&img) {
    this->width =img.width;
    this->height =img.height;
    this->images = new Pixel*[height];
    for (int r = 0; r < height; r++) {
        this->images[r] = new Pixel[width];
        for (int c = 0; c < width; c++) {
            this->images[r][c] =img.images[r][c];
        }
    }
}
image::~image(){
    for(int i=0;i<height;i++){
        delete[] images[i];
    }
    delete [] images;
}
Pixel& image::at(int row,int col){
    return images[row][col];
}
int image::getHeight(){
    return height;
}
int image::getWidth(){
    return width;
}
bool image::loadfromFile(string path) {
    cout << "Path length: " << path.length() << endl;
    cout << "Path: [" << path << "]" << endl;
    for(int i = 0; i < path.length(); i++)
        cout << (int)path[i] << " ";
    cout << endl;
    
int fileW, fileH, channels;
unsigned char* rawData = stbi_load(path.c_str(), &fileW, &fileH, &channels, 3);
if (rawData == nullptr) return false;
if (this->images != nullptr) {
    for(int r = 0; r < this->height; r++) {
        delete[] this->images[r];
    }
    delete[] this->images;
}
this->width = fileW;
this->height = fileH;
this->images = new Pixel*[height];
for(int r = 0; r < height; r++) {
    this->images[r] = new Pixel[width];
    for(int c = 0; c < width; c++) {
        int index = 3 * (r * width + c);
        this->images[r][c].setRed(rawData[index]);
        this->images[r][c].setGreen(rawData[index+1]);
        this->images[r][c].setBlue(rawData[index+2]);
    }
}
stbi_image_free(rawData);
return true;
}
bool image::save(string path) {
    int totalBytes = width * height * 3;
    unsigned char* rawData = new unsigned char[totalBytes];
    for(int r = 0; r < height; r++) {
        for(int c = 0; c < width; c++) {
            int index = 3 * (r * width + c);       
            rawData[index] = this->images[r][c].getRed();
            rawData[index+1] = this->images[r][c].getGreen();
            rawData[index+2] = this->images[r][c].getBlue();
        }
    }
    int success = stbi_write_png(path.c_str(), width, height, 3, rawData, width * 3);
    delete[] rawData;
    return success; 
}
void image::displayASCII(){
    cout<<"ASCII DISPLAY MADE SMALL FOR DISPLAY PURPOSES"<<endl;
    int maxRows = (height > 100) ? 100 : height;
    int maxCols = (width > 100) ? 100 : width;
    int rowStep = (height > 100) ? height / 100 : 1;
    int colStep = (width > 100) ? width / 100 : 1;
    
    for(int r=0; r<height; r+=rowStep){
        if(r >= maxRows * rowStep) break;
        for(int c=0; c<width; c+=colStep){
            if(c >= maxCols * colStep) break;
            cout << images[r][c];
        }
        cout<<endl;
    }
    cout<<"Image: "<<width<<"x"<<height<<" pixels"<<endl;
}