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
	char content[2000];	
};

struct httprequest me;
struct httpresponse respo,respon;

void getdate(char* field)
{
	FILE* fp;
	char cmd[10000];
	strcpy(cmd,"date");
	fp = popen(cmd,"r");
	fgets(field,180,fp);		
}


void getmodified(char* filename,char* field)
{
	FILE* fp;
	char cmd[10000];
	strcpy(cmd,"stat ");
	strcat(cmd,filename);
	strcat(cmd," -c %y");
	printf("%s",cmd);
	fp = popen(cmd,"r");
	fgets(field,100,fp);		
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

void handleget(char* filename)
{
	struct httprequest re;
	genreq(filename,&re);
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
	char mess[10000];
		//printf("%s\n%s\n%s\n",requ.type,requ.url,requ.connection);
		//printf("%s\n %d",mess,sizeof(requ));
		k = send(so,&re,sizeof(re),0);
		printf("%d\n",k);
		k = recv(so,&respon,sizeof(respo),0);
		if(strlen(respon.content) > 0)
		{
		char cpy[100] = "./tmp/";
		strcat(cpy,filename);
		FILE* fp = fopen(cpy,"w");
		fprintf(fp,"%s",respon.content);
		fclose(fp);
		}
}

	

void genresp(struct httprequest* req,struct httpresponse* resp)
{
	strcpy(resp->httpver,req->httpver);
	strcpy(resp->connection,req->connection);
	getdate(resp->date);
	strcpy(resp->contenttype,"text");
	strcpy(resp->server,"imdaredevil's server");
	//printf("%s",req->url + 1);
	char cpy[100] = "./tmp";
	strcat(cpy,req->url);
	int fd = open(cpy,0666);
	//printf("%d",fd);
	char filename[100];
	strcpy(filename,&(req->url)[1]);
	if(fd < 0)
	{
		char cmd[1000] = "touch ./tmp/ ";
		strcat(cmd,filename);
		//printf("%s ",cmd);
		system(cmd);	
		handleget(filename);
		fd = open(cpy,0666);
		read(fd,resp->content,1000);
		resp->status_code = 200;
		strcpy(resp->status,"OK");
		getmodified(&((req->url)[1]),resp->lastmodified);
	} 
	else
	{
		read(fd,resp->content,1000);
		resp->status_code = 200;
		strcpy(resp->status,"OK");
		getmodified(&((req->url)[1]),resp->lastmodified);
	}
	
}

int main()
{
printf("%lu",sizeof(respo));
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
do
{
	printf("%d",k);
	k = recv(newso,&me,330,0);
	printf("the url is \n %s \n",me.url + 1);
		genresp(&me,&respo);
		//printf("%s\n",respo.content);
		send(newso,&respo,sizeof(respo),0);
}while(strcmp(me.url,"bye") != 0);
close(so);
return 0;
}
