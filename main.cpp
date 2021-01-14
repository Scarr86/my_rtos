/*
 * filosophy.cpp
 *
 * Created: 23.10.2020 14:49:14
 * Author : Dizel
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "ringbuf.h"
#include "uart.h"

int randRange( int from, int to){
	 return from + (rand() % (to - from + 1));
}

RingBuf<uint8_t, 8> a;

Uart uart0(0);
Uart uart1(1);

//Uart* u0 =  Uart::u0;
//Uart* u1 =  Uart::u1;


	
int main(void)
{
		//a.push(1);
		//uart0.write();
		uart0.begin();
		uart1.begin();
		while (1)
    {
			//uart0.write(uart0.read());
			uart1.write(uart1.read());
			//PORTA = randRange(1, 3);
			//PORTA = a.pop();
			//PORTA = uart0.read();
		}
}



