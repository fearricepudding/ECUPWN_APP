#include "lookup.hpp"

#include <iostream>
#include <fstream>

Lookup::Lookup(){
    this->loadCodes();
};

std::string Lookup::findCode(std::string code){
    std::string response = "";
    try{
        response = this->data[code];
    }catch(nlohmann::json_abi_v3_11_3::detail::type_error e){
        return "Unknown code";
    };
    return response;
};

int Lookup::loadCodes(){
    std::ifstream f("codes.json");
    this->data = json::parse(f);
    return 0;
}

