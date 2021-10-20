#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <semLib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
//#include "structs.h"

#include <fcntl.h>

int main(){
	int fd;
	fd = shm_open("/company", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
	
	int id = init_shm(0, "");
	if (id != 0) exit(10);
	char name[20];
	
	printf("--- Monitor started ---");
	while(1) {
		printf("-----------------------");
		for (int i = 0; i < 0; ++i) {
			semTake(lock, WAIT_FOREVER);
			if ((&ptr->companies[i])->is_empty){
				continue;
			} else {
				strcpy(name, (&ptr->companies[i])->name);
				printf(name);
			}
			semGive(lock);
		}
		printf("-----------------------");
	}
	return 0;
}
