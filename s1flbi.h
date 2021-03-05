/*
 * s1flbi.h
 *
 * Created: 04.02.2021 9:33:00
 *  Author: Dizel
 */ 
#include "app-conf.h"
#include "ringbuf.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef S1FLBI_H_
#define S1FLBI_H_

#define S1FLBI_COMPARE_INTERRUPT TIMER3_COMPA_vect
#define S1FLBI_CLEAR_COUNTER_ON_MATCH				( ( uint8_t ) 0x08 )
#define S1FLBI_PRESCALE_64							( ( uint8_t ) 0x03 )//( ( uint8_t ) 0x04 )
#define S1FLBI_CLOCK_PRESCALER					( ( uint32_t ) 64 )
#define S1FLBI_COMPARE_MATCH_A_INTERRUPT_ENABLE	 ( ( uint8_t ) 0x10 )//( ( uint8_t ) 0x02 )
#define S1FLBI_TIMER_COUNTER (TCNT3)
#define S1FLBI_BOUND (1200)

//#define S1FLBI_COMPARE_MATCH (((F_CPU / (S1FLBI_BOUND * 2) ) / S1FLBI_CLOCK_PRESCALER) - 1)
#define S1FLBI_COMPARE_MATCH (((F_CPU / (S1FLBI_BOUND * 2) ) / S1FLBI_CLOCK_PRESCALER))
#define S1FLBI_ONE_COMPARE_MATCH (S1FLBI_COMPARE_MATCH - 1)
#define S1FLBI_ZERO_COMPARE_MATCH ((S1FLBI_COMPARE_MATCH * 2) - 1)
#define  S1FLBI_MORE_ONE (S1FLBI_COMPARE_MATCH * 6 / 4)

#define S1FLBI_FILLER_BYTE (0x55)

#define  S1FLBI_DIR(x) (7 - (x))
//#define  S1FLBI_DIR(x) (x)

class S1FLBI{
	private:
	
	static IConsole* uart;
	static uint8_t fstart;
	static uint16_t start;
	static uint8_t halfOne;
	static uint8_t rxIndx;
	static uint8_t rxByte;
	
	static uint8_t txByte;
	static uint8_t txIndx;
	static uint8_t fbit;
	static RingBuf<uint8_t, 2048> rb;
	public:
	static uint8_t ocr;
	S1FLBI();
	static void init(IConsole * u);
	static void initTimer();
	static void initExint();
	
	static void send(uint8_t byte);
	static void poll();
	
	static uint16_t getTicks();
	
	inline static uint8_t getCompareMath();
	inline static void handlerExint();
	
	static void setConsole(IConsole & console);
};



#endif /* S1FLBI_H_ */