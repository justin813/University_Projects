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
//error handeler
void error(char *msg){
    perror(msg);
    exit(1);
}
//main program will be connecting and sending data to the server data
int main(int argc, char *argv[])
{
}
