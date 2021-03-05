/*
 * appEtimer.h
 *
 * Created: 15.02.2021 14:45:46
 *  Author: Dizel
 */ 
#include "app.h"
#include "etimer.h"
#include <avr/io.h>

#ifndef APPETIMER_H_
#define APPETIMER_H_

class TaskA: public Task
{
	public:
	TaskA();
	int execute();
};

class AppEtimer:public Application
{
	static TaskA taskA;
	public:
	static Etimer et;
  void init() override;
	void run() override;
};



#endif /* APPETIMER_H_ */