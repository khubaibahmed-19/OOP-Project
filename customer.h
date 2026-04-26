#pragma once
#include"user.h"
#include<string>
using namespace std;
class customer:public user{
    string role;
    string gender;
    string city;
    string number;
    bool isBlocked;
    int sessionCount;
    public:
    customer(string cnic, string name, string password, string r, string g, string c, string n);
    int showMenu () override;
    string getRole();
    void BuildPipeline();
    void applyandSave();
    void viewHistory();
    bool isAccountBlocked();
    ~customer();
};