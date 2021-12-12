#include "../include/server_http.h"
#include <stdint.h>
#include "../include/shared.h"
#include "taskLib.h"

void update_statistics() {
	while (1) {
		uint32_t i = (motor_history.array_start_index + HISTORY_SIZE) % HISTORY_CYCLIC_ARRAY_SIZE;
		motor_history.desired_position[i] = motor_driver_shared.desired_position;
		motor_history.position[i] = motor_driver_shared.position;
		motor_history.pwm_duty[i] = motor_driver_shared.pwm_duty;
		motor_history.array_start_index = (motor_history.array_start_index + 1) % HISTORY_CYCLIC_ARRAY_SIZE;
		motor_history.counter++;
		taskDelay(5);
	}
}
