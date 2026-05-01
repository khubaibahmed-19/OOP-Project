#include "Bcnic.h"
bool blockedCnicManager::isBlocked(string cnic, string filepath) {
    ifstream file(filepath);
    if (!file.is_open()) return false;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line == cnic) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void blockedCnicManager::addBlocked(string cnic, string filepath) {
    ofstream file(filepath, ios::app);
    if (!file.is_open()) {
        cout << "Could not open file" << endl;
        return;
    }
    file << cnic << endl;
    file.close();
}
vector<string> blockedCnicManager::loadAll(string filepath) {
    vector<string> blocked;
    ifstream file(filepath);
    if (!file.is_open()) return blocked;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        blocked.push_back(line);
    }
    file.close();
    return blocked;
}