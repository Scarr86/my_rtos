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
				u0 = this;
			}
		break;
	}
	
}

void Uart::write(uint8_t data){
	while(output.isFull())
	;
	output.push(data);
	*(this->UCSRnB) |= (1 << UDRIE);
}

void Uart::write(const uint8_t* buf, uint16_t len){
	const uint8_t* start = buf;
	while((uint16_t)(buf - start) < len){
		write(*buf++);		
	}
}

uint16_t Uart::read(){
	/* ќжидание данных дл€ приема */
	//while(!(*UCSRnA & (1 << RXC)))
	//;
	//return *UDRn;	
	if(input.isEmpty())
		return -1;
	else
		return input.pop();
}



void Uart::begin(){
	#if defined (UBRR0H) &&  defined (UBRR1H)
	*UBRRnH =  UBRRH_VALUE;
	*UBRRnL = UBRRL_VALUE;
	#else
	#error "Device is not supported by the driver"
	#endif
	cli();
	// 	enable RX and TX and set interrupts on rx complete
	*UCSRnB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE);
	// 	8-bit, 1 stop bit, no parity, asynchronous UART
	*UCSRnC = (1 << UCSZ0) | (1 << UCSZ1);
	//output.clear();
	//input.clear();
	sei();
}

void Uart::hdrUDREI(){
	*UDRn = output.pop();
	if(output.isEmpty()){
		*UCSRnB &= ~(1 << UDRIE);
	}
}

void Uart::hdrRXI(){
	register uint8_t c = *UDRn; 
	register uint8_t error = *UCSRnA;
	if(error & (_BV(FE) | _BV(DOR))){
		/*ERROR rx frame error or data overflow*/
	}
	if(input.isFull()){
		/* ERROR input buffer overflow */
	}
	else{
		input.push(c);
	}
}

void Uart::hdrTXI()
{
	DDRC = 0xff;
	PORTC ^= 0xff;
}

ISR (USART0_UDRE_vect){
	Uart::u0->hdrUDREI();
}
ISR (USART1_UDRE_vect){
	Uart::u1->hdrUDREI();
}

ISR(USART0_TX_vect){
	Uart::u0->hdrTXI();
}
ISR(USART0_RX_vect){
	Uart::u0->hdrRXI();
}

ISR(USART1_TX_vect){
	//Uart::u1->hdrTXI();
}
ISR(USART1_RX_vect){
	Uart::u1->hdrRXI();
}