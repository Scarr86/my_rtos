/*
 * exint.h
 *
 * Created: 11.02.2021 13:34:42
 *  Author: Dizel
 */ 
#include "uart.h"
 #include "s1flbi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef EXINT_H_
#define EXINT_H_

class Exint{
	private:
	static IConsole* uart;
	static uint8_t fstart;
	static uint8_t start;
	static uint8_t halfOne;
	static uint8_t indx;
	static uint8_t byte;
	public:
	static void init(IConsole& u);
	inline static void handler();
};





#endif /* EXINT_H_ */