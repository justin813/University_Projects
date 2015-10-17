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

#define BUFSIZE 256

void openClientAccess(int clientPort);

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
    int sock, clientSock, newForwardedSocket, portNum, clientlength, pid;
    struct sockaddr_in serverAddress, clientAddress;
    //char bufferIn[256], bufferOut[256];
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

	printf("\nTCPServer Waiting for client on port 8686");
    fflush(stdout);
    clientlength = sizeof(clientAddress);
    /*
   * main loop: wait for a connection request, echo connected line,
   * then close connection.
   */
    while(true){
        //accept connection request
        clientSock = accept(sock, (struct sockaddr *) &clientAddress.sin_addr,
            &clientlength);
        if (clientlength < 0)
            error("ERROR on accept");
        pid = fork();
        if (pid < 0) {
            perror("ERROR on fork");
            exit(1);
        }
        if (pid == 0) {
            /* This is the client process */
            //allows client to be redirected to another port
            close(sock);
            openClientAccess(clientSock);
            exit(0);
        }
        else
        {
            close(clientSock);
        }
    }
    //close server
    close(sock);
    return 0;
}
void openClientAccess(int clientPort){
    char buffer[256];
    bzero(buffer,256);
    write(clientPort,"Welcome please enter a number use.\n",buffer);
    programMenu(int clientPort);
}
void programMenu(int clientPort){
    int n;
    char buffer[256];
    bzero(buffer,256);
    bool running = true;
    char data[];
    char menu[] = "1. Host current Date and Time\n2. Host uptime\n3. Host" +
        " memory use\n4. Host Netstat\n5. Host current users\n"+
        "6. Host running processes\n7. Quit\n";
    char invaild[] = "Invaild Choice\n";
    while (running) {
        write(clientPort, menu, sizeof(menu));
        n = read(clientPort,buffer,255);
        switch (atoi(n)) {
            //Option 1 displays the Date and Time realtive to the host in UTC
            case 1:
                break;
            //Option 2 tells how long server has been up
            case 2:
                break;
            //Option 3 tells how much memory it takes on host
            case 3:
                data[] = "";
                break;
            //Option 4 returns Netstat results
            case 4:
                break;
            //Option 5 reports how many users are in use
            case 5:
                break;
            //Option 6 displays running processes
            case 6:
                break;
            //Option 7 quit
            case 7:
                data[] = "GoodBye\n";
                running = false;
                break;
            default:
                data[] = "\n";
                break;
        }
        write(clientPort, data, sizeof(data));
    }
}
