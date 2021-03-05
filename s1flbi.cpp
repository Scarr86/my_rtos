/*
 * s1flbi.cpp
 *
 * Created: 04.02.2021 9:33:12
 *  Author: Dizel
 */ 

#include "s1flbi.h"

IConsole* S1FLBI::uart;

uint8_t S1FLBI::fstart;

uint16_t S1FLBI::start;

uint8_t S1FLBI::halfOne;

uint8_t S1FLBI::rxIndx;

uint8_t S1FLBI::rxByte;


uint8_t S1FLBI::txByte = 0;

uint8_t S1FLBI::txIndx = 0;

uint8_t S1FLBI::fbit = 0;

uint8_t S1FLBI::ocr = S1FLBI_ONE_COMPARE_MATCH;

RingBuf<uint8_t, 2048> S1FLBI::rb;

 S1FLBI::S1FLBI()
{
}

void S1FLBI::init(IConsole * u){
	cli ();
	uart = u;
	DDRA = 0x01;
	S1FLBI::initExint();
	S1FLBI::initTimer();
	sei ();
}
void S1FLBI::initTimer()
{
	OCR3A = ocr;
	//TCCR3B =  S1FLBI_CLEAR_COUNTER_ON_MATCH | S1FLBI_PRESCALE_64;
	TCCR3B = S1FLBI_PRESCALE_64;
	ETIMSK |= S1FLBI_COMPARE_MATCH_A_INTERRUPT_ENABLE;
	
	//OCR0 = 	S1FLBI_ONE_COMPARE_MATCH;
	//TCCR0 =  0x04;
	//TCCR3B = S1FLBI_PRESCALE_64;
	//TIMSK |= 0x02;
}

void S1FLBI::initExint()
{
	DDRE	&=	_BV(DDE6);
	PORTE	|=	_BV(PE6);
	EICRB	=		_BV(ISC60);// ext interrupt control reg
	EIMSK	=		_BV(INT6); // enable ext interrupt
}

void S1FLBI::send(uint8_t byte)
{
	if(rb.isFull()){
	}
	else{
		rb.push(byte);
	}
}

void S1FLBI::poll()
{
	if(!ocr)
		ocr = getCompareMath();
	//uint16_t _start;
	//uint16_t diff;
	//
	//if(fstart){
		//do{
			//_start = start;
		//}while(_start != start);
		//
		//diff = getTicks() - _start;
		//if( diff > (uint16_t)(S1FLBI_MORE_ONE * 2) )	{
			//fstart = 0;
			//PORTB = diff;
		//}
	//}
}

uint16_t S1FLBI::getTicks()
{
	return S1FLBI_TIMER_COUNTER;
	//return TCNT0;
}

inline uint8_t S1FLBI::getCompareMath()
{
	if(fbit){
		fbit = 0;
		return S1FLBI_ONE_COMPARE_MATCH;
	}	else{
		if(rb.isEmpty()){
			txByte = S1FLBI_FILLER_BYTE;
		}else	if(!(txIndx & 7) ){
			txIndx = 0;
			txByte = rb.pop();
		}
		fbit = txIndx++ & 7;
		fbit = txByte & (1 <<  (S1FLBI_DIR(fbit)));
		if(fbit)
			return S1FLBI_ONE_COMPARE_MATCH;
	}
	return S1FLBI_ZERO_COMPARE_MATCH;
}

void S1FLBI::handlerExint()
{
	
	uint16_t diff = 0;
	uint16_t end = 0;
	if(fstart){
		end = S1FLBI::getTicks();
		diff = end - start;
		start = end;
		if(diff > S1FLBI_MORE_ONE){
			halfOne = 0;
			rxByte &= ~_BV(S1FLBI_DIR(rxIndx++ & 7));	 // 0
			//Exint::uart->write(0);
		}
		else{
			//Exint::uart->write(1);
			if(halfOne){
				halfOne = 0;
				rxByte |= _BV(S1FLBI_DIR(rxIndx++ & 7)); // 1
				}	else{
				halfOne = 1;
				return;
			}
		}
		if(!(rxIndx & 7)){
			if(uart) uart->write(rxByte);
		}
	}
	else{
		start = S1FLBI::getTicks();
		fstart = 1;
	}
}


void S1FLBI::setConsole(IConsole & console)
{
	uart = &console;
}

ISR (INT6_vect){
	S1FLBI::handlerExint();
}
ISR(TIMER0_COMP_vect){
	return;
}

ISR(S1FLBI_COMPARE_INTERRUPT){
	PORTA ^= 0x01;
	//OCR3A += S1FLBI::getCompareMath();
	OCR3A += S1FLBI::ocr;
	S1FLBI::ocr = 0;
	return;
}
