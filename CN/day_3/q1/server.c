
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4952    // The port users will be connecting to
#define MAXBUFLEN 200  // Max buffer size

struct dns {
    char domain[100];
    char ip[20];
};

struct dns dns_table[] = {
    {"google.com", "142.250.196.14"},
    {"facebook.com", "157.240.22.35"},
    {"github.com", "140.82.121.4"}
};
const int num_entries = 3;

const char* find_ip(const char* domain) {
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(domain, dns_table[i].domain) == 0) {
            return dns_table[i].ip;
        }
    }
    return "Not Found";
}

int main() {
    int sockfd;
    struct sockaddr_in my_addr;   
    struct sockaddr_in their_addr; 

    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFLEN];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Set up my address structure
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY; 

    // Bind the socket to the port
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
        perror("bind");
        exit(1);
    }

    while (1) {
        addr_len = sizeof their_addr;

        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }

        buf[numbytes] = '\0';

        printf("Received request from %s\n", inet_ntoa(their_addr.sin_addr));
        printf("Requested domain: \"%s\"\n", buf);

        if (strcmp(buf, "exit") == 0) {
            printf("Exiting..\n");
            break; 
        }

        const char* ip = find_ip(buf);
        printf("Sending response: \"%s\"\n", ip);

        if ((numbytes = sendto(sockfd, ip, strlen(ip), 0,
             (struct sockaddr *)&their_addr, addr_len)) == -1) {
            perror("sendto");
            exit(1);
        }
    }

    close(sockfd);
    return 0;
}
