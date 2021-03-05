/*
 * app.h
 *
 * Created: 18.01.2021 13:38:19
 *  Author: Dizel
 */ 
#include "new.h"
#include "uart.h"
#include "systimer.h"
#include "phil.h"
#include "event.h"
#include "s1flbi.h"


#include <util/delay.h>



#ifndef APP_H_
#define APP_H_

class Application{
	public:
	static Uart uart0;
	static Uart uart1;
	public:

	Application();
	virtual void init();
	virtual void run();	
};



#endif /* APP_H_ */