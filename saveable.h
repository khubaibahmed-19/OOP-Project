#pragma once
#include<string>
using namespace std;
class Validator{
    public:
    bool isValidCnic(string cnic);
    bool isValidPassword(string password);
    bool isValidGender(string gender);
    bool isPhone(string phone);
};