#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5555

int main()
{
	char *ip = "127.0.0.1";
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
	{
		printf("[-] Error in connection.\n");
		exit(1);
	}
	printf("[+] Client socket is created successfully.\n");
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	
	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
	{
		printf("[+] Error in connecting.\n");
		exit(1);
	}
	printf("[+] Connected to server.\n");
	
	while(1)
	{
		printf("Client : \t");
		scanf("%s",&buffer[0]);
		send(clientSocket, buffer, strlen(buffer), 0);
		
		if(strcmp(buffer, ":exit") == 0)
		{
			close(clientSocket);
			printf("Disconnected from server.\n");
			exit(1);
		}
		
		if(recv(clientSocket, buffer, 1024, 0) < 0)
		{
			printf("Error in receiving Data.\n");
		}else {
				printf("Server : \t%s\n",buffer);
		}
		
	}
	return 0;
}
		
		
		
		
		
		
