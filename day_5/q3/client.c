#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(){
    int i,sockfd,a,b,p=6,q=7,r;

    char buf[100];
    struct sockaddr_in sa;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    sa.sin_family=AF_INET;
    sa.sin_addr.s_addr=inet_addr("127.0.0.1");
    sa.sin_port=6001;

    i=connect(sockfd,(struct sockaddr *)&sa,sizeof(sa));

    printf("Enter a message to send to the server. \n");
    scanf("%s", buf);

    send(sockfd, buf, 100, 0);

    for(i=0; i < 100; i++) buf[i] = '\0';
    recv(sockfd, buf, 100, 0);
    printf("Message Recieved -%s\n", buf);

    close(sockfd);

    return 0;


}
