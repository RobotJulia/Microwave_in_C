#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
enum op {SYNCH, DOOR, LIGHT, EMIT, KEYPAD, RUN, COOKTIME};

main() {
	key_t key;
	int shm_id;
	int *shm;
	int doorstat;
	int oc;
	
	key=0x520260A;
	//key = ftok("/home/kosuke/IPU", 'a' );
	printf("key= %x\n", key);
	shm_id = shmget(key, sizeof(int)*10, 0666);
	
	printf(" shm_id = %d\n", shm_id);
	shm = shmat(shm_id,0,0);
	printf("waiting for GO.\n");
	while ( *(shm+SYNCH) == 0 );

	printf("door application started.\n");
	while(1) {
		scanf("%d", &oc);
		if(oc == 1) {
			*(shm + DOOR) = 1;
			*(shm + RUN) = 0;
			printf("door is open, press 0 to close.\n");
			
		}
		if(oc == 0) {
			*(shm + DOOR) = 0;
			printf("door closed. ");
			if(shm[COOKTIME] > 0) {
				*(shm + RUN) = 1;
			}
			printf("resuming...\n");
		}
		
	}
}
