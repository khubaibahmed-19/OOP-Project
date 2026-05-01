#pragma once
#include <vector>
#include <string>
#include<iostream>
#include <fstream>
using namespace std;

struct Session {
    string cnic;
    string timestamp;
    string filtersApplied;
    string outputFile;
};

class sessionManager {
public:
    void appendSession(string cnic, string timestamp, string filtersApplied, string outputFile, string filepath);
    vector<Session> loadForCnic(string cnic, string filepath);
    vector<Session> loadAll(string filepath);
};