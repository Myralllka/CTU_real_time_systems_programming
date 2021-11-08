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

	for (unsigned i = 0; i < n; ++i) {
		random_indexes[i] = i;
	}
	for (unsigned i = 0; i < n; ++i) {
		idx = longrand(n);
		tmp = random_indexes[i];
		random_indexes[i] = random_index[idx];
		random_indexes[idx] = tmp;
	}

	for (unsigned i = 0; i < n - 1; ++i) {
		idx = random_indexes[i];
		array[idx].next = &array[idx + 1];
	}

	/* close the cycle */
	array[random_indexes[i]].next = &array[random_indexes[0]];
}

void measurement(struct elem* array, int jumps) {
	struct elem *p = &array[0];
	unsigned start = sysTimestamp();
	while (--jumps) p = p->next;
	unsigned end = sysTimestamp();

}

void measureCache(int mode, int jumps) {
	sysClkRateSet(CLOCK_RATE);

	if (mode == SEQUENTIAL) {
		
	} else if (mode == RANDOM) {
		
	} else return;

	printf("%s\n", "Measurement started");
	for (unsigned i = 1024; i <= 1048576; i <<= 1) {
		
		printf("%zu\t\t%zu", );
	}
	printf("%s\n", "Measurement finished");
}

