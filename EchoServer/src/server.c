#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096    //Max line length
#define SERV_PORT 3000  //Default port
#define LISTENQ 8       //Maximum number of clients

int main (int argc, char **argv) {
	int listenfd, connfd, n;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;

	//Parameter checker
	if (argc < 2 || argc > 3) {
		perror("Invalid Parameters, please provide username and optional port number.");
		exit(1);
	}

	//Username verification
	char *username = argv[1];	

	//Creation of socket
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Problem in creating socket.");
		exit(2);
	}


	//Assignment of socket attributes
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (argv[2] == NULL)
		servaddr.sin_port = htons(SERV_PORT);
	else
		servaddr.sin_port = htons(atoi(argv[2]));

	//Binding of socket
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	//Create a connection queue
	listen(listenfd, LISTENQ);

	printf("Server running... waiting for connections.\n");

	for ( ; ; ) {

		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		printf("Received request...");

		while ((n = recv(connfd, buf, MAXLINE, 0)) > 0) {
			printf("String recieved and resent to the client: ");
			puts(buf);
			send(connfd, buf, n, 0);
			bzero(buf, MAXLINE);
		}

		if (n < 0) {
			perror("Read error");
			exit(1);
		}

		close(connfd);

	}

	close(listenfd);

}


