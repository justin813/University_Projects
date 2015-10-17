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
#include <sys/sysinfo.h>
#include <time.h>
#include <bool.h>

#define BUFSIZE 256
//Initialization
void openClientAccess(int clientPort);
static void startTimersAndSysInfo();
//Program functions
static char[] getHostCurrentTime();
static char[] getHostUptime();
static char[] getHostMemUsage();
static char[] getHostRunningProccesses();
static double getMillisecondExecution();
static char[] getNetStats();
static char[] getUsers();
//error response
void error(char *msg){
    perror(msg);
    exit(1);
}

//Global Variables
static clock_t start;
static struct sysinfo info;
/*
Main Program Starts here
*/
int main(int argc, char *argv[])
{
    //Initialize timer and host data
    startTimersAndSysInfo();
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
    //Print out time it took to Initialize
    printf("Time elapsed to grab port : %f milliseconds\n"
    , getMillisecondExecution());
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
        //Print out time it took to initialize child
        printf("Attempting To spawn child at : %f milliseconds\n"
                , getMillisecondExecution());
        pid = fork();
        if (pid < 0) {
            perror("ERROR on fork");
            exit(1);
        }
        if (pid == 0) {
            /* This is the client process */
            //allows client to be redirected to another port
            close(sock);
            printf("Successfully spawned child at : %f milliseconds\n"
                    , getMillisecondExecution());
            openClientAccess(clientSock);
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
/*
Functions:
Initialize
- openClientAccess
- startTimersAndSysInfo
Program functions
-programMenu
-getHostCurrentTime
-getHostUptime
-getHostMemUsage
-getHostRunningProccesses
*/
static void startTimersAndSysInfo(){
    //start timer
    start = clock();
    //get host data
    int error = sysinfo(&info);
    if(error != 0){
        printf("code error = %d\n", error);
    }
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
                data[] = getHostCurrentTime();
                break;
            //Option 2 tells how long server has been up
            case 2:
                data[] = getHostUptime();
                break;
            //Option 3 tells how much memory it takes on host
            case 3:
                data[] = getHostMemUsage();
                break;
            //Option 4 returns Netstat results
            case 4:
                data[] = getNetStats();
                break;
            //Option 5 reports how many users are in use
            case 5:
                data[] = getUsers();
                break;
            //Option 6 displays running processes
            case 6:
                data[] = getHostRunningProccesses();
                break;
            //Option 7 quit
            case 7:
                data[] = "GoodBye\n";
                running = false;
                break;
            default:
                data[] = "Please select a vaild number of 1 to 7.\n";
                break;
        }
        write(clientPort, data, sizeof(data));
    }
}
static char[] getHostCurrentTime(){
    time_t current_time;
    char* c_time_string;

    /* Obtain current time as seconds elapsed since the Epoch. */
    current_time = time(NULL);

    if (current_time == ((time_t)-1))
    {
        c_time_string = "ERROR: Failed To Calculate Time\n";
    }

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    if (c_time_string == NULL)
    {
        c_time_string = "ERROR: Failed To Convert To Local TimeZone\n";
    }

    return c_time_string;
}
static char[] getHostUptime(){
    return "The Host's Uptime is " + info.uptime +" seconds\n";
}
static char[] getHostMemUsage(){
    return "The Program is using " + info.mem_unit +" Bytes of memory\n";
}
static char[] getHostRunningProccesses(){
    return "The Host has " + info.procs +" processes running\n";
}
static char[] getNetStats(){
    FILE *fp;
    int status;
    char path[1035];
    char data[];
    fp = fopen("/proc/net/tcp", "r");
    if (fp == NULL) {
        printf("Failed to run Netstat command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        data += path;
    }
    return "The Host's Netstat is\n"+ data + "\n";
}
static char[] getUsers(){
    FILE *fp;
    int status;
    char path[1035];
    char data[];
    fp = fopen("/proc/net/tcp", "r");
    if (fp == NULL) {
        printf("Failed to run Netstat command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) {
        data += path;
    }
    return "The Host's Netstat is\n"+ data;
}
static double getMillisecondExecution(){
    return ((double)clock() - start)/ CLOCKS_PER_SEC;
}
