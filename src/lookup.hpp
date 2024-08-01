#pragma once
#include "../include/json.hpp"

using json = nlohmann::json;

class Lookup{
public: 
    std::string findCode(std::string);
    Lookup();
    int getStatus();
private: 
    int loadCodes();
    json data;
    int status;
};
