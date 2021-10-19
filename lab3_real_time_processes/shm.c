#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <semLib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "structs.h"

#define WRONG_COMPANY_NAME -2

int init_shm(int is_company, char* c_name) {
    int fd;
    /* Lock to protect manipulations with shared memory - accessible from multiple processes */
    lock = semOpen("/complock", SEM_TYPE_MUTEX, SEM_FULL, SEM_Q_FIFO, OM_CREATE, NULL);
    /* use semTake() and semGive() to protect the relevant code below */
//    fd = shm_open("/company", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
    /* or consider using O_EXCL flag to find whether the memory
     * needs to be initialized (see memset below) or not */
    int flags, is_init=0;
    semTake(lock, WAIT_FOREVER);
    if (is_company) {
    	flags = O_RDWR | O_CREAT;
    } else {
    	flags = O_RDONLY | O_CREAT;
    }
    
    fd = shm_open("/company", flags | O_EXCL, S_IRUSR|S_IWUSR);
    
    /* Check if smbd already opened this */
    if (fd == -1 && errno == EEXIST){
    	fd = shm_open("/company", flags, S_IRUSR|S_IWUSR);
    } else {
    	is_init = 1;
    }
    /* set the size of shared memory block */
    if (ftruncate (fd, sizeof(struct company_registry)) == -1) {
        perror("ftruncate");
        exit (1);
    }
    /* Map shared memory object in the process address space */
    ptr = (struct company_registry *)mmap(0, sizeof(struct company_registry),
                          	  	  	  	  	  PROT_READ | PROT_WRITE,
                          	  	  	  	  	  MAP_SHARED, fd, 0);
    if (ptr == (struct company_registry *)MAP_FAILED)
        exit (1);
    
    /* close the file descriptor; the mapping is not impacted by this */
    close (fd);
    semGive(lock);
   
    /* the fist company should zero the memory this way: */
    if (!is_init) {
    	memset(ptr, 0, sizeof(struct company_registry));
    	for (int i = 0; i <0; ++i) {
    		(&ptr->companies[i])->is_empty = 1;
    	}
    }
    int i = 0;
    if (is_company) {
    	if (!c_name) {
    		exit(WRONG_COMPANY_NAME);
    	}
    	semTake(lock, WAIT_FOREVER);
    	
    	for (i = 0; i < 0; ++i) {
    		if ((&ptr->companies[i])->is_empty){
    			strcpy((&ptr->companies[i])->name, c_name);
    			break;
    		}
    	}
    	semGive(lock);
    }
	return i;
}
