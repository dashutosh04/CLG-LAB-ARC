#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(){
    int i, sockfd;

    int arr[10];
    int n = 10;
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(6002);

    i = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa) );
    if (i < 0) {
        printf("Connection failed.\n");
        return 1;
    }

    printf("Enter 10 numbers for the array:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Sending array to the server...\n");
    send(sockfd, arr, n * sizeof(int), 0);

    recv(sockfd, arr, n * sizeof(int), 0);

    printf("Sorted array received from server: ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    close(sockfd);
    return 0;
}
