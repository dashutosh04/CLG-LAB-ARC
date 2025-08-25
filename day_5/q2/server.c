#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int sockfd, fd1, length, i, x, y, temp;
    int arr[10];
    int n = 10;
    struct sockaddr_in sa, ta1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(6002);

    i = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    printf("test %d%d\n", sockfd, i);

    listen(sockfd, 5);

    length = sizeof(sa);
    printf("Waiting for a client to connect...\n");
    fd1 = accept(sockfd, (struct sockaddr *) &ta1, &length);
    printf("Client connected.\n");

    printf("Waiting for an array from the client.\n");
    recv(fd1, arr, n * sizeof(int), 0);

    printf("Array received from client: ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Sorting the array...\n");
    for (x = 0; x < n - 1; x++) {
        for (y = 0; y < n - x - 1; y++) {
            if (arr[y] > arr[y + 1]) {
                temp = arr[y];
                arr[y] = arr[y + 1];
                arr[y + 1] = temp;
            }
        }
    }

    printf("Sending sorted array back to client: ");
     for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    send(fd1, arr, n * sizeof(int), 0);

    close(fd1);
    close(sockfd);
    return 0;
}
