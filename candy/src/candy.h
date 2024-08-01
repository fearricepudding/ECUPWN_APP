#pragma once

#include <string>

struct can_frame;

class Candy {
public: 
    Candy();
    ~Candy();
    can_frame recieve();
    int send();
    void setup();
    void shutdown();
    std::string getError();
    bool isConnected();

private:
    int setupCanLink();
    void closeCanLink();
    std::string error;
    bool _connected;
    int s;
};
