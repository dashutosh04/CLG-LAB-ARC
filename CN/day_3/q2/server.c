
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4952  
#define MAXBUFLEN 200 

const char* check_palindrome(const char* str) {
    int left = 0;
    int right = strlen(str) - 1;

    if (right < 0) return "2";

    while (right > left) {
        if (str[left++] != str[right--]) {
            return "2";
        }
    }
    return "1"; }


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
        printf("Received: \"%s\"\n", buf);

        if (strcmp(buf, "exit") == 0) {
            printf("Exiting..\n");
            break; 
        }

     
        const char* response = check_palindrome(buf);
        printf("Sending response: \"%s\"\n", response);

    
        if ((numbytes = sendto(sockfd, response, strlen(response), 0,
             (struct sockaddr *)&their_addr, addr_len)) == -1) {
            perror("sendto");
            exit(1);
        }
    }

    close(sockfd);
    return 0;
}
