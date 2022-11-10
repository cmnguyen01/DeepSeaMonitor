// Alex Westover

#include"UdpHandler.h"
#include <string>
#include <qdebug.h>

using namespace std;
using std::string;

UdpHandler::UdpHandler(char * listen, int bufferSize, int port){
    listening = false;
    updated = false;

    cout << listening << endl;

    // Initalize Buffer size
    //buffer = new char[bufferSize];
    size = bufferSize;

    // Initalize Socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Internet for now, Ethernet Later
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(listen);
    address.sin_port = htons( port );

    // Bind to socket
    if (::bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

UdpHandler::~UdpHandler(){

    // Make sure thread stops
    if(isListening()){
        stopListening();
        t->join();
    }
    delete buffer;
}

void UdpHandler::startListening(){
    listening = true;
    // New thread
    t = new thread(&UdpHandler::startListen, this);
    cout << "Started Listening!" << endl;
}

void UdpHandler::stopListening(){
    listening = false;
}

void UdpHandler::startListen(){

    buffer = new char[size];
    while(listening)
    {
        int val = read(socket_fd,buffer,size);

        dataDecoder->updateBuffer(buffer, val);
        //dataDecoder->printBuffer();
        dataDecoder->parseData();

    }
}

bool UdpHandler::isListening(){
    return listening;
}

char * UdpHandler::getBuffer()
{
    return buffer;
}

bool UdpHandler::isUpdated()
{
    return updated;
}







