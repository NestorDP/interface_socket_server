/**
 * @ Copyright 2020
 */


#include "ethernet_interface.hpp" 

sock::EthernetInterface::EthernetInterface () {
    fprintf(stdout, "Starting Client ...\n");
}

sock::EthernetInterface::~EthernetInterface (){
    close(this->sockfd);
}

void sock::EthernetInterface::create_socket(std::string ip_server, int port, bool protocol){
 
    this->prtlc = protocol; 

    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(port);
    this->server.sin_addr.s_addr = inet_addr(ip_server.c_str());
    memset(this->server.sin_zero, 0x0, 8);

    if(this->prtlc){
        if ((this->sockfd = socket(AF_INET,  SOCK_STREAM, 0)) == -1) {
            perror("\e[1;31mError on client socket creation:");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Client socket created with fd: %d\n", this->sockfd);
        
        if (connect(this->sockfd, (struct sockaddr*) &this->server, sizeof(this->server)) == -1) {
            perror("\e[1;31mCan't connect to server");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Connection established with the server\n");
    }
    else{
        if ((this->sockfd = socket(AF_INET,  SOCK_DGRAM, 0)) == -1) {
            perror("\e[1;31mError on client socket creation:");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Client socket created with fd: %d\n", this->sockfd);
    }
    return;
}

int sock::EthernetInterface::net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;

    if (this->prtlc){
        for (size_t i = 0; i < len_msg; i = i + len_buffer){
            num = num + send(this->sockfd, msg + i , len_buffer, 0);
        }
    }
    else{
        for (size_t i = 0; i < len_msg; i = i + len_buffer){
            num = num + sendto(sockfd, msg + i , len_buffer, 0, 
            (const struct sockaddr *) &this->server, sizeof(server));
        }
    }
    
    return num;  
}

int sock::EthernetInterface::net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;
    unsigned int len;

    if (this->prtlc) {
        for(int i = 0; i < len_msg; i = i + len_buffer) {
            num = num + recv(this->sockfd, msg + i, len_buffer, 0);
        }
    }
    else {
        for(int i = 0; i < len_msg; i = i + len_buffer) {
            num = num + recvfrom(sockfd, msg + i, len_buffer, 0,
            (struct sockaddr *) &this->server, &len);
        }
    }

    return num;
}
