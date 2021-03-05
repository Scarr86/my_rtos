/*
 * phil.cpp
 *
 * Created: 21.01.2021 13:49:20
 *  Author: Dizel
 */ 
#include "phil.h"

uint8_t Phil::num = 10;


 Phil::Phil(StPhil & state, IConsole & console):Task(state){ 
	this->console = &console;
	id = ++Phil::num;
}

//=====

StPhil::StPhil(const char * type):_type(type){}

void StPhil::setContext(Task * task)
{
	_phil = (Phil*)task;
}

int StPhil::handle(event_type_t ev, void * payload)
{
	char buf[30];
	uint16_t len;
	if(ev == EventType::init)	{
		len = sprintf(buf, "Phil(init) %d(%p) has state %s\n\r", _phil->id, Task::getTaskCurrent(), this->_type );
	}
	else{
		len = sprintf(buf, "Phil(poll) %d(%p) has state %s\n\r", _phil->id, Task::getTaskCurrent(), this->_type );
	}

	_phil->console->write((uint8_t*)buf, len);
	_delay_ms(500);
	_phil->console->write((const uint8_t[]){12}, 1);
	_phil->poll();
	
	_phil->next(this->_state);
	return 0;
}

void StPhil::send()
{
;
}

StPhilA::StPhilA():StPhil("A"){};
StPhilB::StPhilB():StPhil("B"){};
	
