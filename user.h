#pragma once
#include<string>
using namespace std;
class user{
    string Cnic;
    string name;
    string password;
    public:
    user();
    user(string cnic,string name,string password);
    virtual ~ user();
    string getCnic() const;
    string getName();
    bool checkPassword(string password);
    virtual int showMenu()=0;
    virtual string getRole()=0;
    string getPassword();
    
};