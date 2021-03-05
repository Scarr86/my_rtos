/*
 * task.h
 *
 * Created: 20.01.2021 14:15:33
 *  Author: Dizel
 */ 

#include <string.h>
#include <stdint.h>
#include "event.h"

#ifndef TASK_H_
#define TASK_H_

class Task;
	
class State{
		
	protected:
	State * _state;
	public:
	State();
	virtual	~State();
	virtual void setContext(Task *) = 0;
	virtual	int handle(event_type_t ev, void * payload) = 0;
	
	virtual State & next(State & state);
};

 
class Task{
	
	private:
	static Task * _taskList;
	static uint8_t _poll_request;
	static Task* _taskCurrent;
	Task* _task; // next task
	State* _state;	// next state
	uint8_t _needspoll;
	
	static void do_poll();
	
	void call(EventType::event_type_t, void*);
	
	public:	
	static void run();
	static Task* getTaskCurrent();
	
	uint8_t start();
	uint8_t exit();
	void poll();
	Task();	
	Task(State & state);
	void next(State * state);
	virtual int execute(event_type_t ev, void * payload);
};









#endif /* TASK_H_ */