#include <taskLib.h>

#include "../include/shared.h"
#include "../include/server.h"
#include "../include/stepper_motor.h"
#include "../include/server_http.h"

/*!
 * \brief Main function of our project
 * Create tasks - function for tasks creation, setting all parameters and spawning.
 * Main entry point in a whole project for both modes.
 * @param transmiter - bool -  flag for differentiation between two modes - receiver and transmitter
 * @param ip_address - char* - ip address of the UDP receiver or NULL if the board is receiver itself
 */
void create_tasks(bool transmiter, char *ip_address) {
	sysClkRateSet(CLOCK_RATE);
	sysTimestampEnable();
	motor_history.timestamp_start = sysTimestamp();

	printf("%lu\n", sizeof(motor_history.desired_position));
    // setting all arrays to zero, because we are reading from them
	memset(motor_history.desired_position, 0, sizeof(motor_history.desired_position));
	memset(motor_history.position, 0, sizeof(motor_history.position));
	memset(motor_history.pwm_duty, 0, sizeof(motor_history.pwm_duty));

	taskSpawn("tMotor_driver", MOTOR_DRIVER_PRIOROTY, 0, 4096, (FUNCPTR)motor, !transmiter, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	taskSpawn("tUDP_server", UDP_COMMUNICATION_PRIORITY, 0, 4096, (FUNCPTR)run_udp_srv, (_Vx_usr_arg_t)ip_address, DEFAULT_PORT, 0, 0, 0, 0, 0, 0, 0, 0);

	if (!transmiter) {
		taskSpawn("tHTTP_server", HTTP_SERVER_PRIORITY, 0, 16384 * 4, (FUNCPTR)run_http_srv, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		taskSpawn("tStatistics_monitor", STATISTICS_MONITOR_PRIORITY, 0, 4096, (FUNCPTR)update_statistics, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}
