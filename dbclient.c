/****

TO RUN THE CODE:
1) Open two terminals and navigate to the folder where the this file is stored
2) On the first terminal run "$cc dbserver.c -o chats" (this terminal acts like a server)
3) On the second terminal run "$cc dbclient.c -o chatc" (this terminal acts like a client)
4) On the first terminal run "$./chats"
5) On the second terminal run "$./chatc"
6) Enter the port number (eg: 1234 or 3388) on the first terminal and enter the same
  port number on the second terminal.

PLEASE NOTE THAT THE CODE WILL NOT CREATE ANY NEW TXT FILES.
IT ONLY WORKS ON PREXISTING FILES IN THE FOLDER.

****/
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

struct Student
{
	int regno;
	char name[MAXSIZE];
	char course[MAXSIZE];
	char DOB[MAXSIZE];
};

int main()
{
	int sockfd, retval, recedbytes, sentbytes, x, count,size=4;
	char port[5], opt, buff[MAXSIZE];
	struct sockaddr_in serveraddr;
	struct Student records[100];

	printf("Enter the port number: ");
	gets(port);
	sscanf(port, "%d", &x); //converting string "port" to integer "x"

	/* create a socket */

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(x);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	/* connect to the server */

	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection //error");
		exit(0);
	}

	/* Run the options Menu */

	while(1)
	{
		printf("\nPlease enter your choice:\n");
		printf("1) Insert ( Format: \"1 regno name course dob\" )\n2) Search ( Format: \"2 regno\" )\n3) Delete ( Format: \"3 regno\") \n4) Display\n5) Exit\n\n");
		gets(buff);

		opt=buff[0]; //save the option number in "opt" variable

		sentbytes=send(sockfd,buff,sizeof(buff),0);
		if(sentbytes==-1)
		{
			printf("\nError while sending.Please try again!\n\n");
			close(sockfd);
			exit(0);
		}

		printf("\nChoice sent!\n\n"); 

		switch(opt)
		{
			case '1':

					/*Insert*/
					recedbytes = recv(sockfd, buff, sizeof(buff), 0);

					if(recedbytes == -1)
					{
						printf("\nRecieving failed\n");
						close(sockfd);
						exit(0);
					}
					if(buff[0]=='1')
					{
						size++;
						printf("\nValues inserted successfully! :D\n\n");
					}
					else
					{
						printf("\nValues already present:(\n\n");
					}
					break;
					
			case '2':
					/*search*/
					recedbytes=recv(sockfd,buff,sizeof(buff),0);

					if(recedbytes==-1)
					{
						printf("\nRecieving failed\n");
						close(sockfd);
						exit(0);
					}	

					if(buff[0]=='1')
					{
						printf("\nRECORD FOUND! :D\n\n");
					}
					else
					{
						printf("\nRECORD NOT FOUND! :(\n\n");
					}		
					break;

			case '3':
					/*delete*/
					recedbytes=recv(sockfd,buff,sizeof(buff),0);

					if(recedbytes==-1)
					{
						printf("\nRecieving failed\n");
						close(sockfd);
						exit(0);
					}
					if(buff[0]=='0')
					{
						printf("Record Not Found!:(\n");
					}
					else
					{
						size--;
						printf("Record deleted! :D\n");
					}
					
					break;
					
			case '4':
					/*display*/
					recedbytes=recv(sockfd,records,sizeof(records),0);

					if(recedbytes==-1)
					{
						printf("\nRecieving failed\n");
						close(sockfd);
						exit(0);
					}
					
					for (count = 0; count <=size; count++)
					{
						printf("\n--------------------------------------------------------------------------\n");
						printf("\nRECORD %d \n", count+1);
						printf("\nRegistration number: %d\n",records[count].regno);
						printf("\nName: ");
						puts(records[count].name);
						printf("\nCourse: ");
						puts(records[count].course);
						printf("\nDate of birth: ");
						puts(records[count].DOB);
					}
					printf("\nDone!\n");

					break;

			case '5':
					/*exit*/
					recedbytes=recv(sockfd,buff,sizeof(buff),0);

					if(recedbytes==-1)
					{
						printf("\nRecieving failed\n");
						close(sockfd);
						exit(0);
					}
					break;		

			default:
					printf("\nPlease enter valid options! \n");
					break;

		}//end of switch case

		if(strcmp(buff, "exit")==0)
		{
			break;
		}

	}//end of while(1)
	close(sockfd);
	printf("\nEnding..\n");
}//end of main