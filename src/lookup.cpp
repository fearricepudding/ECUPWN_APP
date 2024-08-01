#include "lookup.hpp"

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
    };
    return response;
};

int Lookup::loadCodes() {
    std::ifstream f("codes.json");
    try{
        this->data = json::parse(f);
    }catch(json::parse_error& e){
        return 1;
    };
    return 0;
};

