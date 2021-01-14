/*
 * fifo.h
 *
 * Created: 13.01.2021 14:23:40
 *  Author: Dizel
 */ 

#include "stdint.h"
#ifndef FIFO_H_
#define FIFO_H_

template <typename T,  int BS>
class RingBuf{
	private:
	T buf[BS];
	uint8_t head;
	uint8_t tail;
	
	public:
	//Fifo(){};
	void push(T v);
	T pop();
	bool isEmpty();
	bool isFull();
}; 

template <typename T,  int BS>
void RingBuf<T, BS>::push(T v){
	buf[head++ & (BS - 1)] = v;
}

template <typename T,  int BS>
T RingBuf<T, BS>::pop(){
	return buf[tail++ & (BS - 1)];
}

template <typename T,  int BS>
bool RingBuf<T, BS>::isEmpty(){
	return head == tail;
}

template <typename T,  int BS>
bool RingBuf<T, BS>::isFull(){
	return (head - tail) == BS;
}






#endif /* FIFO_H_ */