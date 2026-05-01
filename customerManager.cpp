#include "customerManager.h"
vector<customer> customerManager::loadAll(string filepath) {
    vector<customer> customers;
    ifstream file(filepath);
    if (!file.is_open()) return customers;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string fields[7];
        int idx = 0;
        string token = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '|') {
                fields[idx++] = token;
                token = "";
            } else {
                token += line[i];
            }
        }
        fields[idx] = token;
        string cnic     = fields[0];
        string password = fields[1];
        string name     = fields[2];
        string gender   = fields[3];
        string phone    = fields[4];
        string city     = fields[5];
        bool isBlocked  = (fields[6] == "1");
        customer c(cnic, password, name, gender, phone, city);
        if (isBlocked) c.setBlocked(true);
        customers.push_back(c);
    }
    file.close();
    return customers;
}
void customerManager::saveAll(vector<customer> customers, string filepath) {
    ofstream file(filepath);
    for (int i = 0; i < customers.size(); i++) {
        file << customers[i].getCnic()     << "|"
             << customers[i].getPassword() << "|"
             << customers[i].getName()     << "|"
             << customers[i].getGender()   << "|"
             << customers[i].getPhone()    << "|"
             << customers[i].getCity()     << "|"
             << (customers[i].isAccountBlocked() ? "1" : "0")
             << "\n";
    }
    file.close();
}
customer* customerManager::findByCnic(vector<customer>& customers, string cnic) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getCnic() == cnic) return &customers[i];
    }
    return nullptr;
}
void customerManager::addCustomer(vector<customer>& customers, customer c) {
    customers.push_back(c);
}
void customerManager::blockCustomer(vector<customer>& customers, string cnic) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getCnic() == cnic) {
            customers[i].setBlocked(true);
            break;
        }
    }
}
void customerManager::deleteCustomer(vector<customer>& customers, string cnic) {
    vector<customer> updated;
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getCnic() != cnic) updated.push_back(customers[i]);
    }
    customers = updated;
}