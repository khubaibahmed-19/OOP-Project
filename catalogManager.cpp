#include"catalogManager.h"
vector<filter>catalogManager::loadCatalog(string filepath){
    vector<filter> filters;
    ifstream file (filepath);
    while(!file.is_open()){return filters;}
    string line;
    string fields[3];
    while(getline(file,line)){
    if(line.empty()){continue;}
    int idx=0;
    string token="";
    for(int i=0;i<line.size();i++){
        if(line[i]==' '){
            fields[idx]=token;
            token="";
        }else{
            token=token+line[i];
        }
        }
        int id=stoi(fields[0]);
        string name=fields[1];
        if(fields[2]=="true"){
            bool isEnabled=true;
        }else if(fields[2]=="false"){
            bool isEnabled=false;
        }
        
    }
}