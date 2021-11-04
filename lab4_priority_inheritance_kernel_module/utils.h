#ifndef UTILS_H
#define UTILS_H
/* Includes */
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
extern int num_of_mes;
extern int end;

/* Subtract the `struct timespec' values X and Y,
   storing the result in RESULT (result = x - y).
   Return 1 if the difference is negative, otherwise 0.  */

int timespec_subtract (	struct timespec *result,
						struct timespec *x,
						struct timespec *y);

void tHPrio();

void tMPrio();

void tLPrio();

void do_work_for_some_time(int x);

void do_something_while_the_mutex_is_locked();

void do_something_very_long();

int time_to_ms (struct timespec *time);

#endif /* UTILS_H */
