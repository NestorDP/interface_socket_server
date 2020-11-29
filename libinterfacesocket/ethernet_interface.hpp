/**
 * @ Copyright 2020
 */

#ifndef ETHERNET_INTERFACE_HPP
#define ETHERNET_INTERFACE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #include <ros/ros.h>

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUFFER_LEN 512
#define TCP 1
#define UDP 0


namespace sock {

class EthernetInterface{
  public:
    EthernetInterface();
    ~EthernetInterface();
    void create_socket(std::string ip_server, int port, bool protocol);
    int net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg);
    int net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg);

  private:
    struct sockaddr_in server;
    int port;
    int sockfd; 
    bool prtlc;     
};
}

#endif // ETHERNET_INTERFACE_HPP
