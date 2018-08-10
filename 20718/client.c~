#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>

#define backlog 5

int main()
{
int so = socket(AF_INET,SOCK_STREAM,0);
printf("%d is socket descriptor\n",so);
if(so < 0)
{
	exit(1);
}
struct sockaddr_in my_addr;
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(8080);
my_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
memset(&(my_addr.sin_zero),'\0',8);

int k = connect(so,(struct sockaddr*) &(my_addr),sizeof(struct sockaddr));
if(k >= 0)
printf("connected\n with socket descriptor %d\n",so);
else
{
printf("error in connecting\n");
exit(1);
}
char str[10000];
do
{
	printf("Enter message: ");
	gets(str);
	k = send(so,str,sizeof(str),0);
	k = recv(so,str,sizeof(str),0);
	printf("The response is %s\n",str);	
}while(strcmp(str,"bye") != 0);
return 0;
}
