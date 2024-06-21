#pragma once
#include "../include/json.hpp"

using json = nlohmann::json;

class Lookup{
public: 
    std::string findCode(std::string);
    Lookup();
private: 
    int loadCodes();
    json data;
};
