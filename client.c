// client //

#include <stdio.h>	
#include <string.h> 	// for strlen func.
#include <sys/socket.h>	// socket
#include <arpa/inet.h>	// for sockaddr_in, AF_INET func.
#include <unistd.h>   // for write, read, close functions
#include<stdlib.h>

#define CLI_PORT 2100
#define BUFF_SIZE 30

int main(int argc , char *argv[])
{
    printf ("Client Starting...\n");
    
	int clisoc;
	int re;
	struct sockaddr_in servaddr;
	char recbuff[BUFF_SIZE];
	char message[1000];
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons( CLI_PORT );                  // Prepare the sockaddr_in structure
	servaddr.sin_addr.s_addr = inet_addr ("127.0.0.1");      // Server will start a server on localhost (127.0.0.1) port 8888
	bzero(&servaddr, sizeof(servaddr));
	
    clisoc = socket(AF_INET , SOCK_STREAM , 0);
	if (clisoc == -1)          // Create socket
	{
		printf("Socket Errror ! \n");
		exit(0);
	}
	printf("Socket created, connecting to server\n");
	
	if (connect(clisoc , (struct sockaddr *)&servaddr , sizeof(servaddr)) < 0)     // Connect to remote server
	{
		perror("Connect Error ! \n");
		return 1;
	}
	printf("Connected to server, reading from socket\n");
	
	
	int count=0;  // for information how many client
	while(1)              // keep communicating with server
	{
		printf("message to be echo : ");
		scanf("%s" , message);

		if( send(clisoc , message , strlen(message) , 0) < 0)     // Send data
		{
			printf("Send Failed ! \n");
			exit(0);
		}
		
		if((re=(read(clisoc,recbuff,sizeof(recbuff))))<0)  // Receive a reply from the server
		{
			printf("Read Error ! \n");
			break;
		}
		printf("- ");
		puts(recbuff);
		count++;
		
	}
	printf("you are %d . client",count);
	
	close(clisoc);      // Close the socket and exit 
	return 0;
}