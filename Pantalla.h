/*
 * Pantalla.h
 *
 *  Created on: 29/03/2019
 *      Author: Lilia Lobato
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

typedef enum {
	B1, B2, B3, B4, B5, B6
}RGB_Bn;

//inicializacion
void prueba (void);
void pantalla_init(void);
//Pantallas inicio
void pantalla_main(void);
void pantalla_menu(void);
//Pantallas estados
void pantalla_RGB_Manual(void);
void pantalla_RGB_ADC(float Pot);
void pantalla_RGB_Secuencial(RGB_Bn Boton, uint8_t BotonCounter);
void pantalla_RGB_Frecuencia(float Fr);

//funciones backend
uint8_t intToChar (uint8_t valor);
#endif /* PANTALLA_H_ */
