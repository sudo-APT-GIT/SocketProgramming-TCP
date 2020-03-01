#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXSIZE 50

main()
{
	int sockfd,retval;
	int recedbytes,sentbytes,x,i;
	struct sockaddr_in serveraddr;
	char buff[MAXSIZE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection //error");
		exit(0);
	}

	while(1)
	{

		printf("\nYou: ");
		gets(buff);
		
		if(!strcmp(buff,"bye"))
		{
			sentbytes=send(sockfd,buff,sizeof(buff),0);
			if(sentbytes==-1)
			{
				printf("!!");
				close(sockfd);
				exit(0);
			}
			break;
		}
		sentbytes=send(sockfd,buff,sizeof(buff),0);
		if(sentbytes==-1)
		{
			printf("!!");
			close(sockfd);
			exit(0);
		}

		recedbytes=recv(sockfd,buff,sizeof(buff),0);
		if(recedbytes==-1)
		{
			printf("Recieving failed\n");
			close(sockfd);
			exit(0);
		}
		i=0;
		while(buff[i]!='\0')
		{
			if(buff[i]<=90 && buff[i]>=65)
			buff[i]=buff[i]+32;
			else
				buff[i]=buff[i]-32;
			i++;
		}
		printf("\nMum: ");
		puts(buff);
		if(!strcmp(buff,"bye"))
		{
			break;		
		}
	}
	close(sockfd);
}