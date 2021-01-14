/*
 * uart.cpp
 *
 * Created: 14.01.2021 13:21:08
 *  Author: Dizel
 */ 
#include "uart.h"


Uart* Uart::u0 = nullptr;
Uart* Uart::u1 = nullptr;

Uart::Uart(const uint8_t port){
	
	switch (port)
	{
		case 1:
		if(u1 == nullptr){
		  UDRn = &UDR1;
		  UCSRnA = &UCSR1A;
		  UCSRnB = &UCSR1B;
		  UCSRnC = &UCSR1C;
			UBRRnH = &UBRR1H;
		  UBRRnL = &UBRR1L;
			this->port = &PORTB;
			u1 = this;
		}
		break;
		default:
			if(u0 == nullptr){
				UDRn = &UDR0;
				UCSRnA = &UCSR0A;
				UCSRnB = &UCSR0B;
				UCSRnC = &UCSR0C;
				UBRRnH = &UBRR0H;
				UBRRnL = &UBRR0L;
				this->port = &PORTA;
				u0 = this;
			}
		break;
	}
	
}

void Uart::write(uint8_t data){
	/* ќжидание освобождени€ буфера передатчика */
	while(!(*UCSRnA & (1 << UDRE)))
	;
	*UDRn =  data;
}

void	Uart::write(const uint8_t* buf){
}

uint16_t Uart::read(){
	/* ќжидание данных дл€ приема */
	while(!(*UCSRnA & (1 << RXC)))
	;
	return *UDRn;
}

void Uart::begin(	uint32_t baud,
									USARTOperatingMode mode,
									USARTParity parity ,
									USARTStopBits stopBits,
									USARTFrameLength frameLength ){
	//this->setParity(parity);
	//this->setStopBit(stopBits);
	//this->setFrameLength(frameLength);
	////this->flushBuffer();
	///* Enable receiver and transmitter */
	//*(this->UCSRnB) = (1 << RXEN) | (1 << TXEN) | ( 1 << RXCIE);
	//this->setOpMode(baud, mode);
	#if defined (UBRR0H) &&  defined (UBRR1H)
	*UBRRnH =  UBRRH_VALUE;
	*UBRRnL = UBRRL_VALUE;
	#else
	#error "Device is not supported by the driver"
	#endif
	cli();
	// 	enable RX and TX and set interrupts on rx complete
	*UCSRnB = (1 << RXEN) | (1 << TXEN) | (0 << RXCIE) | (0 << TXCIE);
	// 	8-bit, 1 stop bit, no parity, asynchronous UART
	*UCSRnC = (1 << UCSZ0) | (1 << UCSZ1);
	sei();
}
	
void Uart::setOpMode(uint32_t baud, USARTOperatingMode mode){
}