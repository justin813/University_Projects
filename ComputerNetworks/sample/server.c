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
#include <stdbool.h>

//Program functions
void programMenu(int clientPort);
static char* getHostCurrentTime();
static char* getHostUptime();
static char* getHostMemUsage();
static char* getHostRunningProccesses();
static double getMillisecondExecution();
static void getNetStats(int clientPort);
static void getUsers(int clientPort);
//error response
void error(char *msg){
    perror(msg);
    exit(1);
}
//Global Variables
static clock_t start;
static struct sysinfo info;
static char buffer[1024];

/*
Main Program Starts here
*/
int main(int argc, char *argv[]){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
  strcpy(buffer,"Hello World\n");
  send(newSocket,buffer,13,0);

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

    char* data = "Welcome please enter a number use.\n";
    bzero(buffer,256);
    write(clientPort,data,sizeof(data));
    programMenu(clientPort);
}
void programMenu(int clientPort){
    int n;
    char buffer[256];
    bzero(buffer,256);
    bool running = true;
    char* data;
    char* menu = "1. Host current Date and Time\n2. Host uptime\n3. Host memory use\n4. Host Netstat\n5. Host current users\n6. Host running processes\n7. Quit\n";
    char invaild[] = "Invaild Choice\n";
    while (running) {
        write(clientPort, menu, sizeof(menu));
        n = read(clientPort,buffer,255);
        switch (n) {
            //Option 1 displays the Date and Time realtive to the host in UTC
            case 1:
                data = getHostCurrentTime();
                break;
            //Option 2 tells how long server has been up
            case 2:
                data = getHostUptime();
                break;
            //Option 3 tells how much memory it takes on host
            case 3:
                data = getHostMemUsage();
                break;
            //Option 4 returns Netstat results
            case 4:
                data = "Completed Netstat";
				getNetStats(clientPort);
                break;
            //Option 5 reports how many users are in use
            case 5:
                data = "completed getting users";
				getUsers(clientPort);
                break;
            //Option 6 displays running processes
            case 6:
                data = getHostRunningProccesses();
                break;
            //Option 7 quit
            case 7:
                data = "GoodBye\n";
                running = false;
                break;
            default:
                data = "Please select a vaild number of 1 to 7.\n";
                break;
        }
        write(clientPort, data, sizeof(data));
    }
}
static char* getHostCurrentTime(){
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
static char* getHostUptime(){
	char data[250];
	sprintf(data, "The Host's Uptime is %ld seconds\n", info.uptime);
	strcpy(buffer, data);
    return buffer;
}
static char* getHostMemUsage(){
	char data[250];
	sprintf(data, "The Program is using %ld Bytes of memory\n", info.bufferram);
	strcpy(buffer, data);
    return buffer;
}
static char* getHostRunningProccesses(){
	char data[250];
	sprintf(data, "The Host has %d processes running\n", info.procs);
	strcpy(buffer, data);
    return buffer;
}
static double getMillisecondExecution(){
    return ((double)clock() - start)/ CLOCKS_PER_SEC;
}
static void getNetStats(int clientPort){
	FILE *fp;
	char path[1035];
	/* Open the command for reading. */
	fp = popen("netstat", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}
	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		write(clientPort, path, sizeof(path));
	}
	/* close */
	pclose(fp);
}
static void getUsers(int clientPort){
    FILE *fp;
	char path[1035];
	/* Open the command for reading. */
	fp = popen("awk -F':' '{ print $1}' /etc/passwd", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}
	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		write(clientPort, path, sizeof(path));
	}
	/* close */
	pclose(fp);
}
