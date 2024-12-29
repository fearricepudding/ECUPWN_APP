#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/can.h>

class udp_listener {
public:
    udp_listener(std::string, std::string);
    int setup();
    canfd_frame recieve();
    void close();

private:
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    std::string target;
    std::string port;
    int yes = 1;
};
