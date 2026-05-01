#pragma once
#include<string>
#include<vector>
using namespace std;
class Validator{
    public:
    bool isValidCnic(string cnic, string blockedCnicFile, string customersFile);
    bool isValidPassword(string password);
    bool isValidGender(string gender);
    bool isPhone(string phone);
};