#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <semLib.h>
#include <fcntl.h>

struct company {
    char name[20];
    int work_done;
};

struct company_registry {
    struct company companies[50];
};

struct company_registry *ptr;
SEM_ID lock;

void init_shm(void)
{
//    int fd;
//
//    /* Lock to protect manipulations with shared memory - accessible from multiple processes */
//    lock = semOpen("/complock", SEM_TYPE_MUTEX, SEM_FULL, SEM_Q_FIFO, OM_CREATE, NULL);
//    /* use semTake() and semGive() to protect the relevant code below */
//
//    fd = shm_open("/company", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
//    /* or consider using O_EXCL flag to find whether the memory
//     * needs to be initialized (see memset below) or not */
//    fd = shm_open("/company", O_RDWR | O_CREAT | O_EXCL, S_IRUSR|S_IWUSR);
//
//    /* set the size of shared memory block */
//    if (ftruncate (fd, sizeof(struct company_registry)) == -1) {
//        perror("ftruncate");
//        exit (1);
//    }
//
//    /* Map shared memory object in the process address space */
//    ptr = (struct company_registry *)mmap(0, sizeof(struct company_registry),
//                          PROT_READ | PROT_WRITE,
//                          MAP_SHARED, fd, 0);
//
//    if (ptr == (struct company_registry *)MAP_FAILED)
//        exit (1);
//
//    /* close the file descriptor; the mapping is not impacted by this */
//    close (fd);
//
//    /* ... */
//
//    /* the fist company should zero the memory this way: */
//    memset(ptr, 0, sizeof(struct company_registry));
//
//    /* ... register this company to the memory ... */
}
