#include "config.h"

#define TIME_MAP_SIZE 20
/* Semaphore that is passed between `timer_isr` and Service task. */
SEM_ID isr_semaphore;

int m_end = 0;
uint32_t m_time_isr_map[TIME_MAP_SIZE];
uint32_t m_time_srv_map[TIME_MAP_SIZE];


/*
 * timer_isr()
 *
 *  This function is attached to timer as an interrupt handler.
 *  On every call, this function reads and stores the timer value
 *  and releases `isr_semaphore`.
 */
void timer_isr(void) {
	// m_tim_value_service =  TTC0_TIMER2_COUNTER_VAL * 36ns / 1000 (ms)
	uint32_t time = (TTC0_TIMER2_COUNTER_VAL * 36) / 1000;
	if (time < TIME_MAP_SIZE) ++m_time_isr_map[time];
	semGive(isr_semaphore);
	
	// read ISR register to clear interrupt (see TRM B.32)
	TTC0_TIMER2_INTERRUPT;

}


/*
 * ServiceTask()
 *  : (int) o -- "optional" argument, you can use it freely if you want to
 *
 *  This function is spawned as a Service task with name `tService`.
 *
 *  Service task is running in a loop, waiting for `isr_semaphore`
 *  to be unlocked. After successfully taking this semaphore, timer
 *  value is read and stored.
 */
void ServiceTask(int o) {
	while (! m_end) {
		semTake(isr_semaphore, WAIT_FOREVER);
		uint32_t time = (TTC0_TIMER2_COUNTER_VAL * 36) / 1000;
		if (time < TIME_MAP_SIZE) ++m_time_srv_map[time];
	}
}

/*
 * MonitorTask()
 *  : (int) o -- "optional" argument, you can use it freely if you want to
 *
 *  This function is spawned as a Monitor task with name `tMonitor`.
 *
 *  Monitor task is running in a loop, printing out measurement data
 *  from both `timer_isr` and Service task. After printing, task is
 *  suspended for 1 second.
 *
 *  Data format:
 *  The functions prints out three rows every time:
 *   1) First row is the x-axis, values in microseconds, ordered in a strictly
 *      increasing sequence.
 *   2) Second row is histogram for "interrupt--timer_isr" latency. The sequence
 *      has the same size as first row (number of elements) and the values
 *      correspond to the x-axis (number of occurences of given latency).
 *   3) Third row is histogram for "interrupt--ServiceTask" latency. The rest is
 *      same as the second row.
 *   Printed out values are delimited by comma ',' only. Rows are ended with '\n'.
 */
void MonitorTask(int measurements) {
	int i = 0, j;
	printf("%s\n", "Measurement started");
//	for (i = 0; i < measurements; ++i) {
	while (measurements == 0 || measurements != i) {
		// delay for 1 sec
		taskDelay(BREAK_TIME);
		char c;
		for (j = 0; j < TIME_MAP_SIZE; ++j) {
			printf("%i", j);
			c = (j + 1 == TIME_MAP_SIZE) ? '\n' : ',';
			printf("%c", c);
		}
		for (j = 0; j < TIME_MAP_SIZE; ++j) {
			printf("%i", m_time_isr_map[j]);
			c = (j + 1 == TIME_MAP_SIZE) ? '\n' : ',';
			printf("%c", c);
		}
		for (j = 0; j < TIME_MAP_SIZE; ++j) {
			printf("%i", m_time_srv_map[j]);
			c = (j + 1 == TIME_MAP_SIZE) ? '\n' : ',';
			printf("%c", c);
		}
		++i;

	}
	printf("%s\n", "Measurement finished");
	
	m_end = 1;
	
	TTC0_TIMER2_COUNTER_CTRL = CTRL_DIS;
	intDisable(INT_LVL_TTC0_2);
	intDisconnect((VOIDFUNCPTR *) INT_VEC_TTC0_2, timer_isr, 0);
	
}

/*
 * CreateTasks()
 *  : (int) seconds -- how many seconds should the measurement last
 *
 *
 *  Entry point function.
 *
 *  This function makes a measurement of interrupt latency.
 *  First, it prepares registers of the hardware and links
 *  `timer_isr` function as an interrupt handler.
 *  Then, Service and Monitor tasks are spawned.
 *
 *  Whole application (that is, after running this function),
 *  should print to stdout 'Measurement started' message. Then,
 *  every 1 second measurement data are printed. At the end,
 *  after `seconds` seconds have passed, the 'Measurement finished'
 *  message is printed and application is terminated (all tasks deleted,
 *  and interrupt is disabled + disconnected).
 *
 *  Note:
 *  See Monitor task for more information about the measurement data
 *  format.
 *
 *  Example:
 *      -> CreateTasks(1)
 *      Measurement started
 *      0,1,2,3,4,5,6,7
 *      59,984,34,0,45,3,784,35
 *      0,0,0,0,0,13,1159,772
 *      Measurement finished
 *
 *      -> CreateTasks(2)
 *      Measurement started
 *      0,1,2,3,4,5,6,7
 *      59,984,34,0,45,3,784,35
 *      0,0,0,0,0,13,1159,772
 *      0,1,2,3,4,5,6,7
 *      147,1751,134,5,85,13,997,80
 *      0,0,0,0,0,30,1909,1273
 *      Measurement finished
 */

void CreateTasks(int measurements) {
	sysClkRateSet(CLOCK_RATE);
	int j;
	for (j = 0; j < TIME_MAP_SIZE; ++j) {
		m_time_srv_map[j] = 0;
		m_time_isr_map[j] = 0;
	}
	
	isr_semaphore = semCCreate(0, 0);
	// timer init (see TRM 8.5.5)
	TTC0_TIMER2_COUNTER_CTRL = CTRL_DIS;
	TTC0_TIMER2_CLOCK_CTRL = CLOCK_PRESCALE | CLOCK_PRESCALE_EN;
	TTC0_TIMER2_INTERVAL = TIM_MAX; // See "Choosing the timer period" below
	TTC0_TIMER2_INTERRUPT_EN = INTERRUPT_EN_IV;

	TTC0_TIMER2_COUNTER_CTRL = CTRL_INT | CTRL_EN;

	intConnect((VOIDFUNCPTR *) INT_VEC_TTC0_2, timer_isr, 0);
	intEnable(INT_LVL_TTC0_2);
	
	int srv = taskSpawn("tService", 210, 0, 4096, (FUNCPTR) ServiceTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	taskSpawn("tMonitor", 210, 0, 4096, (FUNCPTR) MonitorTask, measurements, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	while(!m_end){};
	taskDelete(srv);
}
