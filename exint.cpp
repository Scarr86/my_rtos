/*
 * exint.cpp
 *
 * Created: 11.02.2021 13:34:55
 *  Author: Dizel
 */ 
#include "exint.h"

#include <stdio.h>

IConsole* Exint::uart = nullptr;

uint8_t Exint::fstart = 0;

uint8_t Exint::start = 0;

uint8_t Exint::halfOne = 0;

uint8_t Exint::indx = 0;

uint8_t Exint::byte = 0;

void Exint::init(IConsole& u)
{
	cli();
	uart = &u; 
	DDRE = 0x00;
	EICRB = _BV(ISC60);// ext interrupt control reg
	EIMSK = _BV(INT6); // enable ext interrupt
	sei();
}

void Exint::handler()
{
	uint8_t diff = 0;
	uint8_t end = 0;
	//char buf[30] = {'t'};
	//uint16_t len;
	//len = sprintf(buf, "%X\n\r", S1FLBI::getTicks());
	//Exint::uart->write((uint8_t*)buf, len);
	if(fstart){
		start = S1FLBI::getTicks();
		fstart = 0;
	}
	else{
		end = S1FLBI::getTicks();
		diff = end - start;
		start = end;
		if(diff > S1FLBI_MORE_ONE){
			halfOne = 0;
			byte &= ~_BV(7 - (indx++ & 7));	 // 0
			//Exint::uart->write(0);
		}
		else{
			//Exint::uart->write(1);
			if(halfOne){
				halfOne = 0;
				byte |= _BV(7 - (indx++ & 7)); // 1
			}	else{
				halfOne = 1;
				return;
			}
		}
		if(!(indx & 7)){
			Exint::uart->write(byte);
		}
	}
}

ISR (INT6_vect){
	Exint::handler();
}
