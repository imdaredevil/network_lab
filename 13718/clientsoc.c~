#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>

#define backlog 5

struct message{
	char mess[1000];
	int len;
};


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
char dumm;
struct message me;
do
{
	printf("Enter message: \n");
		gets(me.mess);
		printf("Enter id: \n");
		scanf("%d",&(me.len));
		send(so,&me,sizeof(me),0);
	if(strcmp(me.mess,"bye") != 0)
	{
	printf("Waiting for server response\n");
	k = recv(so,&me,sizeof(me),0);
		printf("the response is \n %s \n id is %d\n",me.mess,me.len);
	}
scanf("%c",&dumm);
}while(strcmp(me.mess,"bye") != 0);
close(so);
return 0;
}
