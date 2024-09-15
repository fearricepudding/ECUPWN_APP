#pragma once

#include "../include/json.hpp"

#include <iostream>

class File {
public:
    File(std::string);
    nlohmann::json getContent();
    void create();
    bool exists();
    void writeContent(nlohmann::json);

private:
    std::string _path;
};