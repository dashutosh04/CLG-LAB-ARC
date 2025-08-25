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

    int sockfd,fd1,fd2, length,i;
    char buf[100]; 
    struct sockaddr_in sa,ta1;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    sa.sin_family=AF_INET;
    sa.sin_addr.s_addr=INADDR_ANY;
    sa.sin_port=htons(8085);

    i=bind(sockfd,(struct sockaddr *)&sa,sizeof(sa));
    printf("test %d %d\n",sockfd,i);

    listen(sockfd,5);

    length=sizeof(sa);

    printf("Waiting for client 1 to connect...\n");
    fd1=accept(sockfd, (struct sockaddr *) &ta1,&length);
    printf("Client 1 connected.\n");

    printf("Waiting for client 2 to connect...\n");
    fd2=accept(sockfd, (struct sockaddr *) &ta1,&length);
    printf("Client 2 connected.\n Server is ready..\n");


    for(i=0; i < 100; i++) buf[i] = '\0';
    recv(fd1, buf, 100, 0);
    printf("Number received from Client 1: %s\n", buf);
    send(fd2, buf, 100, 0);
    printf("Forwarded number to Client 2.\n");


    for(i=0; i < 100; i++) buf[i] = '\0';
    recv(fd2, buf, 100, 0);
    printf("Number received from Client 2: %s\n", buf);
    send(fd1, buf, 100, 0);
    printf("Forwarded number back to Client 1.\n");


    close(fd1);
    close(fd2);
    close(sockfd);
    return 0;
}
