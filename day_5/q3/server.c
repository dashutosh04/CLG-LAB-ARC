
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
int sockfd,fd1, length,i,x,y,sum;
char buf[100],p[3]; /* We will use this buffer for communication */
struct sockaddr_in sa,ta1;


sockfd=socket(AF_INET,SOCK_STREAM,0);

sa.sin_family=AF_INET;
sa.sin_addr.s_addr=INADDR_ANY;
sa.sin_port=6001;

i=bind(sockfd,(struct sockaddr *)&sa,sizeof(sa));
printf("test %d%d\n",sockfd,i);

listen(sockfd,5);


length=sizeof(sa);
fd1=accept(sockfd, (struct sockaddr *) &ta1,&length);


printf("Waitig for a message from the client.\n");

for(i=0; i < 100; i++) buf[i] = '\0';
recv(fd1, buf, 100, 0);
printf("%s\n", buf);

send(fd1, buf, 100, 0);

close(fd1);


 }
