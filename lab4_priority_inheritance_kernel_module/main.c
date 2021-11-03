#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sysLib.h>
#include <taskLib.h>
#include <semLib.h>
#include <timers.h>
#include <cpuset.h>
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
  sysClkRateSet(CLOCK_RATE);
	
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
	do_work_for_some_time(LOW_PRIORITY_WORK);
}

void do_something_very_long() {
	do_work_for_some_time(MID_PRIORITY_WORK);
}

/* activated first
low priority task*/
void tLPrio() {
	while (!end) {
	  semTake(global_mutex, WAIT_FOREVER);
	  do_something_while_the_mutex_is_locked();
	  semGive(global_mutex);
	  taskDelay(LOW_PRIORITY_DELAY); /* this delay can be even zero - do you know why? */
	}
}

/* activated second
 middle priority task */
void tMPrio() {
	while (!end) {
	  do_something_very_long();
	  taskDelay(MID_PRIORITY_DELAY); /* wait to let the low priority task run */
	}
}
int time_to_ms (struct timespec *time) {
	return time->tv_sec * 1000 + time->tv_nsec / 1000000;
}
/* activated third
 high priority task */
void tHPrio() {
	
	printf("%s\n0\n", "Measurement started");
	int max_time = 0, current;
	int i;
	for (i = 0; i < num_of_mes; ++i) {
	  struct timespec tstart, tend, result;
	  clock_gettime(CLOCK_MONOTONIC, &tstart);
	  if (semTake(global_mutex, WAIT_FOREVER) == ERROR)
	    fprintf(stderr, "semTake error\n");
	  clock_gettime(CLOCK_MONOTONIC, &tend);
	  semGive(global_mutex);
	  timespec_subtract(&result, &tend, &tstart);
	  /* Handle measurement and print if necessary*/
	  current = time_to_ms(&result);
	  if (current > max_time) {
		  printf("%i\n", current);
		  max_time = current;
	  }
	  taskDelay(HIGH_PRIORITY_DELAY); // let other tasks run 
	}
	end = 1; // Signal the other tasks to end
	printf("%s\n", "Measurement finished");
}

void CreateTasks(int a1, int a2) {
	
	cpuset_t affinity;

	if (a1 == 1)
		global_mutex = semMCreate(0);
	else if (a1 == 2)
		global_mutex = semMCreate(SEM_INVERSION_SAFE|SEM_Q_PRIORITY);
	else return;
	
	num_of_mes = a2;
	sysClkRateSet(CLOCK_RATE);

	TASK_ID low, middle, high;
	
	/* Create the task but only activate it after setting its affinity */
	low = taskCreate("tLPrio", LOW_PRIORITY, 0, 4096, (FUNCPTR) tLPrio, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	middle = taskCreate("tMPrio", MID_PRIORITY, 0, 4096, (FUNCPTR) tMPrio, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	high = taskCreate("tHPrio", HIGH_PRIORITY, 0, 4096, (FUNCPTR) tHPrio, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	if (low == TASK_ID_ERROR || middle == TASK_ID_ERROR || high == TASK_ID_ERROR)
	    return;
	
	/* Clear the affinity CPU set and set index for CPU 1 */
	CPUSET_ZERO (affinity);
	CPUSET_SET (affinity, 0);
	
	if (taskCpuAffinitySet ( low, affinity) == ERROR || 
			taskCpuAffinitySet(middle, affinity) == ERROR || 
			taskCpuAffinitySet(middle, affinity) == ERROR) {
	    /* Either CPUs are not enabled or we are in UP mode */
	    taskDelete (low);
	    taskDelete(middle);
	    taskDelete(high);
	    return;
	}
	
	/* Now let the task run on CPU 1 */
	taskActivate (low);
	taskActivate(middle);
	taskActivate(high);
	
	return;
}
