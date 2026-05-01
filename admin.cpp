#include "admin.h"
#include <iostream>
using namespace std;
const string admin::HARDCODED_PASSWORD = "Admin1234";
const string admin::HARDCODED_CNIC = "0016";
admin::admin() : user(HARDCODED_CNIC, HARDCODED_PASSWORD, "Admin") {}
admin::~admin() {}
int admin::showMenu() {
    int choice;
    cout << "       ADMIN PANEL : Image Filter Studio   " << endl;
    cout << "1) Manage Filter Catalog" << endl;
    cout << "2) Manage Customers" << endl;
    cout << "3) View All Sessions" << endl;
    cout << "4) Logout" << endl;
    cin >> choice;
    return choice;
}
string admin::getRole() {
    return "Admin";
}