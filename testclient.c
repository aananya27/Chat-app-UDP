#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 2017
#define BUFF_SIZE 2048
#define ANSI_COLOR_MAGENTA "\x1b[35m"



int main (int argc, char **argv)
{
	printf(ANSI_COLOR_MAGENTA);
	/*Declare Variables*/
	struct sockaddr_in client_address;
	int client_socket;
	int bind_status;
	struct sockaddr_in server_address;
	unsigned char buffer[BUFF_SIZE];
	int sent_bytes;
	socklen_t server_address_len = sizeof (server_address);
	int received_bytes;
	
	/*Rest Body*/

	/*Initialising sockaddr_in structure*/
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(0);
	client_address.sin_addr.s_addr = htonl (INADDR_ANY);
	memset (&(client_address.sin_zero),'\0',8);

	/*Creating Socket*/
	client_socket = socket (AF_INET, SOCK_DGRAM, 0);

	if (client_socket < 0)
	{
		perror ("**Error in creating socket !!!!**");
		return 0;

	}
	else
	{
		printf ("*Client Socket is created* \n");
	}

	/*Binding*/
	bind_status = bind (client_socket,(struct sockaddr *) &client_address, sizeof(client_address));

	if (bind_status < 0)
	{
		perror ("**Error in binding i.e. binding failed!!!**");
		return 0;
	}
	else
	{
		printf ("* Bind success ! *\n");
	}

	/*Setting up the sockaddr_in for server with whom client will communicate */
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl (INADDR_ANY);
	//inet_aton("127.0.0.1",&server_address.sin_addr);
	memset (&(server_address.sin_zero),'\0',8);
	do{
		/*Sending Data/Messsage to Server and Printing it on Console*/

		printf("Send a Message: \t ");
		memset (buffer,0,BUFF_SIZE);
		//@@@@@Changing this for input from user
		// sprintf (buffer,"Hi I am First Client !");
		gets(buffer);

		sent_bytes = sendto (client_socket, buffer, strlen(buffer), 0, (struct sockaddr *) &server_address, server_address_len);

		if (sent_bytes < 0)
		{
			perror ("**Error in sentto from client to server!!!**");
			return 0;
		}
		else
		{
			printf ("\t \t >Message Sent< \n ");
		}

		/*Receiving Data/Message from Server and Printing it on Console*/
		memset (buffer,0,BUFF_SIZE);

		received_bytes = recvfrom (client_socket, buffer, BUFF_SIZE, 0, (struct sockaddr *) &server_address, &(server_address_len));
		if (received_bytes < 0)
		{
			perror ("**Error in recvfrom!!!**");
			return 0;
		}
		else
		{
			buffer[received_bytes] = 0;
			printf ("Server:  %s \n ", buffer);
		}
	}while(1);
	//no need to close client, runs infinitely.
	// close (client_socket);
}
