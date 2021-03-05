/*
 * appS1FLBI.cpp
 *
 * Created: 15.02.2021 15:32:57
 *  Author: Dizel
 */ 

#include "appS1FLBI.h"


void AppS1FLBI::init()
{
		Application::init();
		S1FLBI::init(&uart0);
}

void AppS1FLBI::run()
{
		uint16_t w;
		while(~(w = uart0.read())){
			uart0.write(w);
			S1FLBI::setConsole(uart0);
			S1FLBI::send(w);
		}
		while(~(w = uart1.read())){
			S1FLBI::setConsole(uart1);
			S1FLBI::send(w);
		}
		S1FLBI::poll();
}
