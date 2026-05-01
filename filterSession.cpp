#include "filterSession.h"
#include <iostream>
using namespace std;
filterSession::filterSession(string customerID, string timestamp) {
    this->customerID = customerID;
    this->timestamp = timestamp;
    picture = nullptr;
}
filterSession::~filterSession() {
    for (int i = 0; i < pipeline.size(); i++) {
        delete pipeline[i];
    }
    delete picture;
}
filterSession& filterSession::addFilter(filter* f) {
    pipeline.push_back(f);
    return *this;
}
void filterSession::applyAll() {
    if (picture == nullptr) {
        cout << "No image loaded" << endl;
        return;
    }
    for (int i = 0; i < pipeline.size(); i++) {
        cout << "Applying filter " << i + 1 << "/" << pipeline.size() << ": " << pipeline[i]->getName() << " ..." << endl;
        picture = pipeline[i]->apply(picture);
        previewASCII();
    }
}
void filterSession::previewASCII() {
    if (picture == nullptr) {
        cout << "No image loaded" << endl;
        return;
    }
    picture->displayASCII();
}
bool filterSession::saveResult(string filepath) {
    if (picture == nullptr) {
        cout << "No image to save" << endl;
        return false;
    }
    return picture->save(filepath);
}
string filterSession::getPipeline() {
    string result = "";
    for (int i = 0; i < pipeline.size(); i++) {
        result += pipeline[i]->getName();
        if (i != pipeline.size() - 1) result += ">";
    }
    return result;
}
void filterSession::setImage(image* img) {
    picture = img;
}