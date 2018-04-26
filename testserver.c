#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 2017
#define BUFF_SIZE 2048
#define ANSI_COLOR_CYAN "\x1b[36m"

int main (int argc, char **argv)
{
	printf(ANSI_COLOR_CYAN );
	/*Declare Variables*/
	struct sockaddr_in server_address;
	int server_socket;
	int bind_status;
	int received_bytes;
	unsigned char buffer[BUFF_SIZE];
	struct sockaddr_in client_address;
	int sent_bytes;
	socklen_t client_address_len = sizeof (client_address);

	/*Rest Body*/
	printf ("*The value of AF_INET is %d * \n *The value of SERVER_PORT is %d * \n *The address of computer is %d * \n", AF_INET,  SERVER_PORT , INADDR_ANY);

	/*Initialising sockaddr_in structure*/
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl (INADDR_ANY);
	memset (&(server_address.sin_zero),'\0',8);

	printf ("*Server Address details: * \n *1. Server Port: %hu * \n *2. Address: %u * \n *3: Family %hhu * \n", server_address.sin_port,server_address.sin_addr.s_addr,server_address.sin_family);
	
	/*Creating Socket*/
	server_socket = socket (AF_INET, SOCK_DGRAM, 0);

	if (server_socket < 0)
	{
		perror ("**Error in creating socket !!!**");
		return 0;
	}
	else
	{
		printf ("*Server Socketfd is created * \n");
	}

	/*Binding*/
	bind_status = bind (server_socket,(struct sockaddr *) &server_address, sizeof(server_address));

	if (bind_status < 0)
	{
		perror ("**Error in binding i.e. binding failed!!!**");
		return 0;
	}
	else
	{
		printf ("*Bind success*\n");
	}
	do{

		/*Receiving Data/Message from Client and Printing it on Console*/
		memset (buffer,0,BUFF_SIZE);

		printf ("*Waiting for receiving data on socket created* \n");
		received_bytes = recvfrom (server_socket, buffer, BUFF_SIZE, 0, (struct sockaddr *) &client_address, &(client_address_len));
		if (received_bytes < 0)
		{
			perror ("**Error in recvfrom!!!!**");
			return 0;
		}
		else
		{
			buffer[received_bytes] = 0;
			printf ("Client:  %s \n" , buffer );
		}

		/*Sending Data/Messsage to Client and Printing it on Console*/

		memset (buffer,0,BUFF_SIZE);
		//@@@@@HANGING this to input msg from server (from user)
		// sprintf (buffer,"Hi First Client, I am server !");
		printf("Your Reply:\t");
		gets(buffer);

		sent_bytes = sendto (server_socket, buffer, strlen(buffer), 0, (struct sockaddr *) &client_address, client_address_len);

		if (sent_bytes < 0)
		{
			perror ("Error in sendto !");
			return 0;
		}
		else
		{
			printf ("\t \t >Message Sent< \n ");
		}
	}while(1);
	
	close (server_socket);
}
