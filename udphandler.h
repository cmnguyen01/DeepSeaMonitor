#ifndef UDPHANDLER_H_
#define UDPHANDLER_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <thread>
#include "datadecoder.h"

using namespace std;

class UdpHandler{
    public:
        UdpHandler(char*,int,int);
        ~UdpHandler();
        void startListening();
        bool isListening();
        void stopListening();
        char * getBuffer();
        bool isUpdated();
    private:
        bool listening;
        bool updated;
        int socket_fd;
        char * buffer;
        int size;
        struct sockaddr_in address;
        void startListen();
        thread * t;
        dataDecoder * dataDecoder;
};


#endif
