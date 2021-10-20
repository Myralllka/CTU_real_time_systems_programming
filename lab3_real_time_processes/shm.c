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

#define WRONG_COMPANY_NAME 2
#define ERROR_FTRUNC 3
#define ERROR_MAPPING 4
#define ERROR_OPEN_FILE 6

int init_shm(int is_company, char* c_name) {
    int fd;
    /* Lock to protect manipulations with shared memory - accessible from multiple processes */
    lock = semOpen("/complock", SEM_TYPE_MUTEX, SEM_EMPTY, SEM_Q_FIFO, OM_CREATE, NULL);
    /* use semTake() and semGive() to protect the relevant code below */
//    fd = shm_open("/company", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
    /* or consider using O_EXCL flag to find whether the memory
     * needs to be initialized (see memset below) or not */
    int is_init=0;
    semTake(lock, WAIT_FOREVER);
 
    fd = shm_open("/company", O_RDWR | O_CREAT | O_EXCL, S_IRUSR|S_IWUSR);
    
    /* Check if smbd already opened this */
    
    if (fd == -1){
    	if (errno != EEXIST) {
    		semGive(lock);
    		exit(ERROR_OPEN_FILE);
    	}
    	// Not first open
    	fd = shm_open("/company", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
		if (fd == -1) {
			semGive(lock);
			exit(ERROR_OPEN_FILE);
		}
		is_init = 1;
    }
    if (ftruncate (fd, sizeof(struct company_registry)) == -1) {
		perror("ftruncate");
		semGive(lock);
		exit (ERROR_FTRUNC);
	}
    
    /* Map shared memory object in the process address space */
    ptr = (struct company_registry *)mmap(0, sizeof(struct company_registry),
                          	  	  	  	  	  PROT_READ | PROT_WRITE,
                          	  	  	  	  	  MAP_SHARED, fd, 0);
    if (ptr == (struct company_registry *)MAP_FAILED) {
    	semGive(lock);
    	exit (ERROR_MAPPING);
    }
        
    
    /* close the file descriptor; the mapping is not impacted by this */
    close (fd);
    semGive(lock);
   
    /* the fist company should zero the memory this way: */
    if (!is_init) {
    	semTake(lock, WAIT_FOREVER);
    	memset(ptr, 0, sizeof(struct company_registry));
    	for (int i = 0; i < 50; ++i) {
    		(&ptr->companies[i])->is_empty = 1;
    	}
    	semGive(lock);
    }
    
    int i = 0;
    if (is_company) {
    	if (!c_name) {
    		exit(WRONG_COMPANY_NAME);
    	}
    	
    	semTake(lock, WAIT_FOREVER);   	
    	for (i = 0; i < 50; ++i) {
    		if ((&ptr->companies[i])->is_empty){
    			strcpy((&ptr->companies[i])->name, c_name);
    			(&ptr->companies[i])->is_empty = 0;
    			break;
    		}
    	}
    	semGive(lock);
    	return i;
    }
	return 0;
}
