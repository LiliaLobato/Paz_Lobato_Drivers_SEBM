/**
 \file
 \brief
 This is the starter file of FlexTimer.
 In this file the FlexTimer is configured in overflow mode.
 \author J. Luis Pizano Escalante, luispizano@iteso.mx
 \date	21/03/2019
 \todo
 Add configuration structures.
 */

#include "FlexTimer.h"
#include "MK64F12.h"
#include "Delay.h"

void FTM0_ISR() {

}

void FlexTimer_Init() {
	/**Clock gating for FlexTimer*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
	/**It enable the FTM*/
	FTM0->MODE |= FTM_MODE_FTMEN_MASK;
	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	FTM0->CONF |= FTM_CONF_BDMMODE(3);
	/**Assign modulo register with a predefined value*/
	FTM0->MOD = 0x05; //Valor al que se desborda
	/**Configure FlexTimer in output compare in toggle mode*/
	FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSA(1) | FTM_CnSC_ELSA(1); //Control del canal 0 en status control
	/**Assign channel value register with a predefined value*/
	FTM0->CONTROLS[0].CnV = 0x03; //Cuando se llegue a este valor, se va a dar un toogle
	/**Select clock source and prescaler*/
	FTM0->SC |= FTM_SC_CLKS (FLEX_TIMER_CLKS_1) | FTM_SC_PS(FLEX_TIMER_PS_128);
}

void Compare_init(uint32_t mod, uint32_t cnv, input_capture_els els,
		uint8_t Flex_Timer_clk_N, uint8_t Flex_Timer_ps_N) {
	/**Clock gating for FlexTimer*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
	/**It enable the FTM*/
	FTM0->MODE |= FTM_MODE_FTMEN_MASK;
	/**Assign modulo register with a predefined value*/
	FTM0->MOD = mod; //Valor al que se desborda

	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	FTM0->CONF |= FTM_CONF_BDMMODE(3);

	/**Configure FlexTimer in output compare in toggle mode*/
	switch (els) {
	case TOOGLE:
		FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSA(1) | FTM_CnSC_ELSA(1);
		break;
	case SET:
		delay(65000);
		FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSA(1) | FTM_CnSC_ELSA(1) | FTM_CnSC_ELSB(1);
		break;
	case CLEAR:
		delay(65000);
		FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSA(1) | FTM_CnSC_ELSA(0) | FTM_CnSC_ELSB(1);
		break;
	default:
		break;
	}

	/**Assign channel value register with a predefined value*/
	FTM0->CONTROLS[0].CnV = cnv; //Cuando se llegue a este valor, se va a dar un toogle

	/**Select clock source and prescaler*/
	FTM0->SC |= FTM_SC_CLKS(Flex_Timer_clk_N) | FTM_SC_PS(Flex_Timer_ps_N);
}

void PWM_init_p(ft_mode mode) {
	switch (mode) {
	case EDGE_ALIGNED_PWM:
		break;
	case CENTER_ALIGNED_PWM:
		break;
	case COMBINE_PWM:
		break;
	default:
		break;
	}
}

void Capture_init(ft_mode mode) {
	switch (mode) {
	case INPUT_CAPTURE:
		break;
	case DUAL_EDGE_CAPTURE_MODE:
		break;
	default:
		break;
	}

}

