/*
 * Motor.c
 *
 *  Created on: 11/03/2019
 *      Author: Lilia Lobato
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "PIT.h"
#include "NVIC.h"
#include "RGB.h"
#include "Motor.h"
#include "Bits.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY1S (2.0F)
#define DELAY4S (8.0F)
#define MOTOR_REP_TOP 3
#define COUNTERTOP 2	//Num. de ciclos a repetir el encendido

static motor_status flag_motor = MOTOR_ON;
static uint8_t motor_rep = FALSE;
uint8_t pit_inter_counter = COUNTERTOP;

void MOTOR_output_config(gpio_port_name_t portName, uint8_t pin) {
	gpio_pin_control_register_t pin_control_register_bit_d_0 = GPIO_MUX1;
	GPIO_clock_gating(portName);
	GPIO_pin_control_register(portName, pin, &pin_control_register_bit_d_0);
	GPIO_data_direction_pin(portName, GPIO_OUTPUT, pin);
	GPIO_set_pin(portName, pin);
}

void MOTOR_PIT_config1s() {
	PIT_clock_gating();
	PIT_enable();
	NVIC_set_basepri_threshold(PRIORITY_12);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_3);
	NVIC_global_enable_interrupts;
	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY1S);
	PIT_enable_interrupt_0(PIT_0);
}

void MOTOR_fun_3(gpio_port_name_t portName, uint8_t pin) {
	//LED externo
	RGB_estado3(GPIO_C, bit_17, GPIO_C, bit_16);
	//Configuracion GPIO
	MOTOR_output_config(portName, pin);

	GPIO_set_pin(portName, pin);
}

//MOTOR_fun_2(GPIO_D, bit_0, flag_motor, pit_inter_status);
void MOTOR_fun_2(gpio_port_name_t portName, uint8_t pin) {
	//LED externo
	RGB_estado2(GPIO_C, bit_17, GPIO_C, bit_16);

	if (MOTOR_ON == flag_motor) {
		if (MOTOR_REP_TOP == motor_rep) {
			encender_led(COLOR_RED);
			GPIO_clear_pin(portName, pin);
			flag_motor = MOTOR_OFF;
			motor_rep = FALSE;
		} else {
			motor_rep++;
		}
	} else {
		if (MOTOR_REP_TOP == motor_rep) {
			encender_led(COLOR_GREEN);
			GPIO_set_pin(portName, pin);
			flag_motor = MOTOR_ON;
			motor_rep = FALSE;
		} else {
			motor_rep++;
		}
	}

	PIT_clear0_interrupt_flag();
}

void MOTOR_fun_1(gpio_port_name_t portName, uint8_t pin) {
	//LED externo
	RGB_estado1(GPIO_C, bit_17, GPIO_C, bit_16);

	if (MOTOR_ON == flag_motor) {
		encender_led(COLOR_RED);
		GPIO_set_pin(portName, pin);
		flag_motor = MOTOR_OFF;
	} else if (MOTOR_OFF == flag_motor) {
		encender_led(COLOR_GREEN);
		GPIO_clear_pin(portName, pin);
		flag_motor = MOTOR_ON3S;
	} else if (MOTOR_ON3S == flag_motor) {
		if (FALSE == pit_inter_counter) {
			encender_led(COLOR_RED);
			GPIO_set_pin(portName, pin);
			flag_motor = MOTOR_OFF1S;
			pit_inter_counter = COUNTERTOP;
		} else {
			encender_led(COLOR_GREEN);
			GPIO_clear_pin(portName, pin);
			flag_motor = MOTOR_ON3S;
			pit_inter_counter--;
		}
	} else {
		encender_led(COLOR_GREEN);
		GPIO_clear_pin(portName, pin);
		flag_motor = MOTOR_ON;
	}
	PIT_clear0_interrupt_flag();
}

void MOTOR_fun_1_3(gpio_port_name_t portName, uint8_t pin, sw_status SW) {
	if (TRUE == PIT_get0_interrupt_flag_status()) {
		if (SW1 == SW) {
			MOTOR_fun_1(portName, pin);
		} else if (SW2 == SW) {
			MOTOR_fun_2(portName, pin);
		} else if (SW3 == SW) {
			MOTOR_fun_3(portName, pin);
		} else
			{
			MOTOR_fun_3(portName, pin);
			}
	}
}