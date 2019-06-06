#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int option = 0, power = 100, time = 0;
enum op {SYNCH, DOOR, LIGHT, EMIT, KEYPAD, RUN, COOKTIME};

main(int argc, char argv[]) {

	key_t key;
	int shm_id;
	int *shm;
	//printf("enum %d\n", SYNCH);
	//printf("enum %d\n", DOOR);
	key=0x520260A;
	//key = ftok("/home/kosuke/IPU", 'a' );
	//printf("key= %x\n", key);
	shm_id = shmget(key, sizeof(int)*10,  IPC_CREAT| 0666);
	//printf(" shm_id = %d\n", shm_id);

	shm = shmat(shm_id,0,0);
	*(shm+SYNCH) = 0;
	//printf(" *shm = %d\n", *shm);
	printf(" run all the programs now,\n");
	printf(" then hit the return key.\n");
	getchar();
	*(shm+SYNCH) = 1;

	// set/check operation modes, door open/closed, running/not running.
}


