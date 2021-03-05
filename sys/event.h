/*
 * event.h
 *
 * Created: 02.03.2021 15:48:52
 *  Author: Dizel
 */ 
#include "../ringbuf.h"

#ifndef EVENT_H_
#define EVENT_H_



namespace EventType{
	typedef enum {
		poll,
		init,
		exit	
	} event_type_t;
}
using namespace EventType;
typedef struct{
	 event_type_t ev;
	 void * payload;
} event_t; 

class Event{
	//uint32_t  
	RingBuf<event_t, 32> events;
 	void emit(event_type_t ev, void* payload){
		 
		 
	}
	void do_vent(void);
	//subscribe()
};

#endif /* EVENT_H_ */