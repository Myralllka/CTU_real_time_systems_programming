#ifndef SHARED_H
#define SHARED_H

#include <stdint.h>


typedef struct {
	uint32_t irq_count;
	int32_t position;
	int32_t desired_position;
	int32_t pwm_duty;
} motor_driver_shared_t;

#define HISTORY_SIZE 400
#define HISTORY_CYCLIC_ARRAY_SIZE 600

typedef struct {
	int32_t position[HISTORY_CYCLIC_ARRAY_SIZE];
	int32_t desired_position[HISTORY_CYCLIC_ARRAY_SIZE];
	int32_t pwm_duty[HISTORY_CYCLIC_ARRAY_SIZE];
	uint32_t counter;
	uint32_t array_start_index;
} motor_history_t;

extern motor_driver_shared_t motor_driver_shared;
extern motor_history_t motor_history;

#define SERVER_SEND_DELAY 50
#define CLOCK_RATE 1000
#define MOTOR_DRIVER_PRIOROTY 150
#define UDP_COMMUNICATION_PRIORITY 151
#define HTTP_SERVER_PRIORITY 153
#define STATISTICS_MONITOR_PRIORITY 152

#define DEBUG_OUTPUT
#undef DEBUG_OUTPUT



#endif
