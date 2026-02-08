#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    if(argc < 4){
        perror("Not enough parameteres passed. ");
        return 0;
        
    }
    int my_port = atoi(argv[1]);
    const char* peer_ip = argv[2];
    int peer_port = atoi(argv[3]);

    int sockfd;
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error: Socket Creation Failed\n");
        return 0;
    }

    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(my_port);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        perror("Error: Bind Failed\n");
        close(sockfd);
        return 0;
    }

    struct sockaddr_in peer_addr;
    memset(&peer_addr, 0, sizeof(peer_addr));

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(peer_port);

    if (inet_pton(AF_INET, peer_ip, &peer_addr.sin_addr) <= 0) {
        perror("Error: inet_pton failed.\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Chat program started.\n");
    printf("Listening on port %d. Sending to %s:%d.\n", my_port, peer_ip, peer_port);
    printf("Type your message and press Enter to send. Type 'exit' to quit.\n\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        char buffer[BUFFER_SIZE];
        struct sockaddr_in sender_addr;
        socklen_t len = sizeof(sender_addr);

        while (1) {
            int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                             (struct sockaddr *)&sender_addr, &len);
            if (n < 0) {
                continue;
            }
            buffer[n] = '\0';

            char sender_ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sender_addr.sin_addr, sender_ip_str, INET_ADDRSTRLEN);

            printf("\rPeer (%s): %s\nYou: ", sender_ip_str, buffer);
            fflush(stdout);

            if (strncmp(buffer, "exit", 4) == 0) {
                printf("\n'exit' received. Shutting down...\n");
                kill(getppid(), SIGTERM);
                break;
            }
        }
        close(sockfd);
        exit(EXIT_SUCCESS);
    }
    else {
        char buffer[BUFFER_SIZE];
        while (1) {
            printf("You: ");
            fflush(stdout);

            if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
                strcpy(buffer, "exit");
            }
            
            buffer[strcspn(buffer, "\n")] = 0;

            sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&peer_addr, sizeof(peer_addr));

            if (strncmp(buffer, "exit", 4) == 0) {
                printf("You sent 'exit'. Shutting down...\n");
                kill(pid, SIGTERM);
                break;
            }
        }
        close(sockfd);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
