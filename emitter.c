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
	int emitstat;
	int os = 0;
	
	key=0x520260A;
	//key = ftok("/home/kosuke/IPU", 'a' );
	printf("key= %x\n", key);
	shm_id = shmget(key, sizeof(int)*10, 0666);
	
	printf(" shm_id = %d\n", shm_id);
	shm = shmat(shm_id,0,0);
	printf("waiting for GO.\n");
	while ( *(shm+SYNCH) == 0 );

	printf("emitter application started.\n");
	while(1) {
		if (*(shm+RUN) == 1 && *(shm+DOOR) == 0 && *(shm+COOKTIME) > 0) {
         *(shm+EMIT) = 1;
         if (os == 0) {
            os = 1;
            printf("Emitter is on.");
         }
      } else {
         *(shm+EMIT) = 0;
         if (os == 1) {
            os = 0;
            printf("Emitter is off.");
         }
      }
	}
}
