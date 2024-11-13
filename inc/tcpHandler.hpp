#ifndef JIKIMZON_TCPHANDLER_H
#define JIKIMZON_TCPHANDLER_H

#include <iostream>
#include <opencv2/opencv.hpp>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT    12345

class TcpHandler {
public:
    TcpHandler(const TcpHandler&) = delete;
    TcpHandler& operator=(const TcpHandler&) = delete;
    
    static TcpHandler& GetInstance();
    
    void InitSocket();
    void SendFrame(const std::vector<uchar>& frame);

private:
    TcpHandler() = default;
    ~TcpHandler() = default;
    static TcpHandler* sInstance;

    int mSockfd;
    int mClientSock;
    struct sockaddr_in mServerAddr;
    struct sockaddr_in mClientAddr;
    socklen_t mClientSockLen = sizeof(mClientAddr);
};

#endif