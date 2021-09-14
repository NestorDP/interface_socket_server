/**
 * @ Copyright 2020
 */

#ifndef INCLUDE_INTERFACE_SOCKET_SERVER_ETHERNET_INTERFACE_HPP_
#define INCLUDE_INTERFACE_SOCKET_SERVER_ETHERNET_INTERFACE_HPP_

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
    void create_socket(int port, bool protocol);
    int net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg);
    int net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg);

 private:
    struct sockaddr_in remote_addr;
    struct sockaddr_in local_addr;
    int port;
    int localfd = 1;
    int remotefd = 1;
    bool prtlc;
};
}  // namespace sock

#endif  // INCLUDE_INTERFACE_SOCKET_SERVER_ETHERNET_INTERFACE_HPP_
