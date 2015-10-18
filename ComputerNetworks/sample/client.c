/*
Author: Nagavarun Kanaparthy
Date: 10/16/2015
Client side interface access
Program Details:
This app will basically just be sending data to the server program.
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <bool.h>
//initialize communications
//

//error handeler
void error(char *msg){
    perror(msg);
    exit(1);
}
//main program will be connecting and sending data to the server data
int main(int argc, char *argv[])
{
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(7891);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, buffer, 1024, 0);
    /*---- Print the received message ----*/
    printf("Received: %s\n",buffer);
    while (buffer != NULL) {
        /*---- Read the message from the server into the buffer ----*/
        recv(clientSocket, buffer, 1024, 0);
        /*---- Print the received message ----*/
        printf("Data received: %s",buffer);
    }
    return 0;
}
