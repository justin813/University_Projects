#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
/*Exit Flags
 * */

//Global Variables
key_t key = 210658;
//semaphore set pointer
int semSetId;
//creates semphore set with 3 pre-determined semaphores
int createSemaphoreSetOfSizeThree(){
	int semId;
	//3 represents the amount of semphores in the semget fn
	if ((semId = semget(key, 3, 0600 | IPC_CREAT)) == -1) {
        printf("Error creating semaphore set\n");
        exit(1);
    }
    //create 3 semaphores
    //Semphore 0 - Controls access to crit space
		// 1 = producer/consumer can access critical space, shared mem
		// 0 = NO access to critcal space, shared mem
	if(semctl(semSetId, 0, SETVAL, 0) == -1){
		printf("Error intializing semaphore 0 with value 0");
		exit(2);
	}
	//Semphore 1 - Indicates queue's Fill status
		// 10 > semval > 0 = queue is NOT full
		// 0 = queue full
	if(semctl(semSetId, 1, SETVAL, 9) == -1){
		printf("Error intializing semaphore 1 with value 9");
		exit(3);
	}
	//Semphore 2 - Indicates queue's empty status
		// 10 > semval > 0 = queue is NOT empty
		// 0 = queue empty
	if(semctl(semSetId, 2, SETVAL, 0) == -1){
		printf("Error intializing semaphore 2 with value 0");
		exit(2);
	}
	return semId;
}
int main(int argc, char *argv[]){
    {
		//local scope that takes in command line args
		int numProducers = atoi(argv[1]);
		int numConsumers = atoi(argv[2]);
		int productionRate = atoi(argv[3]);
		char *tableHeader = "pid\n";
		printf("%s", tableHeader);
	}
	semSetId = createSemaphoreSetOfSizeThree();
	printf("Success\nGot Sem Set: %d\n", semSetId);
	return 0;
}
