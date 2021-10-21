#include <stdlib.h>
#include <stdio.h>
#include "config.h"

/* Subtract the `struct timespec' values X and Y,
   storing the result in RESULT (result = x - y).
   Return 1 if the difference is negative, otherwise 0.  */

int timespec_subtract (	struct timespec *result,
						struct timespec *x,
						struct timespec *y)
{
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


// activated first
// low priority task
void tLPrio() {
//	while (!end) {
//	  semTake(mutex, WAIT_FOREVER);
//	  do_something_while_the_mutex_is_locked();
//	  semGive(mutex);
//	  taskDelay(LOW_PRIORITY_DELAY); /* this delay can be even zero - do you know why? */
//	}
}

// activated second
// middle priority task
void tMPrio() {
//	while (!end) {
//	  do_something_very_long();
//	  taskDelay(MID_PRIORITY_DELAY); /* wait to let the low priority task run */
//	}
}

// activated third
// high priority task
void tHPrio() {
	// pseudocode 
	/* while (loop NUMBER_OF_MEASUREMENTS times ) {
	  struct timespec tstart, tend, result;
	  clock_gettime(CLOCK_MONOTONIC, &tstart);
	  if (semTake(mutex, WAIT_FOREVER) == ERROR)
	    fprintf(stderr, "semTake error\n");
	  clock_gettime(CLOCK_MONOTONIC, &tend);
	  semGive(mutex);
	  timespec_subtract(&result, &tend, &tstart);
	  // Handle measurement and print if necessary 
	  taskDelay(HIGH_PRIORITY_DELAY); // let other tasks run 
	  n++;
	}

	end = 1; // Signal the other tasks to end  */
}

int main(int argc, char* argv[]) {
	// argv[1] == "1" 	--> runs the tasks without priority inheritance,
	// argv[1] == "2" 	--> runs the tasks with priority inheritance,
	// other   		  	--> terminates the app
	
	// argv[2] 		  	--> configures the number of measurements
	
	// Report start of the measurement by printing measurement started and end of 
	// the measurement by printing measurement finished. As measurement finishes, 
	// all created tasks should end as well.
	
	// This behaviour is controlled by the high priority task. When the target 
	// number of the measurements is reached, a global variable (e.g. end) should 
	// be set to a certain value, that allows the other tasks to end.
	
	
	// Measured worst-case mutex blocking time is printed to standard output each 
	// time it changes as integer number of milliseconds (without units) followed 
	// by a newline character.
	
	
	// To achieve higher clock precision use sysClkRateSet() function.
	
	printf("Hello world\n");
	return 0;
}
