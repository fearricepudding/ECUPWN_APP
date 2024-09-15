#pragma once

#include "../include/json.hpp"
#include "File.h"

class State{
public:
    State(std::string);
    void load();
    void save();
    void create();

    nlohmann::json state;

private:
    File *dataFile;
};