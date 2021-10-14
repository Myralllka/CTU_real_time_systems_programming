#include <taskLib.h>
#include <stdio.h>
#include <kernelLib.h>
#include <semLib.h>

#define WORK_TIME 50
#define BREAK_TIME 50

SEM_ID semShovels;
SEM_ID semSoilHeap;

		
const int MAX_NUM_OF_DIGGERS = 50;
const int SHOVELS = 3;
int l_diggers_count = 0;
int u_diggers_count = 0;
int l_diggers_ids[50];
int u_diggers_ids[50];
int i = 0;

void digger_in_hole(int n)
{
  printf("lower digger %d: arriving\n", n);
  while (1) {
	taskSafe();
    semTake(semShovels, WAIT_FOREVER);
    
    printf("lower digger %d: working\n", n);
    taskDelay(WORK_TIME);
    semGive(semSoilHeap);
    semGive(semShovels);
    taskUnsafe();
    printf("lower digger %d: resting\n", n);
    taskDelay(BREAK_TIME);
  }
}

void digger_up_the_hole(int n)
{
  printf("upper digger %d: arriving\n", n);
  while (1) {
	semTake(semSoilHeap, WAIT_FOREVER);
	taskSafe();
	int errcode = semTake(semShovels, 10);
	if (errcode == ERROR){
		semGive(semSoilHeap);
		taskUnsafe();
		continue;
	}
	printf("upper digger %d: working\n", n);
    taskDelay(WORK_TIME);
    semGive(semShovels);
    taskUnsafe();
    printf("upper digger %d: resting\n", n);
    taskDelay(BREAK_TIME);
  }
}

int create_lower(int i){
	char taskName[11];
	sprintf(taskName, "tWorkerL%d", i);
	
	return taskSpawn(taskName, 210, 0, 4096, (FUNCPTR) digger_in_hole, i, 0, 0, 0, 0, 0, 0, 0, 0, 0);	
}

int create_upper(int i) {
	char taskName[11];
	sprintf(taskName, "tWorkerU%d", i);
	
	return taskSpawn(taskName, 210, 0, 4096, (FUNCPTR) digger_up_the_hole, i, 0, 0, 0, 0, 0, 0, 0, 0, 0);	
}

void CreateTasks(void){
	semShovels = semCCreate(SEM_Q_FIFO, SHOVELS);
	semSoilHeap = semCCreate(SEM_Q_FIFO, 0);
	l_diggers_ids[l_diggers_count] = create_lower(l_diggers_count);
	++l_diggers_count;
	u_diggers_ids[u_diggers_count] = create_upper(u_diggers_count);
	++u_diggers_count;
	while (1) {
		switch getchar() {
			case 'i': 
				if (l_diggers_count >= MAX_NUM_OF_DIGGERS) break;
				l_diggers_ids[l_diggers_count] = create_lower(l_diggers_count);
				++l_diggers_count;
				break;
			case 'I': 
				if (l_diggers_count >= MAX_NUM_OF_DIGGERS) break;
				u_diggers_ids[u_diggers_count] = create_upper(u_diggers_count);
				++u_diggers_count;
				break;
			case 'o': 
				if (l_diggers_count == 0) break;
				printf("lower digger %d: leaving\n", l_diggers_count - 1);
				taskDelete(l_diggers_ids[l_diggers_count - 1]);
				l_diggers_count--;
				break;
			case 'O': 
				if (u_diggers_count == 0) break;
				printf("upper digger %d: leaving\n", u_diggers_count - 1);
				taskDelete(u_diggers_ids[u_diggers_count - 1]);
				u_diggers_count--;
				break;
			case 'E': 
				for (i = 0; i < l_diggers_count; ++i) {
					taskDelete(l_diggers_ids[i]);
					printf("lower digger %d: leaving\n", i);
				}
				for (i = 0; i < u_diggers_count; ++i) {
					taskDelete(u_diggers_ids[i]);
					printf("upper digger %d: leaving\n", i);
				}
				u_diggers_count = 0;
				l_diggers_count = 0;
				break;
			default:
				continue;
		}
	}
}
