/*
 * etimer.h
 *
 * Created: 18.01.2021 14:49:38
 *  Author: Dizel
 */ 

#include "app-conf.h"

#include <avr/interrupt.h>
#ifndef SYSTIMER_H_
#define SYSTIMER_H_

#define portCOMPARE_INTERRUPT TIMER1_COMPA_vect
#define portCLEAR_COUNTER_ON_MATCH				( ( uint8_t ) 0x08 )
#define portPRESCALE_64							1 /*( ( uint8_t ) 0x03 )*/
#define portCLOCK_PRESCALER					1	/*( ( uint32_t ) 64 )*/
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE	( ( uint8_t ) 0x10 )
#define portTIMER_COUNTER (TCNT1)

#define COMPARE_MATCH ((F_CPU / CLOCK_PER_SECOND) - 1)
#define GAP(x) ((x * COMPARE_MATCH) / 1000)


class SysTimer{
	public:
	static uint16_t count;
	SysTimer();
	static void init();
	static uint16_t ticks();
	static uint16_t clocks();
};





#endif /* ETIMER_H_ */