/*
 * filosophy.cpp
 *
 * Created: 23.10.2020 14:49:14
 * Author : Dizel
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "app.h"
//#include "appEtimer.h"
//#include "appS1FLBI.h"
#include "appPhil.h"


//Application app;
//AppEtimer appEtimer;
//AppS1FLBI appS1FLBI;
AppPhil appPhil;

int randRange( uint16_t from, uint16_t to){
	 return from + (rand() % (to - from + 1));
}
 uint16_t calc(uint16_t a, uint16_t b, uint16_t (*opt)(uint16_t a, uint16_t b) ){
	 return opt(a,b);
 }
 


int main(void)
{	
	//refApp = app;
	//refApp = appEtimer;
	Application &refApp = appPhil;
	
	//uint16_t v = 0x2;
	//auto lamda{[v](uint16_t a, uint16_t b)->uint16_t{return a+b + v;}};
	//PORTB = lamda(2,3);
	//PORTA =  calc(0x40, 0x2, [](uint16_t a, uint16_t b)-> uint16_t{ return a + b;})	;

	refApp.init();
	while (1)
  {
		refApp.run();
	}
}



