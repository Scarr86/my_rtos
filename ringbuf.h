/*
 * fifo.h
 *
 * Created: 13.01.2021 14:23:40
 *  Author: Dizel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define  GET_PARAM(param, val) 		if(BUFF_SIZE > 256){ATOMIC_BLOCK(ATOMIC_RESTORESTATE){(val) = (param);}	}\
																	else{(val) = (param);}
																		
#define SET_PARAM(param, val)			GET_PARAM(val, param)

#ifndef FIFO_H_
#define FIFO_H_

template <typename T, int BUFF_SIZE>
class RingBuf{
	private:
	T buf[BUFF_SIZE];
	uint16_t _head = 0;
	uint16_t _tail = 0;
	
	public:
	RingBuf(){};
		
	uint16_t getHead(){
		uint16_t  h;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){h = _head;}
		return h;
	}
	uint16_t getTail(){
		uint16_t  t;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){t = _tail;}
		return t;
	}
	void setHead(uint16_t h){
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){_head = h;}
	}

	void setTail(uint16_t t){
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){_tail = t;}
	}
	void push(T v){
		uint16_t h = getHead(); 
		buf[h & (BUFF_SIZE - 1)] = v;
		setHead(h + 1);
	}
		
	T pop(){ 
		uint16_t t = getTail();
		T val =	buf[t & (BUFF_SIZE - 1)];
		setTail(t + 1);
		return val; 
	}
		
	bool isEmpty(){ 
		return getHead() == getTail();
	};
		
	bool isFull(){return (uint8_t)(getHead() - getTail()) == BUFF_SIZE;}
		
	void clear(){	
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){_head = _tail = 0;}
	}
}; 

#endif /* FIFO_H_ */