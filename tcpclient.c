/*

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{

	if(argc < 2)
	{

		printf("Usage: [%s] [Server] [Port]", argv[0]);
		return 0;

	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == 0)
	{

		fprintf(stderr, "[E]: %s\n", strerror(errno));
		return 2;

	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));

	int conn_status = connect(sockfd, (struct sockaddr*) &server_address, sizeof(server_address));
	if(conn_status != 0)
	{

		fprintf(stderr, "[E]: %s\n", strerror(errno));
		return 1;

	}

	char reply_buff[1024];
	recv(sockfd, &reply_buff, sizeof(reply_buff), 0);

	printf("%s", reply_buff);

	return 0;

}
