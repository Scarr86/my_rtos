/*
 * subject.h
 *
 * Created: 03.02.2021 15:52:44
 *  Author: Dizel
 */ 

#include <avr/io.h>
#ifndef EVENT_H_
#define EVENT_H_

class EventListener{
	public:
	EventListener* next;
	virtual void update(uint8_t ev) = 0;
		
};

class EventManager{
	
	EventListener * EventListenerList;
	public:
	void subscribe(EventListener *  listener){
		listener->next = EventListenerList;
		EventListenerList = listener;
	}
	
	void unsubscribe(const EventListener * listener){
		EventListener * evl;
		for (evl = EventListenerList; evl != nullptr && evl->next != listener; evl = evl->next )
		;
		
		if(evl == nullptr) 
			return;
		
		evl->next = evl->next->next;
	}
	
	void notify(uint8_t ev){
		EventListener *evl;
		for (evl = EventListenerList; evl != nullptr ; evl = evl->next)
		{
			evl->update(ev);
		}
	}
};


class EventListenerA:public EventListener{ 
	public:
	void update(uint8_t ev) override;
	
}; 
class EventListenerB:public EventListener{
	public:
	void update(uint8_t ev) override;
};

#endif /* EVENT_H_ */