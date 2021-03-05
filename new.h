/*
 * new.h
 *
 * Created: 15.02.2021 9:05:43
 *  Author: Dizel
 */ 


#ifndef NEW_H_
#define NEW_H_
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>



void * operator new(size_t size);
void operator delete(void * ptr);

__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard*);
extern "C" void __cxa_guard_release(__guard*);
extern "C" void __cxa_guard_abort(__guard*);
extern "C" void __cxa_pure_virtual(void);



#endif /* NEW_H_ */