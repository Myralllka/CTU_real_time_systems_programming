#include "utils.h"

int end = 0;
int num_of_mes = 0;

void CreateTasks(int a1, int a2) {
	
	// for one core execution
	cpuset_t affinity;
	
	/* 	passing value 1 runs the tasks without priority inheritance,
		passing value 2 runs the tasks with priority inheritance, and
		passing other values terminates the application.*/
	
	if (a1 == 1)
		global_mutex = semMCreate(0);
	else if (a1 == 2)
		global_mutex = semMCreate(SEM_INVERSION_SAFE|SEM_Q_PRIORITY);
	else return;
	// The second parameter configures the number of measurements.
	num_of_mes = a2;
	
	sysClkRateSet(CLOCK_RATE);

	TASK_ID low, middle, high;
	
	/* Create the task but only activate it after setting its affinity */
	low = taskCreate("tLPrio", LOW_PRIORITY, 0, 4096, (FUNCPTR) tLPrio, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	middle = taskCreate("tMPrio", MID_PRIORITY, 0, 4096, (FUNCPTR) tMPrio, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	high = taskCreate("tHPrio", HIGH_PRIORITY, 0, 4096, (FUNCPTR) tHPrio, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	if (low == TASK_ID_ERROR || middle == TASK_ID_ERROR || high == TASK_ID_ERROR)
	    return;
	
	// for one core execution
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
	taskActivate(low);
	taskActivate(middle);
	taskActivate(high);
	
	return;
}
