#include <iostream>
#include <string>
#include<fstream>
#include <vector>
#include <ctime>
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
#include "catalogManager.h"
#include "Bcnic.h"
#include "saveable.h"
using namespace std;
const string CUSTOMERS_FILE = "customers.txt";
const string CATALOG_FILE = "catalog.txt";
const string SESSIONS_FILE = "sessions.txt";
const string BLOCKED_FILE = "blocked_cnics.txt";
string getCurrentTimestamp() {
    time_t now = time(0);
    tm* t = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", t);
    return string(buf);
}
void printLine() {
    cout << "============================================" << endl;
}
void printBox(string title) {
    printLine();
    cout << "   " << title << endl;
    printLine();
}
void registerCustomer(customerManager& cm, vector<customer>& customers, blockedCnicManager& bcm) {
    printBox("CUSTOMER REGISTRATION");
    Validator v;
    string cnic, password, confirm, name, gender, phone, city;
    while (true) {
        cout << "Enter CNIC (13 digits): ";
        cin >> cnic;
        if (!v.isValidCnic(cnic, BLOCKED_FILE, CUSTOMERS_FILE)) {
            cout << "Invalid CNIC. Must be 13 digits, not blocked, and not already registered." << endl;
            continue;
        }
        break;
    }
    while (true) {
        cout << "Enter Password (8+ chars, uppercase + lowercase + digit + special): ";
        cin >> password;
        if (!v.isValidPassword(password)) {
            cout << "Invalid password. Need 8+ chars with uppercase, lowercase, digit, and special char." << endl;
            continue;
        }
        cout << "Confirm Password: ";
        cin >> confirm;
        if (password != confirm) {
            cout << "Passwords do not match." << endl;
            continue;
        }
        break;
    }
    cin.ignore();
    cout << "Full Name: ";
    getline(cin, name);
    while (true) {
        cout << "Gender (M / F): ";
        cin >> gender;
        if (v.isValidGender(gender)) break;
        cout << "Invalid. Enter M or F." << endl;
    }
    while (true) {
        cout << "Phone (11 digits, starts with 0): ";
        cin >> phone;
        if (v.isPhone(phone)) break;
        cout << "Invalid phone. Must be 11 digits starting with 0." << endl;
    }
    cout << "City: ";
    cin >> city;
    customer c(cnic, password, name, gender, phone, city);
    cm.addCustomer(customers, c);
    cm.saveAll(customers, CUSTOMERS_FILE);
    cout << "Registration successful! Welcome, " << name << "." << endl;
}
void manageCatalog(catalogManager& catMgr, vector<filter*>& filters) {
    int choice;
    while (true) {
        printBox("MANAGE FILTER CATALOG");
        cout << "ID  Name              Status" << endl;
        cout << "------------------------------------" << endl;
        for (int i = 0; i < (int)filters.size(); i++) {
            cout << filters[i]->getID() << "   " << filters[i]->getName() << "\t\t" << (filters[i]->getStatus() ? "[Enabled]" : "[Disabled]") << endl;
        }
        cout << "1) Enable a filter" << endl;
        cout << "2) Disable a filter" << endl;
        cout << "3) Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        if (choice == 3) break;
        int id;
        cout << "Enter filter ID: ";
        cin >> id;
        if (choice == 1)
            catMgr.toggleFilter(filters, id, true, CATALOG_FILE);
        else if (choice == 2)
            catMgr.toggleFilter(filters, id, false, CATALOG_FILE);
        cout << "Done." << endl;
    }
}
void manageCustomers(customerManager& cm, vector<customer>& customers, blockedCnicManager& bcm) {
    int choice;
    while (true) {
        printBox("MANAGE CUSTOMERS");
        cout << "1) View all customers" << endl;
        cout << "2) Search by CNIC" << endl;
        cout << "3) Block a customer" << endl;
        cout << "4) Delete a customer" << endl;
        cout << "5) Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "CNIC          | Name           | Gender | Phone       | City     | Blocked" << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < (int)customers.size(); i++) {
                cout << customers[i].getCnic() << " | " << customers[i].getName() << "\t| " << customers[i].getGender() << "      | " << customers[i].getPhone() << " | " << customers[i].getCity() << "\t| " << (customers[i].isAccountBlocked() ? "Yes" : "No") << endl;
            }
        } else if (choice == 2) {
            string cnic;
            cout << "Enter CNIC: ";
            cin >> cnic;
            customer* c = cm.findByCnic(customers, cnic);
            if (c == nullptr) { cout << "Not found." << endl; continue; }
            cout << "Name: " << c->getName() << " | City: " << c->getCity() << " | Blocked: " << (c->isAccountBlocked() ? "Yes" : "No") << endl;
        } else if (choice == 3) {
            string cnic;
            cout << "Enter CNIC to block: ";
            cin >> cnic;
            cm.blockCustomer(customers, cnic);
            bcm.addBlocked(cnic, BLOCKED_FILE);
            cm.saveAll(customers, CUSTOMERS_FILE);
            cout << "Customer blocked." << endl;
        } else if (choice == 4) {
            string cnic;
            cout << "Enter CNIC to delete: ";
            cin >> cnic;
            cm.deleteCustomer(customers, cnic);
            cm.saveAll(customers, CUSTOMERS_FILE);
            cout << "Customer deleted." << endl;
        } else if (choice == 5) {
            break;
        }
    }
}
void viewAllSessions() {
    sessionManager sm;
    vector<Session> all = sm.loadAll(SESSIONS_FILE);
    if (all.empty()) { cout << "No sessions recorded." << endl; return; }
    cout << "CNIC          | Timestamp        | Filters Applied         | Output File" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < (int)all.size(); i++) {
        cout << all[i].cnic << " | " << all[i].timestamp << " | " << all[i].filtersApplied << " | " << all[i].outputFile << endl;
    }
}
void runAdminPanel(vector<customer>& customers, vector<filter*>& filters) {
    admin a;
    printBox("ADMIN LOGIN");
    cout << "Enter CNIC: ";
    string cnic; cin >> cnic;
    cout << "Enter Password: ";
    string pass; cin >> pass;
    if (cnic != a.getCnic() || !a.checkPassword(pass)) {
        cout << "Invalid admin credentials." << endl;
        return;
    }
    customerManager cm;
    catalogManager catMgr;
    blockedCnicManager bcm;
    int choice;
    while (true) {
        choice = a.showMenu();
        if (choice == 1) manageCatalog(catMgr, filters);
        else if (choice == 2) manageCustomers(cm, customers, bcm);
        else if (choice == 3) viewAllSessions();
        else if (choice == 4) { cout << "Logged out." << endl; break; }
        else cout << "Invalid choice." << endl;
    }
}
void browseCatalog(vector<filter*>& filters) {
    printBox("FILTER CATALOG");
    cout << "ID  Name              Status" << endl;
    cout << "------------------------------------------------------" << endl;
    for (int i = 0; i < (int)filters.size(); i++) {
        cout << filters[i]->getID() << "   " << filters[i]->getName() << "\t\t" << (filters[i]->getStatus() ? "[Enabled]" : "[Disabled]") << endl;
    }
}
void runCustomerPanel(customer* cust, vector<filter*>& filters) {
    sessionManager sm;
    filterSession* session = nullptr;
    bool imageLoaded = false;
    int choice;
    while (true) {
        choice = cust->showMenu();
        if (choice == 1) {
            browseCatalog(filters);
        } else if (choice == 2) {
            if (session != nullptr) { delete session; session = nullptr; }
            string timestamp = getCurrentTimestamp();
            session = new filterSession(cust->getCnic(), timestamp);
            cout << "1) Load from JPG/PNG file" << endl;
            cout << "2) Generate test pattern" << endl;
            cout << "Choice: ";
            int imgChoice; cin >> imgChoice;
            image* img = nullptr;
            if (imgChoice == 1) {
                cout << "Enter image path: ";
                cin.ignore();
                string path;
                getline(cin, path);
                img = new image(0, 0);
                if (!img->loadfromFile(path)) {
                    cout << "Failed to load image." << endl;
                    delete img;
                    delete session;
                    session = nullptr;
                    continue;
                }
                cout << "Image loaded: " << img->getWidth() << "x" << img->getHeight() << endl;
            } else {
                img = new image(20, 10);
                for (int r = 0; r < 10; r++)
                    for (int c = 0; c < 20; c++) {
                        int val = (r * 20 + c) * 255 / 200;
                        img->at(r, c).setRed(val);
                        img->at(r, c).setGreen(val / 2);
                        img->at(r, c).setBlue(255 - val);
                    }
                cout << "Test pattern generated: 20x10" << endl;
            }
            session->setImage(img);
            imageLoaded = true;
            cout << "=== ASCII Preview ===" << endl;
            session->previewASCII();
        } else if (choice == 3) {
            if (!imageLoaded || session == nullptr) {
                cout << "Please load an image first." << endl; continue;
            }
            cout << "=== Build Filter Pipeline ===" << endl;
            browseCatalog(filters);
            cout << "Enter filter ID to add (0 to finish): ";
            int id;
            while (cin >> id && id != 0) {
                filter* found = nullptr;
                for (int i = 0; i < (int)filters.size(); i++) {
                    if (filters[i]->getID() == id) { found = filters[i]; break; }
                }
                if (found == nullptr) { cout << "Filter not found." << endl; }
                else if (!found->getStatus()) { cout << "Filter is disabled by admin." << endl; }
                else {
                    filter* clone = nullptr;
                    string n = found->getName();
                    if (n == "Grayscale") clone = new grayscale(id, n, true);
                    else if (n == "Invert") clone = new invert(id, n, true);
                    else if (n == "Brightness") {
                        int amount;
                        cout << "Enter brightness amount (-100 to +100): ";
                        cin >> amount;
                        brightness* b = new brightness(id, n, true);
                        b->setBrightness(amount);
                        clone = b;
                    }
                    else if (n == "Stretch") clone = new stretch(id, n, true);
                    else if (n == "RedChannel") clone = new redChannel(id, n, true);
                    else if (n == "GreenChannel") clone = new greenChannel(id, n, true);
                    else if (n == "BlueChannel") clone = new blueChannel(id, n, true);
                    else if (n == "BoxBlur") clone = new boxBlur(id, n, true);
                    else if (n == "FlipHorizontal") clone = new flipHorizontal(id, n, true);
                    else if (n == "FlipVertical") clone = new flipVertical(id, n, true);
                    if (clone) {
                        session->addFilter(clone);
                        cout << "Added: " << n << endl;
                        cout << "Pipeline: [ " << session->getPipeline() << " ]" << endl;
                    }
                }
                cout << "Enter filter ID to add (0 to finish): ";
            }
        } else if (choice == 4) {
            if (!imageLoaded || session == nullptr) {
                cout << "Please load an image and build a pipeline first." << endl; continue;
            }
            cout << "=== Applying Pipeline ===" << endl;
            session->applyAll();
            cout << "Save result? (y/n): ";
            char yn; cin >> yn;
            if (yn == 'y' || yn == 'Y') {
                string timestamp = getCurrentTimestamp();
                string outfile = cust->getCnic() + "_" + timestamp + ".png";
                if (session->saveResult(outfile)) {
                    cout << "Saved to: " << outfile << endl;
                    sm.appendSession(cust->getCnic(), timestamp, session->getPipeline(), outfile, SESSIONS_FILE);
                    cust->incrementSession();
                    cout << "Session recorded." << endl;
                } else {
                    cout << "Failed to save image." << endl;
                }
            }
            delete session; session = nullptr; imageLoaded = false;
        } else if (choice == 5) {
            vector<Session> hist = sm.loadForCnic(cust->getCnic(), SESSIONS_FILE);
            if (hist.empty()) { cout << "No sessions yet." << endl; continue; }
            cout << "Timestamp        | Filters Applied         | Output File" << endl;
            cout << "--------------------------------------------------------------" << endl;
            for (int i = 0; i < (int)hist.size(); i++) {
                cout << hist[i].timestamp << " | " << hist[i].filtersApplied << " | " << hist[i].outputFile << endl;
            }
        } else if (choice == 6) {
            cout << "Logged out." << endl;
            if (session) { delete session; session = nullptr; }
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}
void runCustomerLogin(vector<customer>& customers, vector<filter*>& filters) {
    printBox("CUSTOMER LOGIN");
    customerManager cm;
    string cnic, pass;
    int attempts = 0;
    while (attempts < 3) {
        cout << "Enter CNIC: "; cin >> cnic;
        cout << "Enter Password: "; cin >> pass;
        customer* found = cm.findByCnic(customers, cnic);
        if (found == nullptr) {
            cout << "Account not found." << endl;
            attempts++;
        } else if (found->isAccountBlocked()) {
            cout << "Your account is blocked. Contact admin." << endl;
            return;
        } else if (!found->checkPassword(pass)) {
            cout << "Wrong password. Attempts left: " << (3 - attempts - 1) << endl;
            attempts++;
        } else {
            runCustomerPanel(found, filters);
            cm.saveAll(customers, CUSTOMERS_FILE);
            return;
        }
    }
    cout << "Too many failed attempts. Returning to main menu." << endl;
}
int main() {
    customerManager cm;
    catalogManager catMgr;
    blockedCnicManager bcm;
    vector<customer> customers = cm.loadAll(CUSTOMERS_FILE);
    vector<filter*> filters = catMgr.loadCatalog(CATALOG_FILE);
    if (filters.empty()) {
        filters.push_back(new grayscale(1, "Grayscale", true));
        filters.push_back(new invert(2, "Invert", true));
        filters.push_back(new brightness(3, "Brightness", true));
        filters.push_back(new stretch(4, "Stretch", true));
        filters.push_back(new redChannel(5, "RedChannel", true));
        filters.push_back(new greenChannel(6, "GreenChannel", true));
        filters.push_back(new blueChannel(7, "BlueChannel", true));
        filters.push_back(new boxBlur(8, "BoxBlur", true));
        filters.push_back(new flipHorizontal(9, "FlipHorizontal", true));
        filters.push_back(new flipVertical(10, "FlipVertical", true));
        catMgr.saveCatalog(filters, CATALOG_FILE);
    }
    int choice;
    while (true) {
        printLine();
        cout << "        IMAGE FILTER STUDIO" << endl;
        printLine();
        cout << "1) Admin Login" << endl;
        cout << "2) Customer Login" << endl;
        cout << "3) New Customer? Register here" << endl;
        cout << "4) Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;
        if (choice == 1) {
            runAdminPanel(customers, filters);
            customers = cm.loadAll(CUSTOMERS_FILE);
        } else if (choice == 2) {
            runCustomerLogin(customers, filters);
        } else if (choice == 3) {
            registerCustomer(cm, customers, bcm);
        } else if (choice == 4) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    for (int i = 0; i < (int)filters.size(); i++) delete filters[i];
    return 0;
}