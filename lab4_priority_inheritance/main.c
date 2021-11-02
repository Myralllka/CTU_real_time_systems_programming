#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <taskLib.h>
#include <semLib.h>
#include <sysLib.h>

#include "config.h"

SEM_ID global_mutex;
int num_of_mes;
int end = 0;

/* Subtract the `struct timespec' values X and Y,
   storing the result in RESULT (result = x - y).
   Return 1 if the difference is negative, otherwise 0.  */

int timespec_subtract (	struct timespec *result,
						struct timespec *x,
						struct timespec *y){
  /* Perform the carry for the later subtraction by updating Y. */
  if (x->tv_nsec < y->tv_nsec) {
    int num_sec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
    y->tv_nsec -= 1000000000 * num_sec;
    y->tv_sec += num_sec;
  }
  if (x->tv_nsec - y->tv_nsec > 1000000000) {
    int num_sec = (x->tv_nsec - y->tv_nsec) / 1000000000;
    y->tv_nsec += 1000000000 * num_sec;
    y->tv_sec -= num_sec;
  }

  /* Compute the time remaining to wait.
     `tv_nsec' is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_nsec = x->tv_nsec - y->tv_nsec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

void do_work_for_some_time(int x)
{
    long int len = x * 100000000;
    while (len > 0) len--;
}

void do_something_while_the_mutex_is_locked() {
	do_work_for_some_time(5);
}

void do_something_very_long() {
	do_something_very_long(30);
}

// activated first
// low priority task
void tLPrio() {
	while (!end) {
	  semTake(global_mutex, WAIT_FOREVER);
	  do_something_while_the_mutex_is_locked();
	  semGive(global_mutex);
	  taskDelay(LOW_PRIORITY_DELAY); /* this delay can be even zero - do you know why? */
	}
}

// activated second
// middle priority task
void tMPrio() {
	while (!end) {
	  do_something_very_long();
	  taskDelay(MID_PRIORITY_DELAY); /* wait to let the low priority task run */
	}
}

// activated third
// high priority task
void tHPrio() {
	// pseudocode 
	for (int i = 0; i < num_of_mes; ++i) {
	  struct timespec tstart, tend, result;
	  clock_gettime(CLOCK_MONOTONIC, &tstart);
	  if (semTake(global_mutex, WAIT_FOREVER) == ERROR)
	    fprintf(stderr, "semTake error\n");
	  clock_gettime(CLOCK_MONOTONIC, &tend);
	  semGive(global_mutex);
	  timespec_subtract(&result, &tend, &tstart);
	  // Handle measurement and print if necessary 
	  taskDelay(HIGH_PRIORITY_DELAY); // let other tasks run 
	}
	end = 1; // Signal the other tasks to end 
}

int main(int argc, char* argv[]) {

	cpuset_t affinity;

	if (argc != 3) return -1;
	if (argv[1][0] == '1') {
		global_mutex = semMCreate(SEM_DELETE_SAFE);
	} else if (argv[1][0] == '2') {
		global_mutex = semMCreate(SEM_INVERSION_SAFE | SEM_DELETE_SAFE);
	} else return -2;
	
	num_of_mes = atoi(argv[2]);
	
//	printf("%s\n", "Measurement started");
//	
//	printf("%s\n", "Measurement finished");
	int l, m, h;

	/* Create the task but only activate it after setting its affinity */
	l = taskCreate("tLPrio", 210, 0, 4096, (FUNCPTR) digger_up_the_hole, i, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	l = taskCreate("tMPrio", 210, 0, 4096, (FUNCPTR) digger_up_the_hole, i, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	l = taskCreate("tHPrio", HIGH_PRIORITY, 0, 4096, (FUNCPTR) digger_up_the_hole, i, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if (tid == NULL)
	    return (ERROR);

	/* Clear the affinity CPU set and set index for CPU 1 */
	CPUSET_ZERO (affinity);
	CPUSET_SET (affinity, 1);

	if (taskCpuAffinitySet (tid, affinity) == ERROR)
	{
	    /* Either CPUs are not enabled or we are in UP mode */
	    taskDelete (tid);
	    return (ERROR);
	}

	/* Now let the task run on CPU 1 */
	taskActivate (tid);
	
	// Measured worst-case mutex blocking time is printed to standard output each 
	// time it changes as integer number of milliseconds (without units) followed 
	// by a newline character.
	
	// To achieve higher clock precision use sysClkRateSet() function.
	
	printf("Hello world\n");
	return 0;
}
