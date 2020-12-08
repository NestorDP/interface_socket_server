
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>

#include "interface_socket_server/ethernet_interface.hpp"
#include "hps_0.h"

#define PORT 4242
#define MSG_LEN 2764800

// The start address and length of the Lightweight bridge
#define HPS_TO_FPGA_LW_BASE 0xFF200000
#define HPS_TO_FPGA_LW_SPAN 0x0020000

/*
 * Main execution of the server program of the simple protocol
 */
int main(int argc, char *argv[]) {
    char buffer_out[BUFFER_LEN];
    std::vector<uint8_t> dados_in(MSG_LEN);
    std::vector<uint8_t> dados_out(MSG_LEN);
    sock::EthernetInterface soc;

    void * lw_bridge_map = 0;
    uint32_t * dobro_map = 0;
    int devmem_fd = 0;

    // int valor = 0;
    // char valor_r[10];

    // Open up the /dev/mem device (aka, RAM)
    devmem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(devmem_fd < 0) {
        perror("devmem open");
        exit(EXIT_FAILURE);
    }

    // mmap() the entire address space of the Lightweight bridge so we can access our custom module 
    lw_bridge_map = (uint32_t*)mmap( NULL, HPS_TO_FPGA_LW_SPAN, PROT_READ|PROT_WRITE, MAP_SHARED, devmem_fd, HPS_TO_FPGA_LW_BASE ); 
    if(lw_bridge_map == MAP_FAILED) {
        perror("devmem mmap");
        close(devmem_fd);
        exit(EXIT_FAILURE);
    }

    // Set the dobro_map to the correct offset within the RAM
    dobro_map = (uint32_t*)(lw_bridge_map + DOBRO_0_BASE);

    soc.create_socket(PORT, TCP); 
    fprintf(stdout, "Server run!\n");
    strcpy(buffer_out, "\e[1;37mServer running!\e[0m\n\0");
    soc.net_send((uint8_t *) buffer_out, BUFFER_LEN, sizeof(buffer_out));

    while (1) {
        soc.net_recv(dados_in.data(), BUFFER_LEN, MSG_LEN);
        soc.net_send(dados_in.data(), BUFFER_LEN, MSG_LEN);
    }
    return EXIT_SUCCESS;
}