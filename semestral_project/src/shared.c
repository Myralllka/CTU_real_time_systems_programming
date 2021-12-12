#include "../include/shared.h"

motor_driver_shared_t motor_driver_shared = {
		.desired_position = 0,
		.irq_count = 0,
		.position = 0,
		.pwm_duty = 0
};

motor_history_t motor_history = {
		.array_start_index = 0,
		.counter = 0
};
