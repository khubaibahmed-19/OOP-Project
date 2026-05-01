#include <iostream>
#include <string>
#include "image.h"
#include "pixel.h"
#include "filter.h"
#include "grayscale.h"
#include "invert.h"
#include "brightness.h"
#include "stretch.h"
#include "redChannel.h"
#include "greenChannel.h"
#include "blueChannel.h"
#include "boxBlur.h"
#include "flipHorizontal.h"
#include "flipVertical.h"
#include "filterSession.h"
#include "customer.h"
#include "admin.h"
#include "customerManager.h"
#include "sessionManager.h"
#include "Bcnic.h"
using namespace std;

void testFilters(string imagePath) {
    cout << "=== FILTER TEST ===" << endl;
    image* img = new image(0, 0);
    if (!img->loadfromFile(imagePath)) {
        cout << "Failed to load image" << endl;
        delete img;
        return;
    }
    cout << "Image loaded: " << img->getWidth() << "x" << img->getHeight() << endl;
    filterSession session("1234567890123", "20260501_120000");
    session.setImage(img);
    session.addFilter(new grayscale(0, "Grayscale", true))
           .addFilter(new brightness(0, "Brightness", true))
           .addFilter(new flipHorizontal(0, "FlipHorizontal", true));
    session.applyAll();
    session.saveResult("test_output.png");
    cout << "Pipeline: " << session.getPipeline() << endl;
    cout << "Output saved as test_output.png" << endl;
}

void testCustomerManager() {
    cout << "\n=== CUSTOMER MANAGER TEST ===" << endl;
    customerManager cm;
    vector<customer> customers = cm.loadAll("customers.txt");
    cout << "Loaded " << customers.size() << " customers" << endl;
    customer c("1234567890123", "Admin1234", "Test User", "M", "03001234567", "Lahore");
    cm.addCustomer(customers, c);
    cout << "Added customer: " << c.getName() << endl;
    customer* found = cm.findByCnic(customers, "1234567890123");
    if (found != nullptr) {
        cout << "Found customer: " << found->getName() << endl;
    }
    cm.blockCustomer(customers, "1234567890123");
    found = cm.findByCnic(customers, "1234567890123");
    if (found != nullptr) {
        cout << "Is blocked: " << (found->isAccountBlocked() ? "Yes" : "No") << endl;
    }
    cm.saveAll(customers, "customers.txt");
    cout << "Saved to customers.txt" << endl;
}

void testBlockedCnic() {
    cout << "\n=== BLOCKED CNIC TEST ===" << endl;
    blockedCnicManager bcm;
    bcm.addBlocked("1234567890123", "blocked_cnics.txt");
    cout << "Added to blocked list" << endl;
    bool blocked = bcm.isBlocked("1234567890123", "blocked_cnics.txt");
    cout << "Is blocked: " << (blocked ? "Yes" : "No") << endl;
    bool notBlocked = bcm.isBlocked("9999999999999", "blocked_cnics.txt");
    cout << "Random CNIC blocked: " << (notBlocked ? "Yes" : "No") << endl;
}

void testSessionManager() {
    cout << "\n=== SESSION MANAGER TEST ===" << endl;
    sessionManager sm;
    sm.appendSession("1234567890123", "20260501_120000", "Grayscale>Invert", "1234567890123_20260501_120000.png", "sessions.txt");
    sm.appendSession("1234567890123", "20260501_130000", "RedChannel>FlipHorizontal", "1234567890123_20260501_130000.png", "sessions.txt");
    sm.appendSession("9999999999999", "20260501_140000", "BoxBlur", "9999999999999_20260501_140000.png", "sessions.txt");
    cout << "Appended 3 sessions" << endl;
    vector<Session> mySessions = sm.loadForCnic("1234567890123", "sessions.txt");
    cout << "Sessions for 1234567890123: " << mySessions.size() << endl;
    for (int i = 0; i < mySessions.size(); i++) {
        cout << "  " << mySessions[i].timestamp << " | " << mySessions[i].filtersApplied << endl;
    }
    vector<Session> all = sm.loadAll("sessions.txt");
    cout << "Total sessions: " << all.size() << endl;
}

void testAdminLogin() {
    cout << "\n=== ADMIN LOGIN TEST ===" << endl;
    admin a;
    string pass;
    cout << "Enter admin password: ";
    cin >> pass;
    if (a.checkPassword(pass)) {
        cout << "Login successful. Role: " << a.getRole() << endl;
    } else {
        cout << "Wrong password" << endl;
    }
}

void testCustomerLogin() {
    cout << "\n=== CUSTOMER LOGIN TEST ===" << endl;
    customerManager cm;
    vector<customer> customers = cm.loadAll("customers.txt");
    string cnic, pass;
    cout << "Enter CNIC: ";
    cin >> cnic;
    cout << "Enter password: ";
    cin >> pass;
    customer* found = cm.findByCnic(customers, cnic);
    if (found == nullptr) {
        cout << "Customer not found" << endl;
        return;
    }
    if (found->isAccountBlocked()) {
        cout << "Account is blocked" << endl;
        return;
    }
    if (found->checkPassword(pass)) {
        cout << "Login successful. Welcome " << found->getName() << endl;
        cout << "Role: " << found->getRole() << endl;
    } else {
        cout << "Wrong password" << endl;
    }
}

int main() {
    int choice;
    cout << "=== IMAGE FILTER STUDIO TEST MENU ===" << endl;
    cout << "1) Test Filters + FilterSession" << endl;
    cout << "2) Test Customer Manager" << endl;
    cout << "3) Test Blocked CNIC Manager" << endl;
    cout << "4) Test Session Manager" << endl;
    cout << "5) Test Admin Login" << endl;
    cout << "6) Test Customer Login" << endl;
    cout << "7) Run All Tests" << endl;
    cin >> choice;
    if (choice == 1) {
        string path;
        cout << "Enter image path: ";
        cin >> path;
        testFilters(path);
    } else if (choice == 2) {
        testCustomerManager();
    } else if (choice == 3) {
        testBlockedCnic();
    } else if (choice == 4) {
        testSessionManager();
    } else if (choice == 5) {
        testAdminLogin();
    } else if (choice == 6) {
        testCustomerLogin();
    } else if (choice == 7) {
        testCustomerManager();
        testBlockedCnic();
        testSessionManager();
        testAdminLogin();
    }
    return 0;
}