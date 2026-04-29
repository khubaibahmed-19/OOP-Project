#include"catalogManager.h"
vector<filter*> catalogManager::loadCatalog(string filepath){
    vector<filter*> filters;
    ifstream file (filepath);
    if(!file.is_open()){return filters;}
    string line;
    string fields[3];
    bool isEnabled=false;
    while(getline(file,line)){
        if(line.empty()){continue;}
        int idx=0;
        string token="";
        for(int i=0;i<line.size();i++){
            if(line[i]==' '){
                fields[idx]=token;
                token="";
                idx++;
            }else{
                token=token+line[i];
            }
        }
        fields[idx]=token;

        int id=stoi(fields[0]);
        string name=fields[1];
        if(fields[2]=="true"){
            isEnabled=true;
        }else if(fields[2]=="false"){
            isEnabled=false;
        }

        if (name == "Grayscale") {
            filters.push_back(new grayscale(id, name, isEnabled));
        } else if (name == "Invert") {
            filters.push_back(new invert(id, name, isEnabled));
        } else if (name == "Brightness") {
            filters.push_back(new brightness(id, name, isEnabled));
        } else if (name == "Stretch") {
            filters.push_back(new stretch(id, name, isEnabled));
        } else if (name == "RedChannel") {
            filters.push_back(new redChannel(id, name, isEnabled));
        } else if (name == "GreenChannel") {
            filters.push_back(new greenChannel(id, name, isEnabled));
        } else if (name == "BlueChannel") {
            filters.push_back(new blueChannel(id, name, isEnabled));
        } else if (name == "BoxBlur") {
            filters.push_back(new boxBlur(id, name, isEnabled));
        } else if (name == "FlipHorizontal") {
            filters.push_back(new flipHorizontal(id, name, isEnabled));
        } else if (name == "FlipVertical") {
            filters.push_back(new flipVertical(id, name, isEnabled));
        }
    }
    file.close();
    return filters;
}

void catalogManager::saveCatalog(vector<filter*> filters, string filepath){
    ofstream file(filepath);
    for(int i=0;i<filters.size();i++){
        string status;
        if(filters[i]->getStatus()){
            status = "true";
        }else{
            status = "false";
        }
        file << filters[i]->getID() << " " << filters[i]->getName() << " " << status << endl;
    }
    file.close();
}

void catalogManager::toggleFilter(vector<filter*>& filters, int id, bool v, string filepath){
    for(int i=0;i<filters.size();i++){
        if(filters[i]->getID() == id){
            filters[i]->setEnabled(v);
            break;
        }
    }
    ofstream file(filepath);
    for(int i=0;i<filters.size();i++){
        string status;
        if(filters[i]->getStatus()){
            status = "true";
        }else{
            status = "false";
        }
        file << filters[i]->getID() << " " << filters[i]->getName() << " " << status << endl;
    }
    file.close();
}