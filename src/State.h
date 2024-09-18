#pragma once

#include "../include/json.hpp"
#include "File.h"

class State{
public:
    State(std::string);
    nlohmann::json load();
    void save(nlohmann::json);
    nlohmann::json create();

private:
    File *dataFile;
};