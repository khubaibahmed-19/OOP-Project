#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class blockedCnicManager {
public:
    bool isBlocked(string cnic, string filepath);
    void addBlocked(string cnic, string filepath);
    vector<string> loadAll(string filepath);
};