#include "lookup.hpp"
#include "File.h"

#include <fstream>
#include <string>

Lookup::Lookup() {
    int status = this->loadCodes();
    this->status = status;
};

int Lookup::getStatus() {
    return this->status;
};

std::string Lookup::findCode(std::string code) {
    std::string response = "";
    try{
        response = this->data[code];
    }catch(json::type_error& e){
        return "Unknown code";
    }catch(std::exception &e) {
        return "Unknown error";
    }
    return response;
};

int Lookup::loadCodes() {
    File *codeDatabase = new File("codes.json");
    this->data = codeDatabase->getContent();
return 0;
};

