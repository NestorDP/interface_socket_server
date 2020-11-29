
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

    char buffer_out[BUFFER_LEN];   

    fprintf(stdout, "Server run!\n");

    strcpy(buffer_out, "\e[1;37mServer running!\e[0m\n\0");
    soc.net_send((uint8_t *) buffer_out, BUFFER_LEN, MSG_LEN);

    fprintf(stdout, "###################\n");

    return EXIT_SUCCESS;
}