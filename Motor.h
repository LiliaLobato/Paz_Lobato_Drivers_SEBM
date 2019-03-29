/*
 * Motor.h
 *
 *  Created on: 11/03/2019
 *      Author: Lilia Lobato
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include <GPIO.h>

typedef enum {
	MOTOR_ON, MOTOR_OFF, MOTOR_ON3S, MOTOR_OFF1S
} motor_status;
typedef enum {
	SW0, SW1, SW2, SW3
} sw_status;

//Configuracion del puerto de salida para la señal del motor
void MOTOR_output_config(gpio_port_name_t portName, uint8_t pin);

//Configuracion del Pit para las interrupciones
void MOTOR_PIT_config1s();
void MOTOR_PIT_config4s();


//Funcionalidades
void MOTOR_fun_1(gpio_port_name_t portName, uint8_t pin);
void MOTOR_fun_2(gpio_port_name_t portName, uint8_t pin);
void MOTOR_fun_3(gpio_port_name_t portName, uint8_t pin);

//Concurrencia
void MOTOR_fun_1_3(gpio_port_name_t portName, uint8_t pin, sw_status SW);

#endif /* MOTOR_H_ */