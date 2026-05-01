#include "sessionManager.h"

void sessionManager::appendSession(string cnic, string timestamp, string filtersApplied, string outputfile, string filepath) {
    ofstream file(filepath, ios::app);
    if (!file.is_open()) {
        cout << "Could not find file" << endl;
        return;
    }
    file << cnic << "|" << timestamp << "|" << filtersApplied << "|" << outputfile << endl;
    file.close();
}

vector<Session> sessionManager::loadForCnic(string cnic, string path) {
    vector<Session> result;
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Could not find file" << endl;
        return result;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string fields[4];
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
        if (fields[0] == cnic) {
            Session sesh;
            sesh.cnic = fields[0];
            sesh.timestamp = fields[1];
            sesh.filtersApplied = fields[2];
            sesh.outputFile = fields[3];
            result.push_back(sesh);
        }
    }
    file.close();
    return result;
}

vector<Session> sessionManager::loadAll(string filepath) {
    vector<Session> sessions;
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "File not open" << endl;
        return sessions;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string fields[4];
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
        Session sesh;
        sesh.cnic = fields[0];
        sesh.timestamp = fields[1];
        sesh.filtersApplied = fields[2];
        sesh.outputFile = fields[3];
        sessions.push_back(sesh);
    }
    file.close();
    return sessions;
}