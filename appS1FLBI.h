/*
 * appS1FLBI.h
 *
 * Created: 15.02.2021 15:32:41
 *  Author: Dizel
 */ 

#include "app.h"
#include "app-conf.h"
#include "uart.h"
#include "s1flbi.h"

#ifndef APPS1FLBI_H_
#define APPS1FLBI_H_

class AppS1FLBI: public Application{

	public:
	void init() override;
	void run() override;
};


#endif /* APPS1FLBI_H_ */