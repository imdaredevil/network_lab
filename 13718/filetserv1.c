#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>


#define backlog 5

int main()
{
int so = socket(AF_INET,SOCK_STREAM,0);
FILE* fp;
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
char message[1000];
char response[20000];
do
{
	printf("!\n");
	k = recv(newso,message,sizeof(message),0);
	if(strcmp(message,"bye") != 0)
	{
	if(strcmp(message,"list") == 0)
		{
			fp = popen("ls *","r");	
			strcpy(response,"");
			char mess[200];
			while(!feof(fp))
			{
				fgets(mess,180,fp);
				strcat(response,"*");
				strcat(response,mess);
			}			
			send(newso,response,sizeof(response),0);
		}
		else
		{
			printf("%s\n",message);
			int fd = open(message,0666);
			strcpy(response,"");
				read(fd,response,20000);
				//printf("%s",mess);						
			send(newso,response,sizeof(response),0);
		}
	}
}while(strcmp(message,"bye") != 0);
close(so);
return 0;
}
