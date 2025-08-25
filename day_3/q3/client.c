/*
** A simple UDP request-response "client"
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

#define SERVERPORT 4952    
#define MAXBUFLEN 200      
int main() {
    int sockfd;
    struct sockaddr_in their_addr;
    char buf[MAXBUFLEN];
    int numbytes;

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(SERVERPORT);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    while (1) {
    
        printf("\nYou:  ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break; 
        }
        buf[strcspn(buf, "\n")] = 0; 
   
        if ((numbytes = sendto(sockfd, buf, strlen(buf), 0,
                 (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
            perror("sendto");
            exit(1);
        }
        printf("Message sent....\n");

        if (strcmp(buf, "exit") == 0) {
            printf("Exiting..\n");
            break;
        }

        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, NULL, NULL)) == -1) {
            perror("recvfrom");
            exit(1);
        }
        buf[numbytes] = '\0';

        printf("Server: \"%s\"\n", buf);

        if (strcmp(buf, "exit") == 0) {
            printf("Exited.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
