/*
 * appEtimer.cpp
 *
 * Created: 15.02.2021 14:46:00
 *  Author: Dizel
 */
 #include "appEtimer.h"

TaskA AppEtimer::taskA = TaskA(); 
Etimer AppEtimer::et = Etimer(AppEtimer::taskA);

void AppEtimer::init()
{
	SysTimer::init();
	et.set(1);
}

void AppEtimer::run()
{
	Etimer::pollList();
}

TaskA::TaskA()
{
	DDRB = 0xFF;
}

int TaskA::execute()
{
	PORTB ^= 0xFF;
	AppEtimer::et.reset();
	return 0;
}
