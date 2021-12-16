#ifndef SHARED_H
#define SHARED_H

#include <stdint.h>

/// Delay between sending motor position over UDP [ticks]
#define SERVER_SEND_DELAY 20
/// System clock rate [Hz]
#define CLOCK_RATE 1000
#define MOTOR_DRIVER_PRIOROTY 100
#define UDP_COMMUNICATION_PRIORITY 151
#define HTTP_SERVER_PRIORITY 153
#define STATISTICS_MONITOR_PRIORITY 152

/// Number of values in cyclic arrays (without gap)
#define HISTORY_SIZE 800
/// Actual size of cyclic arrays. Should be greater than HISTORY_SIZE
#define HISTORY_CYCLIC_ARRAY_SIZE 1200


/// Structure for storing shared data with motor driver
typedef struct {
    uint32_t irq_count; 		///< Number of interrupts handled
    int32_t  position; 			///< Absolute position of the motor
    int32_t  desired_position; 	///< Desired position of the motor
    int32_t  pwm_duty; 			///< Current PWM duty cycle
} motor_driver_shared_t;


/// Structure for storing the hostiry of motor_driver_shared_t
typedef struct {
    int32_t  position[HISTORY_CYCLIC_ARRAY_SIZE]; 			///< cyclic array storing absolute position of the motor
    int32_t  desired_position[HISTORY_CYCLIC_ARRAY_SIZE]; 	///< cyclic array storing desired position of the motor
    int32_t  pwm_duty[HISTORY_CYCLIC_ARRAY_SIZE]; 			///< cyclic array storing PWM duty cycle hitory
    uint32_t timestamp[HISTORY_CYCLIC_ARRAY_SIZE]; 			///< array storing corresponding timestamps
    uint32_t timestamp_start; 								///< Application start timestamp
    uint32_t array_start_index; 							///< Start index in cyclic arrays of this structure
} motor_history_t;

extern motor_driver_shared_t motor_driver_shared;
extern motor_history_t motor_history;

#define DEBUG_OUTPUT
#undef DEBUG_OUTPUT


#endif
