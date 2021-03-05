/*
 * appPhil.h
 *
 * Created: 16.02.2021 14:30:25
 *  Author: Dizel
 */ 

#include "app.h"
#include "uart.h"
#include "phil.h"
#ifndef APPPHIL_H_
#define APPPHIL_H_
class AppPhil:public Application{

 static const char* yx[] ;
	public:	
	void init() override;
	void run() override;
};


#endif /* APPPHIL_H_ */