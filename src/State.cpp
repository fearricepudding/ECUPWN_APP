#include "State.h"
#include "File.h"

State::State(std::string path) {
    this->dataFile = new File(path);
};

void State::load() {
    try{
        this->state = this->dataFile->getContent();
        std::string init = this->state["initiated"];
        std::cout << init;
        return;
    } catch(nlohmann::json::parse_error &e) {
        std::cout << "[!] Could not load state" << std::endl;
    } catch(nlohmann::json::out_of_range &e) {
        std::cout << "Out of range" << std::endl;
    } catch(nlohmann::json::type_error &e) {
        std::cout << "Type error" << std::endl;
    }
    this->create();
};

void State::create() {
    this->state["initiated"] = "true";
    this->save();
}

void State::save() {
    try {
        this->dataFile->writeContent(this->state);
    } catch(std::exception &e) {
        std::cout << "ERROR" << std::endl;
    }
}