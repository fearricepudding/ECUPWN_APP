#include "File.h"
#include "../include/json.hpp"

#include <fstream>
#include <iostream>

File::File(std::string path) {
    this->_path= path; 
};

nlohmann::json File::getContent() {
    nlohmann::json data;
    std::ifstream file(this->_path);
    try {
        data = nlohmann::json::parse(file);
        return data;
    } catch(nlohmann::json::parse_error &e) {
        std::cout << "Failed to parse file: " << this->_path << std::endl;
        throw e;
    };
    return data;
};