
#pragma once

#include <iostream>


struct can_frame;
class Candy{

public: 
    Candy();
    ~Candy();
    can_frame recieve();
    int send();


private:
    int setupCanLink();
    void closeCanLink();
    int s;
};
