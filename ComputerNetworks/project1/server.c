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
    char buffer[256];
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

    //Give the socket a name
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htone

    //close server
    close(sock);
    return 0;
}
