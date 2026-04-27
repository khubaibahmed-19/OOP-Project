#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "customer.h"
using namespace std;
class customerManager {
public:
    vector<customer> loadAll(string filepath);
    void saveAll(vector<customer> customers, string filepath);
    customer* findByCnic(vector<customer>& customers, string cnic);
    void addCustomer(vector<customer>& customers, customer c);
    void blockCustomer(vector<customer>& customers, string cnic);
    void deleteCustomer(vector<customer>& customers, string cnic);
};