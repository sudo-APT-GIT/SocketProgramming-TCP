#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 50

main()
{
	int sockfd,newsockfd,retval,x;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	char bye[]="bye";
	char buff[MAXSIZE];
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1)
	{
		printf("\nSocket creation error");
		exit(0);
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Binding error");
		close(sockfd);
		exit(0);
	}

	retval=listen(sockfd,1);
	if(retval==-1)
	{
		close(sockfd);
		exit(0);
	}

	actuallen=sizeof(clientaddr);

	newsockfd=accept(sockfd,NULL,NULL);


	if(newsockfd==-1)
	{
		close(sockfd);
		exit(0);
	}

	while(1)
	{
		recedbytes=recv(newsockfd,buff,sizeof(buff),0);
		if(recedbytes==-1)
		{
			close(newsockfd);
			close(sockfd);
			exit(0);
			
		}
		printf("\nYou: ");	
		puts(buff);
		
		if(!strcmp(buff,"bye"))
		{
			break;
		}

		printf("\nMum: ");
		gets(buff);
		if(!strcmp(buff,"bye"))
		{
			sentbytes=send(newsockfd,buff,sizeof(buff),0);
			if(sentbytes==-1)
			{
				close(newsockfd);
				close(sockfd);
				exit(0);
			}
			break;
		}
		
		sentbytes=send(newsockfd,buff,sizeof(buff),0);
		if(sentbytes==-1)
		{
			close(newsockfd);
			close(sockfd);
			exit(0);
		}
		
	}
	close(newsockfd);
	close(sockfd);
}