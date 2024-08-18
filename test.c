#include "framebuffer.h"
#include "unistd.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

#include "graphics.h"

void print_ip_addresses() {
    struct ifaddrs *ifaddr, *ifa;
    char addr[INET_ADDRSTRLEN];

    // Get the list of network interfaces
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    // Iterate over the interfaces
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        // Check if the interface is an IPv4 address
        if (ifa->ifa_addr->sa_family == AF_INET) {
            // Convert the IP address to a string
            if (inet_ntop(AF_INET, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, addr, sizeof(addr)) != NULL) {
                printf("%s:%s\n", ifa->ifa_name, addr);
                char msg[16];
                sprintf(msg, "%s:%s", ifa->ifa_name, addr);
                display.print(msg);
            } else {
                perror("inet_ntop");
            }
        }
    }

    freeifaddrs(ifaddr);
}

void main() {
  framebuffer.constructor();
  display.clear_screen();
  print_ip_addresses();
  while(1);
}