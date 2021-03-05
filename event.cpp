/*
 * subject.cpp
 *
 * Created: 03.02.2021 15:52:57
 *  Author: Dizel
 */ 

#include "event.h"

void EventListenerA::update(uint8_t ev)
{
	PORTA = ev;
}

void EventListenerB::update(uint8_t ev)
{
	PORTB = ev;
}
