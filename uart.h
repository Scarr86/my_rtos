/*
 * uart.h
 *
 * Created: 14.01.2021 13:20:57
 *  Author: Dizel
 */ 


#include "app-conf.h"
#include "ringbuf.h"

#include <avr/interrupt.h>
#include <util/setbaud.h>

#ifndef UART_H_
#define UART_H_



class IConsole{
	public:
	virtual void write(const uint8_t* buf, uint16_t len) = 0;
	virtual void write(uint8_t) = 0;
	virtual uint16_t read()=0;
	virtual void begin ()=0;
};


/****************************************************************/
/* Defining ISR vectors                                         */
/****************************************************************/
extern "C" void USART0_RX_vect(void) __attribute__ ((signal));
extern "C" void USART0_TX_vect(void) __attribute__ ((signal));
extern "C" void USART0_UDRE_vect(void) __attribute__ ((signal));
extern "C" void USART1_RX_vect(void) __attribute__ ((signal));
extern "C" void USART1_TX_vect(void) __attribute__ ((signal));
extern "C" void USART1_UDRE_vect(void) __attribute__ ((signal));

class Uart: public IConsole{
	public:																								
	Uart(const uint8_t port);
	
	void write(const uint8_t* buf, uint16_t len);
	void write(uint8_t data);
	uint16_t read();
	void begin();
	
	friend void USART0_RX_vect(void);
	friend void USART0_TX_vect(void);
	friend void USART0_UDRE_vect(void);
	friend void USART1_RX_vect(void);
	friend void USART1_TX_vect(void);
	friend void USART1_UDRE_vect(void);
	 
	private:
	static Uart* u0;
	static Uart* u1;
	inline void hdrUDREI();
	inline void hdrRXI();
	inline void hdrTXI();
	volatile uint8_t* UDRn;
	volatile uint8_t* UCSRnA;
	volatile uint8_t* UCSRnB;
	volatile uint8_t* UCSRnC;
	volatile uint8_t* UBRRnH;
	volatile uint8_t* UBRRnL;
	
	RingBuf<uint8_t, 8> output;
	RingBuf<uint8_t, 8> input;
};






#endif /* UART_H_ */


	//void begin(	uint32_t baud = 0,
	//USARTOperatingMode mode = USARTOperatingMode::ASYNC_NORMAL,
	//USARTParity parity = USARTParity::NONE,
	//USARTStopBits stopBits = USARTStopBits::ONE,
	//USARTFrameLength frameLength = USARTFrameLength::EIGHT_BITS);
	//
	//void setFrameLength(USARTFrameLength frameLength);
	//void setStopBit(USARTStopBits stopBit);
	//void setParity(USARTParity parity);
	//void setOpMode(uint32_t baud, USARTOperatingMode mode);

//
///****************************************************************/
///* Enumeration of communication modes supported by USART        */
///****************************************************************/
//enum class USARTOperatingMode
//{
	//ASYNC_NORMAL = 0,    /*!<Asynchronous Normal mode */
	//ASYNC_DOUBLE_SPEED = 1,    /*!<Asynchronous Double Speed */
	//SYNC_MASTER = 2     /*!<Synchronous Master mode */
//};
//
///****************************************************************/
///* Enumeration defining communication parity modes              */
///****************************************************************/
//enum class USARTParity
//{
	//NONE = 0,
	//EVEN = 2,
	//ODD = 3
//};
//
///****************************************************************/
///* Enumeration defining communication stop bits                 */
///****************************************************************/
//enum class USARTStopBits
//{
	//ONE = 1,
	//TWO = 2
//};
//
///****************************************************************/
///* Enumeration defining communication frame length              */
///****************************************************************/
//enum class USARTFrameLength
//{
	//FIVE_BITS = 5,
	//SIX_BITS = 6,
	//SEVEN_BITS = 7,
	//EIGHT_BITS = 8,
	//NINE_BITS = 9
//};
//
