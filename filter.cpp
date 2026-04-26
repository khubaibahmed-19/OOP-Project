#include"filter.h"
filter::filter(){name="";ID=0;isEnabled=false;}
string filter::getName(){
    return name;
}
int filter::getID()const{
    return ID;
}

bool filter::getStatus(){
    return isEnabled;
}
void filter::setEnabled(bool v){
    isEnabled=v;
}


