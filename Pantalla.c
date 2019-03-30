/*
 * Pantalla.c
 *
 *  Created on: 29/03/2019
 *      Author: Lilia Lobato
 */

#include "SPI.h"
#include "GPIO.h"
#include "Bits.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include "stdint.h"
#include "SPI.h"
#include "Delay.h"
#include "Pantalla.h"

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
const uint8_t inicio[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xFC,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xFC, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0,
		0x70, 0x78, 0x38, 0x38, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x38, 0x38,
		0x78, 0x70, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xF8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xFF, 0xFF, 0xFF,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xFF, 0xFF, 0xFF, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7E, 0xFF, 0xFF, 0xCB, 0x09,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0xCB, 0xFF, 0xFF, 0x7E, 0x08, 0x08, 0x08, 0x08, 0xF8,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F,
		0x0E, 0x1E, 0x1C, 0x1C, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x1C, 0x1C,
		0x1E, 0x0E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x7C, 0x3C, 0xF8, 0xF0, 0xC0, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xFF, 0xFF, 0xFF,
		0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
		0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0,
		0xF0, 0xFC, 0x7F, 0x5F, 0x47, 0x41, 0x40, 0x40, 0x40, 0x43, 0x47, 0x5F,
		0x7E, 0xF8, 0xF0, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F,
		0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x1F, 0x1F,
		0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x03, 0x07, 0x0F, 0x1E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, };

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const spi_config_t g_spi_config = { SPI_DISABLE_FIFO, SPI_LOW_POLARITY,
		SPI_LOW_PHASE, SPI_MSB, SPI_0, SPI_MASTER,
		GPIO_MUX2,
		SPI_BAUD_RATE_2,
		SPI_FSIZE_8, { GPIO_D, bit_1, bit_2 } };

//La pantalla tiene MAX_x=83 y un MAX_y=5
uint8_t menu1[] = "1)RGB Manual";
uint8_t menu2[] = "2)RGB ADC";
uint8_t menu3[] = "3)RGB Secue";
uint8_t menu4[] = "4)RGB Frec";

//Prueba valores ADC
uint8_t valor = 23;

void prueba(void) {

	uint8_t string1[] = "ITESO"; //"( ＾◡＾)っ (‿|‿)";
	//"EL SIGUIENTE QUE HABLE..."; /*! String to be printed in the LCD*/
	uint8_t tarea1[] = "EL QUE HABLE";
	uint8_t tarea3[] = "...";
	uint8_t string2[] = "TOTIS"; /*! String to be printed in the LCD*/
	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */

	for (;;) {
		LCD_nokia_clear();/*! It clears the information printed in the LCD*/
		//Despliego de imagen
		LCD_nokia_goto_xy(0, 0);
		LCD_nokia_bitmap(&inicio[0]); /*! It prints an array that hold an image, in this case is the initial picture*/
		delay(65000);
		LCD_nokia_clear();
		delay(65000);
		//Despliego "EL QUE HABLE"
		LCD_nokia_clear();
		LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
		LCD_nokia_send_string(&tarea1[0]); /*! It print a string stored in an array*/
		LCD_nokia_goto_xy(25, 2);
		LCD_nokia_send_string(&tarea3[0]);

		//dESPLEIGO TOTIS
		delay(65000);
		LCD_nokia_goto_xy(25, 2);
		LCD_nokia_send_string(string2); /*! It print a string stored in an array*/
		delay(65000);

	}
}

void pantalla_init() {
	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */
}

void pantalla_main() {
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	//Despliego de imagen
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_bitmap(&inicio[0]); /*! It prints an array that hold an image, in this case is the initial picture*/
}

void pantalla_menu() {
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	//Despliego de imagen
	LCD_nokia_goto_xy(0, 0);
	LCD_nokia_send_string(&menu1[0]);
	LCD_nokia_goto_xy(0, 1);
	LCD_nokia_send_string(&menu2[0]);
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(&menu3[0]);
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&menu4[0]);
}

void pantalla_RGB_Manual() {
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&menu1[0]);
}
void pantalla_RGB_ADC(float Pot){//uint8_t entero, uint8_t decimal) {
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
	//Genera el valor
	uint8_t PotR = (uint8_t) Pot;
	uint8_t PotD0 = (uint8_t) ((Pot-PotR)*10);
	uint8_t PotD1 = (uint8_t) ((Pot-PotR)*100)-(PotD0*10);

	//Desplegar Pantalla
	LCD_nokia_goto_xy(0, 1);
	LCD_nokia_send_string("VOLTAJE");
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_char(intToChar(PotR));
	LCD_nokia_send_char('.');
	LCD_nokia_send_char(intToChar(PotD0));
	LCD_nokia_send_char(intToChar(PotD1));
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string("SW3=ON");
	LCD_nokia_goto_xy(0, 4);
	LCD_nokia_send_string("SW2=OFF");
}
void pantalla_RGB_Secuencial() {

}
void pantalla_RGB_Frecuencia(float Fr) {
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
		//Genera el valor
		uint8_t FrR0 = (uint8_t) Fr/10;
		uint8_t FrR1 = (uint8_t) Fr-(FrR0*10);
		uint8_t FrD0 = (uint8_t) ((Fr-(FrR1+(FrR0*10)))*10);
		uint8_t FrD1 = (uint8_t) ((Fr-(FrR1+(FrR0*10)))*100)-(FrD0*10);

		//Desplegar Pantalla
		LCD_nokia_goto_xy(0, 1);
		LCD_nokia_send_string("FRECUENCIA");
		LCD_nokia_goto_xy(0, 2);
		LCD_nokia_send_char(intToChar(FrR0));
		LCD_nokia_send_char(intToChar(FrR1));
		LCD_nokia_send_char('.');
		LCD_nokia_send_char(intToChar(FrD0));
		LCD_nokia_send_char(intToChar(FrD1));
		LCD_nokia_send_string("KHz");
		LCD_nokia_goto_xy(0, 3);
		LCD_nokia_send_string("SW3=ON");
		LCD_nokia_goto_xy(0, 4);
		LCD_nokia_send_string("SW2=OFF");
}

uint8_t intToChar (uint8_t valor){
	switch (valor){
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	default:
		return '0';
	}
}