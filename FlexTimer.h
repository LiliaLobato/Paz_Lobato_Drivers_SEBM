/**
 \file
 \brief
 This is the header file for the FlexTimer divice driver.
 \author J. Luis Pizano Escalante, luispizano@iteso.mx
 \date	21/03/2019
 \todo
 Add configuration structures.
 */

#include "stdint.h"

typedef enum {
	INPUT_CAPTURE,
	OUTPUT_COMPARE,
	EDGE_ALIGNED_PWM,
	CENTER_ALIGNED_PWM,
	COMBINE_PWM,
	DUAL_EDGE_CAPTURE_MODE
} ft_mode;

typedef enum {
	TOOGLE, CLEAR, SET
} input_capture_els;

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

#include "MK64F12.h"

#define FLEX_TIMER_CLKS_0  (0U)
#define FLEX_TIMER_CLKS_1  (1U)
#define FLEX_TIMER_CLKS_2  (2U)
#define FLEX_TIMER_CLKS_3  (3U)

#define FLEX_TIMER_PS_1    (0U)
#define FLEX_TIMER_PS_2    (1U)
#define FLEX_TIMER_PS_4    (2U)
#define FLEX_TIMER_PS_8    (3U)
#define FLEX_TIMER_PS_16    (4U)
#define FLEX_TIMER_PS_32    (5U)
#define FLEX_TIMER_PS_64    (6U)
#define FLEX_TIMER_PS_128    (7U)

void FlexTimer_Init();
void Compare_init(uint32_t mod, uint32_t cnv,
		input_capture_els els, uint8_t Flex_Timer_clk_N,
		uint8_t Flex_Timer_ps_N);
void PWM_init_p(ft_mode mode);
void Capture_init(ft_mode mode);

#endif /* FLEXTIMER_H_ */
