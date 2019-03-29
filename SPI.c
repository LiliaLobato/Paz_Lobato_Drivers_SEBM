/*
 * SPI.c
 *
 *  Created on: 20/03/2019
 *      Author: Equipo alfa buena maravilla onda dinamita escuadrón lobo
 */

//MCCR -> Module Configuration Register
//CTAR -> Clock and Transfer Attributes Register
//PUSHR -> Specifies data to be transferred to the TX FIFO
#include "SPI.h"

/*it enable the clock module of the SPI by modifying the MDIS bits*/
static void SPI_enable(spi_channel_t channel) {
	switch (channel) {
	case SPI_0:
		SPI0->MCR &= ~SPI_MCR_MDIS_MASK; //Enables the module clocks
		break;
	case SPI_1:
		SPI1->MCR &= ~SPI_MCR_MDIS_MASK; //Enables the module clocks
		break;
	case SPI_2:
		SPI2->MCR &= ~SPI_MCR_MDIS_MASK; //Enables the module clocks
		break;
	default:
		break;
	}
}

/*It activate the clock gating*/
static void SPI_clk(spi_channel_t channel) {
	switch (channel) {
	case SPI_0:
		SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK; //Clock gating for PIT 0
		break;
	case SPI_1:
		SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK; //Clock gating for PIT 1
		break;
	case SPI_2:
		SIM->SCGC3 |= SIM_SCGC3_SPI2_MASK; //Clock gating for PIT 2
		break;
	default:
		break;
	}
}

/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave) {
	if (SPI_MASTER == masterOrSlave) {
		switch (channel) {
		case SPI_0:
			SPI0->MCR |= SPI_MCR_MSTR_MASK; //Master Mode
			break;
		case SPI_1:
			SPI1->MCR |= SPIx_MCR_MSTR_MASK; //Master Mode
			break;
		case SPI_2:
			SPI2->MCR |= SPIx_MCR_MSTR_MASK; //Master Mode
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_MSTR_MASK; //Slave Mode
			break;
		case SPI_1:
			SPI1->MCR &= ~SPIx_MCR_MSTR_MASK; //Slave Mode
			break;
		case SPI_2:
			SPI2->MCR &= ~SPIx_MCR_MSTR_MASK; //Slave Mode
			break;
		default:
			break;
		}
	}
}

/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable) {
	if (SPI_DISABLE_FIFO == enableOrDisable) {
		switch (channel) {
		case SPI_0:
			//Disable
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK); //Disable RX (data in)
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK); //Disable TX (data out)
			break;
		case SPI_1:
			//Disable
			SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK); //Disable RX (data in)
			SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK); //Disable TX (data out)
			break;
		case SPI_2:
			//Disable
			SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK); //Disable RX (data in)
			SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK); //Disable TX (data out)
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			//Enable
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK; //Enable RX (data in)
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; //Enable TX (data out)
			break;
		case SPI_1:
			//Enable
			SPI1->MCR |= SPI_MCR_DIS_RXF_MASK; //Enable RX (data in)
			SPI1->MCR |= SPI_MCR_DIS_TXF_MASK; //Enable TX (data out)
			break;
		case SPI_2:
			//Enable
			SPI2->MCR |= SPI_MCR_DIS_RXF_MASK; //Enable RX (data in)
			SPI2->MCR |= SPI_MCR_DIS_TXF_MASK; //Enable TX (data out)
			break;
		default:
			break;
		}
	}
}

/*It selects the clock polarity depending on the value of cpol*/
static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol) {
	if (SPI_HIGH_POLARITY == cpol) {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK; //Clock polarity is high
			break;
		case SPI_1:
			SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK; //Clock polarity is high
			break;
		case SPI_2:
			SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK; //Clock polarity is high
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] &= ~SPI_CTAR_CPOL_MASK; //Clock polarity is low
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~SPI_CTAR_CPOL_MASK; //Clock polarity is low
			break;
		case SPI_2:
			SPI2->CTAR[0] &= ~SPI_CTAR_CPOL_MASK; //Clock polarity is low
			break;
		default:
			break;
		}
	}
}

/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize) {
	switch (channel) {
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK); // limpiar el campo frame
		SPI0->CTAR[0] |= frameSize;
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK); // limpiar el campo frame
		SPI1->CTAR[0] |= frameSize;
		break;
	default:
		SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK); // limpiar el campo frame
		SPI2->CTAR[0] |= frameSize;
		break;
	}
}

/*It selects the clock phase depending on the value of cpha*/
static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha) {
	if (SPI_HIGH_PHASE == cpha) {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK; //Clock phase is high
			break;
		case SPI_1:
			SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK; //Clock phase is high
			break;
		case SPI_2:
			SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK; //Clock phase is high
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] &= ~SPI_CTAR_CPHA_MASK; //Clock phase is low
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~SPI_CTAR_CPHA_MASK; //Clock phase is low
			break;
		case SPI_2:
			SPI2->CTAR[0] &= ~SPI_CTAR_CPHA_MASK; //Clock phase is low
			break;
		default:
			break;
		}
	}
}

/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate) {
	//The baud rate is the frequency of the SCK(Serial clock)
	switch (channel) {
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_BR_MASK); //Baud Rate Scaler, 2
		SPI0->CTAR[0] |= SPI_CTAR_BR(baudRate); //Chose other BR
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_BR_MASK); //Baud Rate Scaler, 2
		SPI1->CTAR[0] |= SPI_CTAR_BR(baudRate); //Chose other BR
		break;
	case SPI_2:
		SPI2->CTAR[0] &= ~(SPI_CTAR_BR_MASK); //Baud Rate Scaler, 2
		SPI2->CTAR[0] |= SPI_CTAR_BR(baudRate); //Chose other BR
		break;
	default:
		break;
	}
}

/*It selects if MSB or LSM bits is first transmitted*/
static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb) {
	if (SPI_LSM == msb) {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK; //Data is transmited LSB first.
			break;
		case SPI_1:
			SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK; //Data is transmited LSB first.
			break;
		case SPI_2:
			SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK; //Data is transmited LSB first.
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK; //Data is transmited MSB first.
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK; //Data is transmited MSB first.
			break;
		case SPI_2:
			SPI2->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK; //Data is transmited MSB first.
			break;
		default:
			break;
		}
	}
}

/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_start_tranference(spi_channel_t channel) {
	switch (channel) {
	case SPI_0:
		SPI0->MCR &= ~SPI_MCR_HALT_MASK; //Start transfers
		break;
	case SPI_1:
		SPI1->MCR &= ~SPI_MCR_HALT_MASK; //Start transfers
		break;
	case SPI_2:
		SPI2->MCR &= ~SPI_MCR_HALT_MASK; //Start transfers
		break;
	default:
		break;
	}
}

/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel) {
	switch (channel) {
	case SPI_0:
		SPI0->MCR |= SPI_MCR_HALT_MASK; //Stop transfers
		break;
	case SPI_1:
		SPI1->MCR |= SPI_MCR_HALT_MASK; //Stop transfers
		break;
	case SPI_2:
		SPI2->MCR |= SPI_MCR_HALT_MASK; //Stop transfers
		break;
	default:
		break;
	}
}

/*It transmits the information contained in data*/
void SPI_send_one_byte(uint8_t Data) {
	SPI0->PUSHR = (Data);
	while (0 == (SPI0->SR & SPI_SR_TCF_MASK))
		;
	SPI0->SR = SPI_SR_TCF_MASK;
}

/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const spi_config_t* g_spi_config) {
	SPI_clk(g_spi_config->spi_channel);

	//GPIO port configuration
	GPIO_clock_gating(g_spi_config->spi_gpio_port.gpio_port_name);
	GPIO_pin_control_register(g_spi_config->spi_gpio_port.gpio_port_name,
			g_spi_config->spi_gpio_port.spi_clk, &(g_spi_config->pin_config));
	GPIO_pin_control_register(g_spi_config->spi_gpio_port.gpio_port_name,
			g_spi_config->spi_gpio_port.spi_sout, &(g_spi_config->pin_config));

	//SPI configuration
	SPI_set_master(g_spi_config->spi_channel, g_spi_config->spi_master);
	SPI_fifo(g_spi_config->spi_channel, g_spi_config->spi_enable_fifo);
	SPI_clock_polarity(g_spi_config->spi_channel, g_spi_config->spi_polarity);
	SPI_frame_size(g_spi_config->spi_channel, g_spi_config->spi_frame_size);
	SPI_clock_phase(g_spi_config->spi_channel, g_spi_config->spi_phase);
	SPI_baud_rate(g_spi_config->spi_channel, g_spi_config->spi_baudrate);
	SPI_msb_first(g_spi_config->spi_channel, g_spi_config->spi_lsb_or_msb);
	SPI_enable(g_spi_config->spi_channel);
}
