/*
 * task.cpp
 *
 * Created: 20.01.2021 14:15:20
 *  Author: Dizel
 */ 

#include "task.h"
 
Task * Task::_taskList = nullptr;
uint8_t Task::_poll_request = 0;
Task* Task::_taskCurrent = nullptr;

/*CTOR*/
Task::Task(){
	_state = nullptr;
	_needspoll = 0;
	_task = nullptr;
}
Task::Task(State & state):Task(){
	_state = &state;
}

void Task::run()
{
	if(_poll_request){
		do_poll();
	}
}

Task* Task::getTaskCurrent()
{
	return Task::_taskCurrent;
}

void Task::call(EventType::event_type_t ev, void * payload)
{
	_taskCurrent = this;
	execute(ev, payload);
}

uint8_t Task::start()
{
	Task * q;
	for (q = _taskList; q != nullptr; q = this->_task)
	{
		if(q == this) {
			return false;
		}
	}
	_task = _taskList;
	_taskList = this;
	call(EventType::init, nullptr);
	return true;

}

uint8_t Task::exit()
{
	Task * q;
	for (q = _taskList; q != nullptr; q = this->_task){
		if(q->_task == this){
			q->_task->call(EventType::exit, nullptr);
			q->_task = _task;
			return true;
		}
	}
	return false;
}

void Task::poll()
{
	_needspoll = 1;
	_poll_request = 1;
}

void Task::do_poll()
{
	_poll_request = 0;
	for (Task * t = _taskList; t != nullptr ; t = t->_task){
		if(t->_needspoll){
			t->_needspoll = 0;
			t->call(EventType::poll, nullptr);
		}
	}
}

int Task::execute(event_type_t ev, void * payload){
	int result = 0; 
	if(_state){	
		_state->setContext(this);
		result = _state->handle(ev, payload);
	}
	return result;
}

void Task::next( State * state ){
	//if(this->_state != nullptr){
	//delete this->_state;
	//}
	this->_state = state;
}

/* ===== STATE =======*/
State::State(){}
State::~State(){}

State & State::next(State & state)
{
	_state = &state;
	return state;
}

