
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/* Server port  */
#define PORT 4242


/* Buffer length */
#define BUFFER_LEN 1024
#define MSG_LEN 2764800

/*
 * Main execution of the server program of the simple protocol
 */
int main(void) {

    struct sockaddr_in client, server;
    int serverfd, clientfd;
    char buffer_out[BUFFER_LEN];

    char buffer_in[MSG_LEN];
    unsigned int n_bytes = 0, n_bytes_acc = 0;

    fprintf(stdout, "Starting server\n");

    serverfd = socket(AF_INET,  SOCK_STREAM, 0);
    if(serverfd == -1) {
        perror("Can't create the server socket:");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Server socket created with fd: %d\n", serverfd);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    memset(server.sin_zero, 0x0, 8);

    int yes = 1;
    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR,
                  &yes, sizeof(int)) == -1) {
        perror("Socket options error:");
        return EXIT_FAILURE;
    }

    if(bind(serverfd, (struct sockaddr *)&server, sizeof(server)) == -1 ) {
        perror("Socket bind error:");
        return EXIT_FAILURE;
    }

    if(listen(serverfd, 2) == -1) {
        perror("Listen error:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Listening on port %d\n", PORT);

    socklen_t client_len = sizeof(client);
    if ((clientfd=accept(serverfd,
        (struct sockaddr *) &client, &client_len )) == -1) {
        perror("Accept error:");
        return EXIT_FAILURE;
    }

    strcpy(buffer_out, "\e[1;37mServer running!\e[0m\n\0");

    if (send(clientfd, buffer_out, BUFFER_LEN, 0)) {
        fprintf(stdout, "Client connected.\nWaiting for client message ...\n");
        while (1){ 
            for(int i = 0; i < MSG_LEN; i = i + BUFFER_LEN){
                n_bytes_acc = n_bytes_acc + recv(clientfd, buffer_in + i, BUFFER_LEN, 0);            
            }

            for(int i = 0; i < MSG_LEN; i = i + BUFFER_LEN){
                n_bytes_acc = n_bytes_acc + send(clientfd, buffer_in + i, BUFFER_LEN, 0);             
            }
        }
    }

    /* Client connection Close */
    close(clientfd);

    /* Close the local socket */
    close(serverfd);

    printf("\nConnection closed\n\n");

    return EXIT_SUCCESS;
}