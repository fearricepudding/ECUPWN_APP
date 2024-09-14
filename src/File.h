#pragma once

#include "../include/json.hpp"

#include <iostream>

class File {
public:
    File(std::string);
    nlohmann::json getContent();

private:
    std::string _path;
};