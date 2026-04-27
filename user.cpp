#include"user.h"
user::user(){
    password="";
    name="";
    Cnic="";
}
user::user(string cnic,string password,string name){
    Cnic=cnic;
    this->password=password;
    this->name=name;
}
user::~user(){}
bool user::checkPassword(string p){
    if(password==p){
        return true;
    }else{return false;}
}
string user::getCnic()const {
    return Cnic;
}
string user::getName(){
    return name;
}
string user::getPassword(){
    return password;
}
