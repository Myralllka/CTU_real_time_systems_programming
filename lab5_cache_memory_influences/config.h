#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sysLib.h>
#include <taskLib.h>
#include <timers.h>
#include <cpuset.h>

/* sysClkRateSet(CLOCK_RATE) */
#define CLOCK_RATE 1000
#define MAX_ARRAY_LEN (4*1024*1024/sizeof(struct elem))
#define GAP 0

/* Modes for `measureCache` */
#define SEQUENTIAL 0
#define RANDOM 1


struct elem {
  struct elem *next;
  int gap[GAP];
};

struct elem global_array[MAX_ARRAY_LEN];

unsigned longrand(long int max);

/*
 * seqArray()
 *  : (struct elem*) array -- array to modify
 *  : (int) n -- number of elements to modify
 *
 *  This function takes first `n` elements of `array`
 *  and links them together in a sequential order,
 *  i.e.,
 *      array[0].next == array[1]
 *      array[1].next == array[2]
 *      ...
 *      array[n-1].next == array[0]
 */
void seqArray(struct elem* array, int n);

/*
 * ranArray()
 *  : (struct elem*) array -- array to modify
 *  : (int) n -- number of elements to modify
 *
 *  This function takes first `n` elements of `array`
 *  and links them together in a random order,
 *  i.e. (e.g.),
 *      array[0].next == array[5]
 *      array[5].next == array[1]
 *      ...
 *      array[x].next == array[0]
 */
void ranArray(struct elem* array, int n);

/*
 * measureCache()
 *  : (int) mode -- mode of ordering elements in an array
 *  : (int) jumps -- number of pointer "jumps" in the single working
 *                   set measurement
 *
 *  This function makes a measurement of memory access time.
 *  First, it prepares an array (according to selected `mode`).
 *  Then, for every working set size (1 KiB - 4 MiB) it measures
 *  the time of following the links in the array `jumps` times.
 *
 *  The function should print to stdout 'Measurement started'
 *  message. Then, it prints for each measurement the working set
 *  size (in bytes) and the average access time for a single
 *  "jump" (in CPU ticks). At the end the 'Measurement finished'
 *  message is printed.
 *
 *  Example:
 *      Measurement started
 *      1024    22
 *      2048    23
 *      4096    22
 *      Measurement finished
 */
void measureCache(int mode, int jumps);
#endif
