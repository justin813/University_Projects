/*
Author: Nagavarun Kanaparthy
Date: 10/16/2015
Server side responder
Program Details:
1. Host current Date and Time
2. Host uptime
3. Host memory use
4. Host Netstat
5. Host current users
6. Host running processes
7. Quit
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <bool.h>

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    //create Server TCP/IP socket listener
    //Port Number and Hostname initialization
    uint32_t portNumber = 8686;
    char* hostName = "192.168.0.1";
    /*
    - Socket server connection
    - Socket client connection
    - Forward Socket
    - Port #
    - Client response length
    - Buffer (values from/to Server)
    - Define socket address size
    */
    int sock, newForwardedSocket, portNum, clientlength;
    struct sockaddr_in serverAddress, clientAddress;
    char bufferIn[1024], bufferOut[1024];
    int socketAddressSize;
    //Initializes the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket Failed to Initialize");
            exit(2);
        }
    //Sets the socket options
    if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
        perror("Setsockopt");
        exit(3);
    }
    //Give the socket a name, port, address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    inet_aton(hostName, &serverAddress.sin_addr.s_addr);
    //Initialize serverAddress with 0s
    bzero(&(serverAddress.sin_zero),8);
    //Bind socket toward server
    if (bind(sock, (struct sockaddr *)&serverAddress,
        sizeof(struct serverAddress)) == -1)
        {
            perror("Unable to bind");
            exit(4);
        }
    //Start listening on the server with max of 10 simultanious connections
    if (listen(sock, 10) == -1) {
            perror("Listen");
            exit(5);
        }

	printf("\nTCPServer Waiting for client on port 5000");
    fflush(stdout);

    puts("Connected\n");
    //close server
    close(sock);
    return 0;
}
