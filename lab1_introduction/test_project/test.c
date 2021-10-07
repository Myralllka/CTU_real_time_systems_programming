#include <taskLib.h>
#include <stdio.h>
#include <kernelLib.h>

long int task_run[]={100, 450, 200};
int task_stop[]={18, 25, 30};

void task(int n)
{
        long int x;

        printf("Task %i has been or not been =) \n", n);

        while (1)
        {
                printf("task %d: running\n", n);
                x = 1000000 * task_run[n];
                while (x > 0) x--;
                printf("task %d: stopped\n", n);
                taskDelay(task_stop[n]);
        }
}

void CreateTasks(void)
{
        int id1, id2, id3;

        kernelTimeSlice(0); 

        id1=taskSpawn("Task0", 210, 0, 4096, (FUNCPTR) task, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        id2=taskSpawn("Task1", 210, 0, 4096, (FUNCPTR) task, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        id3=taskSpawn("Task2", 210, 0, 4096, (FUNCPTR) task, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
