#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>

#define backlog 5

struct  httprequest{
	char type[10];
	char url[100];
	char httpver[20];
	char host[100];
	char connection[100];
};

struct httpresponse{
	char httpver[20];
	int status_code;
	char status[100];
	char connection[100];
	char date[100];
	char server[100];
	char lastmodified[100];
	char contentlength[100];
	char contenttype[10];
	char content[10000];	
};

void printresp(struct httpresponse resp)
{
	printf("%s %d %s\n",resp.httpver,resp.status_code,resp.status);
	printf("Connection: %s\nDate: %s\nlast modified: %s\ncontenttype: %s\nserver: %s\n",resp.connection,resp.date,resp.lastmodified,resp.contenttype,resp.server);
	printf("**********************************************************\n");
	printf("%s\n",resp.content);
	printf("**********************************************************\n");
}
void genreq(char* filename,struct httprequest *req)
{
	strcpy(req->type,"GET");
	strcpy(req->url,"/");
	strcat(req->url,filename);
	strcpy(req->httpver,"HTTP/1.1");
	strcpy(req->host,"localhost:8081");
	strcpy(req->connection,"close");
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
my_addr.sin_port = htons(8082);
my_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
memset(&(my_addr.sin_zero),'\0',8);

int k = connect(so,(struct sockaddr*) &(my_addr),sizeof(struct sockaddr));
if(k >= 0)
printf("connected\n");
else
printf("error in connecting\n");
char dumm;
char mess[10000];
struct httprequest requ;
struct httpresponse resp;
do
{
	printf("Enter filename: \n");
		gets(mess);
		genreq(mess,&requ);
		//printf("%s\n%s\n%s\n",requ.type,requ.url,requ.connection);
		//printf("%s\n %d",mess,sizeof(requ));
		k = send(so,&requ,sizeof(requ),0);
		printf("%d\n",k);
	printf("Waiting for server response\n");
	k = recv(so,&resp,sizeof(resp),0);
	printf("the response is \n");
	printresp(resp);
}while(strcmp(requ.url,"bye") != 0);
close(so);
return 0;
}
