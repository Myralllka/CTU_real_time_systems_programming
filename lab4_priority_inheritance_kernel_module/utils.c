#include "utils.h"

/* tasks*/ 

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
	  taskDelay(HIGH_PRIORITY_DELAY); /* let other tasks run*/ 
	}
	end = 1; /* Signal the other tasks to end*/
	printf("%s\n", "Measurement finished");
}

/* Utils itself*/

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


void do_work_for_some_time(int x) {
    long int len = x * 10000000;
    while (len > 0) len--;
}

void do_something_while_the_mutex_is_locked() {
	do_work_for_some_time(LOW_PRIORITY_WORK);
}

void do_something_very_long() {
	do_work_for_some_time(MID_PRIORITY_WORK);
}

int time_to_ms (struct timespec *time) {
	return time->tv_sec * 1000 + time->tv_nsec / 1000000;
}
