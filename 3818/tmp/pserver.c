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
	strcat(req->url,filen