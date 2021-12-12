#include "../include/stepper_motor.h"
#include <taskLib.h>
#include <stdio.h>
#include <kernelLib.h>
#include <semLib.h>
#include <intLib.h>
#include <iv.h>
#include <xlnx_zynq7k.h>
#include <stdbool.h>
#include "../include/shared.h"
#include <math.h>

#define TRANSITION(old, new) (((old) << 2) | new)

static const int TRANSITION_TABLE[16] = {
          [TRANSITION(0,1)] = +1,
          [TRANSITION(1,3)] = +1,
          [TRANSITION(3,2)] = +1,
          [TRANSITION(2,0)] = +1,
  
          [TRANSITION(1,0)] = -1,
          [TRANSITION(3,1)] = -1,
          [TRANSITION(2,3)] = -1,
          [TRANSITION(0,2)] = -1,
};

static SEM_ID sem_motor_pwm_change;
static uint8_t motor_state, prev_motor_state;
static bool set_position_to_desired;

/*!
 * \brief Set duty cycle in percentage
 * Set duty cycle for controlling the motor to the values from -100 to 100,
 * where -100 means max speed backwards, 100 means max speed forward, 0 means no movement and so on
 * @param duty_cycle_percent : desired percentage of duty cycle (from -100 to 100)
 */
static inline void set_motor_dutycycle(int8_t duty_cycle_percent) 
{
	if (duty_cycle_percent < -100 || duty_cycle_percent > 100) 
	{
		return;
	}
	if (duty_cycle_percent < 0) 
	{
		PWM_DUTY_CR = ((1 << DUTY_DIR_R) | (((PWM_PERIOD * -duty_cycle_percent) / 100) << DUTY_CYCLE));
	} 
	else 
	{
		PWM_DUTY_CR = ((1 << DUTY_DIR_F) | (((PWM_PERIOD * duty_cycle_percent) / 100) << DUTY_CYCLE));
	}
}

/*!
 * \brief Get new PWM value from the distance between desired and real position
 * @param distance: distance in steps between the desired and real position
 * @return new PWM value in range (-100, 100)
 */
static inline int8_t get_pwm(int32_t distance) {
	int8_t pwm = min(max(((distance * abs(distance)) >> 7), -100), 100);
	if (pwm < 0 && pwm > -MIN_PWM_DUTY) {
		return -MIN_PWM_DUTY;
	} else if (pwm > 0 && pwm < MIN_PWM_DUTY) {
		return MIN_PWM_DUTY;
	} else {
		return pwm;
	}
}

/*!
 * \brief Motor interrupt handler
 * Interrupt handler for handling intrrupts on the stepper motor phase change
 */
void motor_isr(void)
{
        uint8_t irc_a = (MOTOR_SR & BIT(MOTOR_SR_IRC_A_MON)) ? 1 : 0;
        uint8_t irc_b = (MOTOR_SR & BIT(MOTOR_SR_IRC_B_MON)) ? 2 : 0;
        
        prev_motor_state = motor_state;
        motor_state = irc_a | irc_b;
        motor_driver_shared.position += TRANSITION_TABLE[TRANSITION(prev_motor_state, motor_state)];              
        motor_driver_shared.irq_count++;
        
        if (set_position_to_desired)
        	set_motor_dutycycle(get_pwm(motor_driver_shared.desired_position - motor_driver_shared.position));   
       
        GPIO_INT_STATUS = MOTOR_IRQ_PIN; /* clear the interrupt */
}

/*!
 * \brief Initialize the step motor
 */
void motor_init(void)
{
		motor_driver_shared.position = 0;
		motor_driver_shared.irq_count = 0;
	
        GPIO_INT_STATUS = MOTOR_IRQ_PIN; /* reset status */
        GPIO_DIRM = 0x0;                 /* set as input */
        GPIO_INT_TYPE = MOTOR_IRQ_PIN;   /* interrupt on edge */
        GPIO_INT_POLARITY = 0x0;         /* falling edge */
        GPIO_INT_ANY = 0x0;              /* ignore rising edge */
        GPIO_INT_ENABLE = MOTOR_IRQ_PIN; /* enable interrupt on MOTOR_IRQ pin */
        
        PWM_PERIOD_REGISTER = PWM_PERIOD; // Set PWM period to 20 kHz 
        MOTOR_CR = (1 << MOTOR_CR_PWM_ENABLE); // Enable PWM by default
        PWM_DUTY_CR = 0; // No PWM for now
        
        bool irc_a = (MOTOR_SR & BIT(MOTOR_SR_IRC_A_MON)) != 0;
        bool irc_b = (MOTOR_SR & BIT(MOTOR_SR_IRC_B_MON)) != 0;
        
        // TODO: check if this is ok with bools here
        motor_state =  irc_a | (irc_b << 1);
     
        intConnect(INUM_TO_IVEC(INT_LVL_GPIO), motor_isr, 0);
        intEnable(INT_LVL_GPIO);         /* enable all GPIO interrupts */
}

/*!
 * \brief interrupt handler and registers
 */
void motor_cleanup(void)
{
        GPIO_INT_DISABLE = MOTOR_IRQ_PIN;
        intDisable(INT_LVL_GPIO);
        intDisconnect(INUM_TO_IVEC(INT_LVL_GPIO), motor_isr, 0);
}

/*!
 * \brief Entry point to the DKM
 * @param set_desired : true if the driver should set position of the motor and not just monitor values
 */
void motor(bool set_desired)
{        
		set_position_to_desired = set_desired;
        // Init semaphore for changing PWM duty requests
        sem_motor_pwm_change = semOpen("/sem_motor_pwm_change", SEM_TYPE_COUNTING, SEM_EMPTY, SEM_Q_FIFO, OM_CREATE, NULL);

        motor_init();
        
        while (1)
        {
        	// Wait for the request to recalculate the duty cycle
            semTake(sem_motor_pwm_change, WAIT_FOREVER);
            if (set_desired) {
            	// Disable interrupts to prevent data race (when interrupt handler sets duty cycle too)
            	intDisable(INT_LVL_GPIO);
            	set_motor_dutycycle(get_pwm(motor_driver_shared.desired_position - motor_driver_shared.position));
            	intEnable(INT_LVL_GPIO);
            }
        }
        
        semClose(sem_motor_pwm_change);
        motor_cleanup();
}
