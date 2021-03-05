/*
 * etimer.cpp
 *
 * Created: 18.01.2021 14:49:51
 *  Author: Dizel
 */ 


#include "systimer.h"

uint16_t SysTimer::count = 0;
	
SysTimer::SysTimer(){
}

void SysTimer::init(){
	volatile uint32_t ulCompareMatch;
	 volatile uint8_t ucHighByte, ucLowByte;
  cli ();

	/* Using 16bit timer 1 to generate the tick.  Correct fuses must be
	selected for the configCPU_CLOCK_HZ clock. */

	//ulCompareMatch = F_CPU / CLOCK_PER_SECOND;

	/* We only have 16 bits so have to scale to get our required tick rate. */
	//ulCompareMatch /= portCLOCK_PRESCALER;

	/* Adjust for correct value. */
	ulCompareMatch = COMPARE_MATCH;
	//diff_OCR1A = ulCompareMatch;

	/* Setup compare match value for compare match A.  Interrupts are disabled 
	before this is called so we need not worry here. */
	ucLowByte = ( uint8_t ) ( ulCompareMatch & ( uint32_t ) 0xff );
	ulCompareMatch >>= 8;
	ucHighByte = ( uint8_t ) ( ulCompareMatch & ( uint32_t ) 0xff );
 	OCR1AH = ucHighByte;
 	OCR1AL = ucLowByte;

	/* Setup clock source and compare match behaviour. */
	ucLowByte = portCLEAR_COUNTER_ON_MATCH | portPRESCALE_64;
	TCCR1B = ucLowByte;

	/* Enable the interrupt - this is okay as interrupt are currently globally
	disabled. */
	ucLowByte = TIMSK;
	ucLowByte |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
	TIMSK = ucLowByte;
	//TIMSK |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
 // OCRSetup();
  sei ();
}

uint16_t SysTimer::clocks(){
	uint16_t tmp;
	do 
	{
		tmp = SysTimer::count;
	} while (tmp != SysTimer::count);
	return tmp;
}

uint16_t SysTimer::ticks(){
	return portTIMER_COUNTER;
}


ISR(portCOMPARE_INTERRUPT){
	SysTimer::count++;
}
	
	
