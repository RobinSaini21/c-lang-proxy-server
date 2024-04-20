#ifndef PROXY_SERVER_H
#define PROXY_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __linux__
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

#define PORT 8080
#define BUFFER_SIZE 1024

// Function prototypes
int proxy_server();

#endif /* PROXY_SERVER_H */
