#include"image.h"
#include"pixel.h"
#include<iostream>
using namespace std;
int main(){
    image picture(0,0);
    if( picture.loadfromFile("C:/Users/khuba/Downloads/3) Historical Event.jpg")){
        cout<<"file loaded successfully"<<endl;
    }else{
        cout<<"Image not found";
    }
}