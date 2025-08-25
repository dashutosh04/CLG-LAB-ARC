/*Write a program to create a udp socket through which the clinet will send a number to a server, server will check wheter the number is palindrome or not
and accordingly the server will send the reply to the client.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT 4952    
#define MAXBUFLEN 200      

int main() {
    int sockfd;
    struct sockaddr_in their_addr; 
    char buf[MAXBUFLEN];
    int numbytes;
    socklen_t addr_len;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(SERVERPORT);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    while (1) {
        printf("\nEnter a string to check ");
        
        
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break; 
        }
        buf[strcspn(buf, "\n")] = 0; 

        if ((numbytes = sendto(sockfd, buf, strlen(buf), 0,
                 (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
            perror("sendto");
            exit(1);
        }
        printf("Sent string '%s'...\n", buf);

        
        if (strcmp(buf, "exit") == 0) {
            printf("Exiting..\n");
            break;
        }


        addr_len = sizeof their_addr;
        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }

        buf[numbytes] = '\0';

        printf("Result: ");
        if (strcmp(buf, "1") == 0) {
            printf("palindrome.\n");
        } else if (strcmp(buf, "2") == 0) {
            printf("Not a palindrome.\n");
        } else {
            printf("Error: %s\n", buf);
        }
    }

    close(sockfd);
    return 0;
}
