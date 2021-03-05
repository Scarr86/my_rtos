/*
 * etimer.h
 *
 * Created: 15.02.2021 13:00:21
 *  Author: Dizel
 */ 

#include "task.h"
#include "systimer.h"
#include <stdint.h>
//
#ifndef ETIMER_H_
#define ETIMER_H_


class Timer{
	private:
	uint16_t start;
	uint16_t interval;
	protected:
	void set(uint16_t _interval);
	bool isExpired();
	void reset();
	public:
	Timer();
};


class Etimer: public Timer{
	private:
	static Etimer * etimerList;
	Etimer *etimer;
	Task * task;
	bool fend;
	void add();
	void del();
	void poll();
	
	public:
	Etimer(Task & _task);
	void set(uint16_t interval);
	void reset();
	static void pollList();
};

#endif /* ETIMER_H_ */