/*
** A simple UDP request-response "server"
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4952   
#define MAXBUFLEN 200 

int main() {
    int sockfd;
    struct sockaddr_in my_addr;    
    struct sockaddr_in their_addr; 
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFLEN];


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    \
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

        printf("Client: \"%s\"\n", buf);


        if (strcmp(buf, "exit") == 0) {
            printf("Exited... \n");
            break;
        }

        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break; 
        }
        buf[strcspn(buf, "\n")] = 0; 

        if ((numbytes = sendto(sockfd, buf, strlen(buf), 0,
             (struct sockaddr *)&their_addr, addr_len)) == -1) {
            perror("sendto");
            exit(1);
        }
        printf("Reply sent.\n");

        if (strcmp(buf, "exit") == 0) {
            printf("Exiting..\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
