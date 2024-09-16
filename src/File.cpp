#include "File.h"
#include "../include/json.hpp"

#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

File::File(std::string path) {
    this->_path = path; 
};

nlohmann::json File::getContent() {
    nlohmann::json data;
    std::ifstream file(this->_path, std::ios::binary);
    try {
        data = nlohmann::json::parse(file);
        return data;
    } catch(nlohmann::json::parse_error &e) {
        throw e;
    };
    return data;
};

bool File::exists() {
    if (boost::filesystem::exists(this->_path)) {
        return true;
    };
    return false;
};

void File::writeContent(nlohmann::json data) {
    std::string dataString = data.dump();
    const char* blah = dataString.c_str();
    std::ofstream ostrm(this->_path, std::ios::binary);
    ostrm.write(blah, sizeof(char)*strlen(blah));
};