#pragma once
#include "user.h"
#include <string>
using namespace std;
class admin : public user {
    static const string HARDCODED_PASSWORD;
    static const string HARDCODED_CNIC;
public:
    admin();
    int showMenu() override;
    string getRole() override;
    ~admin();
};