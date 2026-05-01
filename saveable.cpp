#include "saveable.h"
#include <cctype>
#include <fstream>
#include <iostream>
bool Validator::isValidCnic(string cnic, string blockedCnicFile, string customersFile) {
    if (cnic.length() != 13) {
        return false;
    }
    for (int i = 0; i < cnic.length(); i++) {
        if (!isdigit(cnic[i])) {
            return false;
        }
    }
    ifstream blockedFile(blockedCnicFile);
    if (blockedFile.is_open()) {
        string line;
        while (getline(blockedFile, line)) {
            if (line == cnic) {
                blockedFile.close();
                cerr << "Error: CNIC is blocked" << endl;
                return false;
            }
        }
        blockedFile.close();
    }
    ifstream customersFileStream(customersFile);
    if (customersFileStream.is_open()) {
        string line;
        while (getline(customersFileStream, line)) {
            if (line.empty()) continue;
            int idx = 0;
            string token = "";
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '|') {
                    if (token == cnic) {
                        customersFileStream.close();
                        cerr << "Error: CNIC already exists" << endl;
                        return false;
                    }
                    break;
                }
                token += line[i];
            }
        }
        customersFileStream.close();
    }
    return true;
}
bool Validator::isValidPassword(string password) {
    if (password.length() < 8) {
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (int i = 0; i < password.length(); i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}
bool Validator::isValidGender(string gender) {
    return (gender == "M" || gender == "F");
}
bool Validator::isPhone(string phone) {
    if (phone.length() != 11) {
        return false;
    }
    if (phone[0] != '0') {
        return false;
    }
    for (int i = 1; i < phone.length(); i++) {
        if (!isdigit(phone[i])) {
            return false;
        }
    }
    return true;
}
