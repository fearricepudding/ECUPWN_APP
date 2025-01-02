#include "udp_listener.h"

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
#include <sys/poll.h>


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


udp_listener::udp_listener(std::string ip, std::string port) {
    this->target = ip;
    this->port = port;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

};

int udp_listener::setup() {
    if ((rv = getaddrinfo(target.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
        std::cout << "[!] An error occured connecting to socket" << std::endl;
        return -1;
    };

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cout << "An error occured creating socket" << std::endl;
            continue;
        };

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            ::close(sockfd);
            perror("client: connect");
            continue;
        };

        break;
    };

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    char s[INET6_ADDRSTRLEN];
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo);
    return 0;
};

void udp_listener::close() {
    ::close(sockfd);
};

canfd_frame udp_listener::recieve() {
    int numbytes;

    canfd_frame newframe;

    struct pollfd ufds[1];
    ufds[0].fd = sockfd;
    ufds[0].events = POLLIN;

    rv = poll(ufds, 1, 2000);
    if (rv == -1) {
        // error with poll
        std::cout << "Error with poll" << std::endl;
        exit(1);
    } else if (rv == 0) {
        // Timeout no data
        std::cout << "timeout" << std::endl;
    } else {
        if ((numbytes = recv(sockfd, &newframe, sizeof(canfd_frame), 0)) == -1) {
            perror("recv");
            exit(1);
        };
    };
    return newframe;
};



