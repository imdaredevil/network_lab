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

int k = connect(so,(struct sockaddr*) &(my_addr),sizeof(struct sockaddr));
if(k >= 0)
printf("connected\n");
else
printf("error in connecting\n");
char message[20000],cmd[1000];
do
{
		printf("Enter command: ");
		gets(cmd);
		send(so,cmd,sizeof(cmd),0);
	if(strcmp(cmd,"bye") != 0)
	{
	printf("Waiting for server response\n");
	k = recv(so,message,sizeof(message),0);
		printf("the response is \n %s \n",message);
	}
}while(strcmp(cmd,"bye") != 0);
return 0;
}
