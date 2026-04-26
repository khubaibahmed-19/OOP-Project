#include"saveable.h"
bool Validator::isPhone(string phone ){
    int length=phone.length();
    if(length==11){
        return true;
    }
}
bool Validator::isValidCnic(string cnic){
    if(cnic.length()==13){
        return true; 
    }
}