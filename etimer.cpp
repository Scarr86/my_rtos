/*
 * etimer.cpp
 *
 * Created: 15.02.2021 13:00:33
 *  Author: Dizel
 */ 
#include "etimer.h"


Etimer * Etimer::etimerList = nullptr;

Etimer::Etimer(Task & _task):task(&_task)
{
}
	
void Etimer::add()
{
	Etimer * et;
	for ( et = etimerList; et != nullptr; et = et->etimer){
		if(et == this){
			 fend = false;
			 return;
		}
	}
		 
	etimer = Etimer::etimerList;
	Etimer::etimerList = this;
}

void Etimer::del()
{
	Etimer * et;
	if(etimerList == this)	
		etimerList = this->etimer;
	else 
		for (et = etimerList; et != nullptr; et = et->etimer)
			if(et->etimer == this){
				et->etimer = this->etimer;
				break;
			}
}

void Etimer::pollList()
{
	for(Etimer * et = etimerList; et != nullptr; et = et->etimer){
		et->poll();
	}
}

void Etimer::set(uint16_t interval)
{
	Timer::set(interval);
	add();
}

void Etimer::reset()
{
	Timer::reset();
	add();
}

void Etimer::poll()
{
	if(!fend && isExpired()){
		fend = true;
		task->execute(EventType::poll, this);
	}
}

Timer::Timer(){}

void Timer::set(uint16_t _interval)
{
	interval = _interval;	
	start = SysTimer::clocks();
}

bool Timer::isExpired()
{
	uint16_t diff = (SysTimer::clocks() - start) + 1;
	return interval < diff;
}

void Timer::reset()
{
	start += interval;
}
