/****

	TO RUN THE CODE:
	1) Open two terminals and navigate to the folder where the this file is stored
	2) On the first terminal run "$cc sermenudriven.c -o chats" (this terminal acts like a server)
	3) On the second terminal run "$cc clmenudriven.c -o chatc" (this terminal acts like a client)
	4) On the first terminal run "$./chats"
	5) On the second terminal run "$./chatc"
	6) Enter the port number (eg: 1234 or 3388) on the first terminal
	   and enter the same port number on the second terminal.
	NOTE: files which you want to work on must have only one word in one line. The code doesn't work
	for a sentence in a line.


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

int main()
{
	int sockfd, retval, recedbytes, sentbytes, x;
	char port[5], opt, buff[MAXSIZE];
	struct sockaddr_in serveraddr;
	
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

		/***
			send the name of the file ( which is already created and is in the same 
			folder as this code) 
		***/

		printf("\nPlease enter the file name: ");
		gets(buff);
		
		sentbytes=send(sockfd,buff,sizeof(buff),0);
		if(sentbytes==-1)
		{
			printf("\nSending error\n");
			close(sockfd);
			exit(0);
		}
		
		/* display the result (file exists or not) */
		
		recedbytes=recv(sockfd,buff,sizeof(buff),0);

		if(recedbytes==-1)
		{
			printf("\nRecieving failed\n");
			close(sockfd);
			exit(0);
		}

		if(buff[0]=='1')
		{
			printf("\nFile found!(^o^)\n\n");
		}
		else
		{
			printf("\nError 404: File not found! ¯\\_(ツ)_/¯\n\nPlease enter valid file names.\n");
			break;
		}

		/***
			send the choice (1,2,3,4) 
			1) Search - Please enter 1 followed by a space followed by the string that you want to search
				eg: "1 mango"
			2) Replace - Please enter 2 followed by a space followed by the string to be replaced 
				followed by a space followed by the replacement string
				eg: "2 mango banana" => replace mango with banana
			3) Reorder - The results after reordering will be saved in "aftreorder.txt" 
			4) Exit - just the enter number 4

		***/

		printf("Please enter your choice:\n");
		printf("1) Search ( Format: \"1 string_you_want_to_search\" )\n2) Replace ( Format: \"2 old_word new_word\" \n3) Reorder\n4) Exit\n\n");
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
		
		recedbytes=recv(sockfd,buff,sizeof(buff),0);

		if(recedbytes==-1)
		{
			printf("\nRecieving failed\n");
			close(sockfd);
			exit(0);
		}

		/* if option 4 is chosen (exit) */

		if(strcmp(buff, "exit")==0){
			break;
		}
		
		/* the code below can be implemented using switch cases too */

		/* if option 1 is chosen (search) */

		if(opt=='1')
		{
			if(buff[0]=='1')
			{
				printf("\nWORD FOUND! (^o^) \n\n");
			}
			else
			{
				printf("\nWORD NOT FOUND! （>﹏<）\n\n");
			}
		}

		/* if option 2 is chosen (replace) */

		if(opt == '2')
		{
			if(buff[0]=='1')
			{
				printf("\nWORD REPLACED! (^o^) \n\n");
			}
			else
			{
				printf("\nWORD NOT REPLACED! （>﹏<）\n\n");
			}		
		}

		/* if option 3 is chosen(reorder) */

		if(opt=='3')
		{
			if(buff[0]=='1')
			{
				printf("\nResults successfully saved!\n\n");
			}
			else
			{
				printf("\nThere was a problem while saving the results.（>﹏<）\nPlease try again!\n");
			}
		}

	} // end of while(1)

	close(sockfd); // close the connection using the socket descriptor
}