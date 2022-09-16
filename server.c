// server //

#include<stdio.h>
#include<string.h>	// for strlen func.
#include<sys/socket.h>
#include<arpa/inet.h>	// for sockaddr_in, AF_INET func.
#include<unistd.h>	// for write function
#include<stdlib.h>

#define max 30
#define PORT 2100

int main(int argc , char *argv[])
{
	int sersoc , clisoc , conn , read_size;
	struct sockaddr_in servaddr , cliaddr;
	char str[max];
	servaddr.sin_family = AF_INET;          // Prepare the sockaddr_in structure
	servaddr.sin_port = htons( PORT );
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
    sersoc = socket(AF_INET , SOCK_STREAM , 0);
	if (sersoc == -1)               // Create socket
	{
		printf("Socket Error ! \n");
		exit(0);
	}
	printf("Socket Created ! \n");
	
	if( bind(sersoc,(struct sockaddr *)&servaddr , sizeof(servaddr)) < 0)  // Bind the server socket to a local address
	{
		perror("Bind Error ! \n");
		return 1;
	}
	printf("Bind Done ! \n");
	
	listen(sersoc , 10);   //Be ready to listen to client connections 
	
	printf("Server is waiting for new connections...\n");   // Accept and incoming connection
	conn = sizeof(struct sockaddr_in);
	
	
	clisoc = accept(sersoc, (struct sockaddr *)&cliaddr, (socklen_t*)&conn); // Accept connection from an incoming client
	if (clisoc < 0)
	{
		perror("Error on accept");
		return 1;
	}
	printf("A Client connected...\n");
	
	while( (read_size = recv(clisoc ,str ,max , 0)) > 0 )   // Receive a reply from the server
	{
		write(clisoc, str , strlen(str));   // Send the message back to client
	}
	
	if(read_size == 0)
	{
		printf("Client disconnected ! \n");
		fflush(stdout);
	}
	
	else if(read_size < 0)
	{
		printf("Failed ! \n");
	}
	
	return 0;
}