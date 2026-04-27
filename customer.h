#pragma once
#include"user.h"
#include<string>
using namespace std;
class customer:public user{
    string gender;
    string city;
    string number;
    bool isBlocked;
    int sessionCount;
    public:
    customer(string cnic, string name, string password, string g, string c, string n);
    int showMenu () override;
    string getRole();
    void BuildPipeline();
    void applyandSave();
    void viewHistory();
    bool isAccountBlocked();
    string getCity();
    string getPhone();
    string getGender();
    void setBlocked(bool val);
    ~customer();
};