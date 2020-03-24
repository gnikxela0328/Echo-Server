//Client program
//Takes loopback address and port number as arguments 2 and 3 to connect to local 
//server
//
//Argument 1 is used as a username for authentication
//
//As per UNIX requirement arg0 is the program name
//
//Default port is 3000 if not specified in argument
//
//127.0.0.1 : 3000
//
//-------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

#define MAXLINE 4096 //Max buffer length
#define SERV_PORT 3000 //Default port number


int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXLINE];

	if (argc > 4 || argc <= 2) {
		perror("Incorrect number of parameters, please supply \n username, loopback, and optional port");
		exit(1);
	}

	char *username = argv[1]; //Stores username

	//-----Establish connection --------------------
	
	// Creation of socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Problem creating socket.");
		exit(2);
	}

	// Connection of socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[2]);

	if (argv[3] == NULL) 
		servaddr.sin_port = htons(SERV_PORT);
	else
		servaddr.sin_port = htons(atoi(argv[3]));

	// Initial connection test
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("Problem in establishing connection to server");
		exit(3);
	}

	//send(sockfd, username, strlen(username), 0); // Verifies username
	
	// Listening to user input
	while (fgets(sendline, MAXLINE, stdin) != NULL) {
		
		send(sockfd, sendline, strlen(sendline), 0);

		bzero(sendline, MAXLINE);

		if (recv(sockfd, recvline, MAXLINE, 0) == 0) {
			perror("The server terminated prematurely");
			exit(4);
		}

		printf("\nReceived from server: ");
		fputs(recvline, stdout);
		printf("\n");

		bzero(recvline, MAXLINE);
	}

	exit(0);
	
}


	

