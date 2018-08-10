#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

#define backlog 5

void rev(char* str)
{
	int n = strlen(str),i;
	for(i=0;i<n/2;i++)
	{
		char temp = str[i];
		str[i] = str[n-i-1];
		str[n-i-1] = temp;
	}
}  

void handleconnect(int newso)
{
	int k;
	char str[10000];
	printf("%d is the socket descriptor of client\n",newso);
	printf("Server is receiving message\n");
	do
	{
		k = recv(newso,str,sizeof(str),0);
		if(strcmp(str,"bye") != 0)
			rev(str);
		k = send(newso,str,sizeof(str),0);
	}while(strcmp(str,"bye") != 0);
	close(newso);
}

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
do
{
	
	int newso = accept(so,(struct sockaddr*) &cl_addr,&si);
	int p = fork();
	if(p == 0)
	{
		k = 1;
		handleconnect(newso);
	}
	else if(p > 0)
	{
		printf("Press 1 to continue: ");
		scanf("%d",&k);
	}
	else
	{
		printf("error in concurrency\n");
		exit(1);
	}
}while(k == 1);
return 0;
}
