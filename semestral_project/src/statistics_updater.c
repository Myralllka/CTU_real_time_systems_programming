#include "../include/server_http.h"
#include <stdint.h>
#include "../include/shared.h"
#include <taskLib.h>
#include <sysLib.h>
#include <stdio.h>

/*!
 * Entry point of task that contonuously updates motor history statistics
 *
 * Written using Ostrich algorithm - we ignore data race in this function
 * Obviously it can happen (somewhere on the bounds) and we realise it
 * But to use mutex/semaphore here will be a huge overhead for the whole system.
 */
void update_statistics() {
	uint32_t prev_timestamp = sysTimestamp(), cur_timestamp;
	uint64_t timestamp64 = 0;

    while (1) {
    	cur_timestamp = sysTimestamp();
    	timestamp64 += cur_timestamp - prev_timestamp;
    	prev_timestamp = cur_timestamp;
    	
        uint32_t i = (motor_history.array_start_index + HISTORY_SIZE) % HISTORY_CYCLIC_ARRAY_SIZE;
        motor_history.desired_position[i] = motor_driver_shared.desired_position;
        motor_history.position[i] = motor_driver_shared.position;
        motor_history.pwm_duty[i] = motor_driver_shared.pwm_duty;
        motor_history.timestamp[i] = (timestamp64 * 1000) / sysTimestampFreq();
        
        motor_history.array_start_index = (motor_history.array_start_index + 1) % HISTORY_CYCLIC_ARRAY_SIZE;
        taskDelay(3);
    }
}
