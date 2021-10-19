#ifndef STRUCT
#define STRUCT

#include <unistd.h>
#include <stdlib.h>

int init_shm(int is_company, char* c_name);

struct company {
	int n_of_soil_done; 
    char name[20];
    char is_empty;
};

struct company_registry {
    struct company companies[50];
};

struct company_registry *ptr;

// semaphore for a shm
SEM_ID lock;

#endif // STRUCT
