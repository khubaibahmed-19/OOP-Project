#include"filterSession.h"
filterSession& filterSession::addfilter(filter* f){
    pipeline.push_back(f);
    return *this;         
}


