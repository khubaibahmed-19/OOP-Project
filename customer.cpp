#include "customer.h"
#include <iostream>
using namespace std;
customer::customer() : user() {
    gender = "";
    phone = "";
    city = "";
    isBlocked = false;
    sessionCount = 0;
}
customer::customer(string cnic, string password, string name, string gender, string phone, string city)
    : user(cnic, password, name) {
    this->gender = gender;
    this->phone = phone;
    this->city = city;
    isBlocked = false;
    sessionCount = 0;
}
customer::~customer() {}
int customer::showMenu() {
    int choice;
    cout << "Welcome : " << getName() << endl;
    cout << "Sessions Completed : " << sessionCount << endl;
    cout << "------------------------------------------" << endl;
    cout << "1) Browse Filter Catalog" << endl;
    cout << "2) Load Image" << endl;
    cout << "3) Build Filter Pipeline" << endl;
    cout << "4) Apply Pipeline and Save" << endl;
    cout << "5) View My Session History" << endl;
    cout << "6) Logout" << endl;
    cin >> choice;
    return choice;
}
string customer::getRole() {
    return "Customer";
}
string customer::getGender() {
    return gender;
}
string customer::getPhone() {
    return phone;
}
string customer::getCity() {
    return city;
}
bool customer::isAccountBlocked() {
    return isBlocked;
}
void customer::setBlocked(bool val) {
    isBlocked = val;
}
void customer::incrementSession() {
    sessionCount++;
}
int customer::getSessionCount() {
    return sessionCount;
}