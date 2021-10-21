#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <semLib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "structs.h"

#include <fcntl.h>

int main(){
	int id = init_shm(0, "");
	if (id != 0) exit(10);
	char name[20];
	
	printf("--- Monitor started ---\n");
	while(1) {
		for (int i = 0; i < 50; ++i) {
			semTake(lock, WAIT_FOREVER);
			if ((&ptr->companies[i])->is_empty){
				semGive(lock);
				continue;
			} else {
				strcpy(name, (&ptr->companies[i])->name);
				semGive(lock);
				printf("%s\t: %i\n", name, (&ptr->companies[i])->n_of_soil_done);
			}
		}
		printf("-----------------------\n");
		sleep(1);
	}
	return 0;
}
