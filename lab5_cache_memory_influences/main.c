#include "config.h"

struct elem global_array[MAX_ARRAY_LEN];
unsigned random_indexes[MAX_ARRAY_LEN];

/* generate long random number */
unsigned longrand(long int max) {
#if RAND_MAX == 32767
	  return (rand() ^ (rand() << 15)) % max;
#else
	    #error Unsupported RAND_MAX value
#endif
}

/* generate sequential array */
void seqArray(struct elem* array, int n) {
	unsigned i;
	for (i = 0; i < n - 1; i++) {
		array[i].next = &array[i+1];
	}
	array[i].next = &array[0];   /* close the cycle */
}

/* generate random array */
void ranArray(struct elem* array, int n) {
	unsigned idx, tmp;
	unsigned i;
	for (i = 0; i < n; ++i) {
		random_indexes[i] = i;
	}
	for (i = 0; i < n; ++i) {
		idx = longrand(n);
		tmp = random_indexes[i];
		random_indexes[i] = random_indexes[idx];
		random_indexes[idx] = tmp;
	}
	for (i = 0; i < n - 1; i++) {
		array[random_indexes[i]].next = &array[random_indexes[i+1]];
	}
	
	/* close the cycle */
	array[random_indexes[i]].next = &array[random_indexes[0]];
}

unsigned measurement(struct elem* array, int jumps) {
	struct elem *p = &array[0];
	unsigned start = sysTimestamp();
	while (--jumps) p = p->next;
	unsigned end = sysTimestamp();
	
	return end - start;
}

void measureCache(int mode, int jumps) {
	sysClkRateSet(CLOCK_RATE);

	unsigned i, measure_result;
	printf("%s\n", "Measurement started");
	for (i = 1024; i <= MAX_ARRAY_LEN; i <<= 1) {
		if (mode == SEQUENTIAL) {
			ranArray(global_array, i);
		} else if (mode == RANDOM) {
			ranArray(global_array, i);		
		} else return;
		seqArray(global_array, i);

		measure_result = measurement(global_array, i);
		printf("%lu\t\t%lu\n", i, measure_result);
	}
	printf("%s\n", "Measurement finished");
}

