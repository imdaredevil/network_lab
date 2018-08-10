#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>

#define backlog 5

int main()
{
int so = socket(AF_INET,SOCK_STREAM,0);
printf("%d is socket descriptor\n",so);
if(so < 0)
{
	exit(1);
}
struct sockaddr_in my_addr,cl_addr;
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(8080);
my_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
memset(&(my_addr.sin_zero),'\0',8);

int k = bind(so,(struct sockaddr*) &(my_addr),sizeof(struct sockaddr));
if(k >= 0)
printf("binded\n");
else
printf("error\n");
listen(so,backlog);
printf("The server is listening at the port 8080\n");
int si = sizeof(struct sockaddr_in);
int newso = accept(so,(struct sockaddr*) &cl_addr,&si);
printf("%d is the socket descriptor of receiver\n",newso);
printf("Waiting for client message\n");
char message[10000];
	k = recv(newso,message,sizeof(message),0);
	printf("the message is \n %s \n",message);
		gets(message);
		send(newso,message,sizeof(message),0);
close(so);
return 0;
}
