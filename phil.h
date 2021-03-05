/*
 * phil.h
 *
 * Created: 21.01.2021 13:49:10
 *  Author: Dizel
 */ 
#include "uart.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#ifndef PHIL_H_
#define PHIL_H_

class Phil;

class StPhil : public State{
	protected:
	const char * _type;
	Phil * _phil;
	public:
	StPhil(const char * type);
	~StPhil(){}
	void setContext(Task * task) override;
	int handle(event_type_t ev, void * payload) override;	
	void send();
};

class StPhilA: public StPhil{
	public:
	StPhilA();
};

class StPhilB: public StPhil{
	public:
	StPhilB();
};

//=====


class Phil: public Task{
	public:
	IConsole * console;
	uint8_t id;
	Phil(StPhil & state,  IConsole & console);
	private:
	static uint8_t num;
};








#endif /* PHIL_H_ */