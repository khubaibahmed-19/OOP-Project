#include"filter.h"
filter::filter(int ID,string name,bool IsEnabled){
    this->name=name;
    this->ID=ID;
    this->isEnabled=isEnabled;}
filter::~filter(){}
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


