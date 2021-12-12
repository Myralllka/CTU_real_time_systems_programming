#include "../include/shared.h"
#include "../include/server.h"
#include "../include/stepper_motor.h"
#include "taskLib.h"
#include "../include/server_http.h"


void create_tasks(bool transmiter, char *ip_address) {
	sysClkRateSet(CLOCK_RATE);
	
	printf("%d\n", sizeof(motor_history.desired_position));
	memset(motor_history.desired_position, 0, sizeof(motor_history.desired_position));
	memset(motor_history.position, 0, sizeof(motor_history.position));
	memset(motor_history.pwm_duty, 0, sizeof(motor_history.pwm_duty));
	
	taskSpawn("tMotor_driver", MOTOR_DRIVER_PRIOROTY, 0, 4096, (FUNCPTR)motor, !transmiter, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	taskSpawn("tUDP_server", UDP_COMMUNICATION_PRIORITY, 0, 4096, (FUNCPTR)run_udp_srv, (_Vx_usr_arg_t)ip_address, DEFAULT_PORT, 0, 0, 0, 0, 0, 0, 0, 0);
	
	if (!transmiter) {
		taskSpawn("tHTTP_server", HTTP_SERVER_PRIORITY, VX_FP_TASK, 16384 * 4, (FUNCPTR)run_http_srv, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		taskSpawn("tStatistics_monitor", STATISTICS_MONITOR_PRIORITY, 0, 4096, (FUNCPTR)update_statistics, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	
		
}
