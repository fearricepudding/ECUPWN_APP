#include "State.h"
#include "File.h"

State::State(std::string path) {
    this->dataFile = new File(path);
};

nlohmann::json State::load() {
    nlohmann::json state;
    try {
        state = this->dataFile->getContent();
        std::string init = state["initiated"];
        return state;
    } catch(nlohmann::json::parse_error &e) {
        std::cout << "[!] Could not load state" << std::endl;
    } catch(nlohmann::json::out_of_range &e) {
        std::cout << "[!] State init error: out of range" << std::endl;
    } catch(nlohmann::json::type_error &e) {
        std::cout << "[!] State init error: type error" << std::endl;
    }
    state = this->create();
    return state;
};

nlohmann::json State::create() {
    std::cout << "[*] Creating new state file" << std::endl;
    nlohmann::json state;
    state["initiated"] = "true";
    this->save(state);
    return state;
}

void State::save(nlohmann::json state) {
    try {
        this->dataFile->writeContent(state);
    } catch(std::exception &e) {
        std::cout << "[!] Failed to write state: " << e.what() << std::endl;
    };
}