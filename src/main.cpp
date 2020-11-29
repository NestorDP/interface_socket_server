
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "ethernet_interface.hpp"

#define PORT 4242

// #define BUFFER_LEN 512
#define MSG_LEN 2764800

/*
 * Main execution of the server program of the simple protocol
 */
int main(int argc, char *argv[]) {

    std::vector<uint8_t> dados_in(MSG_LEN);
    std::vector<uint8_t> dados_out(MSG_LEN);

    sock::EthernetInterface soc;
    soc.create_socket(PORT, TCP);

    // struct sockaddr_in client, server;
    // int serverfd;
    // int clientfd;
    char buffer_out[BUFFER_LEN];
    // char buffer_in[MSG_LEN];
    // unsigned int n_bytes = 0;
    // unsigned int n_bytes_acc = 0;

    // serverfd = socket(AF_INET,  SOCK_STREAM, 0);
    // // serverfd = socket(AF_INET,  SOCK_DGRAM, 0);
    // if(serverfd == -1) {
    //     perror("Can't create the server socket:");
    //     return EXIT_FAILURE;
    // }
    // fprintf(stdout, "Server socket created with fd: %d\n", serverfd);

    // server.sin_family = AF_INET;
    // server.sin_port = htons(PORT);
    // server.sin_addr.s_addr = htonl(INADDR_ANY);
    // memset(server.sin_zero, 0x0, 8);

    // int yes = 1;
    // if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR,
    //               &yes, sizeof(int)) == -1) {
    //     perror("Socket options error:");
    //     return EXIT_FAILURE;
    // }

    // if(bind(serverfd, (struct sockaddr *)&server, sizeof(server)) == -1 ) {
    //     perror("Socket bind error:");
    //     return EXIT_FAILURE;
    // }

    // if(listen(serverfd, 2) == -1) {
    //     perror("Listen error:");
    //     return EXIT_FAILURE;
    // }
    // fprintf(stdout, "Listening on port %d\n", PORT);

    // socklen_t client_len = sizeof(client);
    // if ((clientfd=accept(serverfd,
    //     (struct sockaddr *) &client, &client_len )) == -1) {
    //     perror("Accept error:");
    //     return EXIT_FAILURE;
    // }    

    fprintf(stdout, "Server run!\n");

    strcpy(buffer_out, "\e[1;37mServer running!\e[0m\n\0");
    soc.net_send((uint8_t *) buffer_out, BUFFER_LEN, MSG_LEN);

    fprintf(stdout, "###################\n");

    // unsigned int len = sizeof(client);
    // recvfrom(serverfd, buffer_in, BUFFER_LEN, 0,(struct sockaddr *) &client, &len);
    // printf("\n %s", buffer_in);

    // if (send(clientfd, buffer_out, BUFFER_LEN, 0)) {
    //     fprintf(stdout, "Client connected.\nWaiting for client message ...\n");
    //     while (1){ 
    //         for(int i = 0; i < MSG_LEN; i = i + BUFFER_LEN){
    //             n_bytes_acc = n_bytes_acc + recv(clientfd, buffer_in + i, BUFFER_LEN, 0);
    //             // n_bytes_acc = n_bytes_acc + recvfrom(serverfd, buffer_in + i, BUFFER_LEN, 0,
    //             //                                 (struct sockaddr *) &client, &len);            
    //         }

    //         for(int i = 0; i < MSG_LEN; i = i + BUFFER_LEN){
    //             n_bytes_acc = n_bytes_acc + send(clientfd, buffer_in + i, BUFFER_LEN, 0);
    //             // sendto(serverfd, buffer_in + i , BUFFER_LEN, 0, 
    //             //     (const struct sockaddr *) &client, sizeof(client));          
    //         }
    //     }
    // }

    // /* Client connection Close */
    // close(clientfd);

    // /* Close the local socket */
    // close(serverfd);

    // printf("\nConnection closed\n\n");

    return EXIT_SUCCESS;
}