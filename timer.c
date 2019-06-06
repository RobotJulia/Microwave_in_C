#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX_SEC 6039
#define KEY 0x520260A

enum op {SYNCH, DOOR, LIGHT, EMIT, KEYPAD, RUN, TIME};

void stopTimer();
int *shm;
int shm_id;

int main() {
	key_t key = KEY;
	shm_id = shmget(key, sizeof(int)*10, 0666);
	shm = shmat(shm_id,0,0);
	int time = *(shm+TIME);
	printf(" shm_id = %d\n", shm_id);
	printf("waiting for GO.\n");
	while ( *(shm+SYNCH) == 0 );
	printf("timer application started.\n");

	while(1) {
		if(*(shm+TIME) != 0) {
			time = *(shm+TIME);
		}
		while(*(shm+RUN) == 1) {
			printf("running microwave \n");
			if(*(shm+DOOR) == 0) { // door is closed

				*(shm+EMIT) = 1;
				*(shm+LIGHT) = 1;
				
				printf("Time: %d \n", time);
				sleep(1);
				time--;
				*(shm+TIME) = time;
				if(time == 0) {
					stopTimer();
				}
			}
			else {
				stopTimer();
				// after the door is opened how do you resume?
				if(shm[RUN] == 1) {
					continue;
				}
			}
		}
	}
}

void stopTimer(){
	
	shm[EMIT] = 0;
	shm[RUN] = 0;
	
	//*(shm+TIME) = time;
	printf("\a");
	printf("cooking done \n");
}
