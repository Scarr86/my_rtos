/*
 * appPhil.cpp
 *
 * Created: 16.02.2021 14:37:02
 *  Author: Dizel
 */ 
#include "appPhil.h"
StPhilA  stPhilA;
StPhilB  stPhilB;

Phil phil1 = Phil(stPhilA, Application::uart0);
Phil phil2 = Phil(stPhilB, Application::uart1);


void AppPhil::init()
{
		Application::init();
		stPhilA.next(stPhilB).next(stPhilA);
		phil1.start();
}

void AppPhil::run()
{
			Task::run();
}
