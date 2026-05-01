#pragma once
#include "user.h"
#include <string>
using namespace std;
class customer : public user {
    string gender;
    string phone;
    string city;
    bool isBlocked;
    int sessionCount;
public:
    customer();
    customer(string cnic, string password, string name, string gender, string phone, string city);
    int showMenu() override;
    string getRole() override;
    string getGender();
    string getPhone();
    string getCity();
    bool isAccountBlocked();
    void setBlocked(bool val);
    void incrementSession();
    int getSessionCount();
    ~customer();
};