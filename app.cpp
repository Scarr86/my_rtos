/*
 * app.cpp
 *
 * Created: 18.01.2021 13:38:03
 *  Author: Dizel
 */ 
#include "app.h"
//----------------------------------
//StatePhilosophy stPhilA("A");
//StatePhilosophy stPhilB("B");
//
//StatePhilosophy stPhilAA("AA");
//StatePhilosophy stPhilBB("BB");

Uart Application::uart0 = Uart(0);

Uart Application::uart1 = Uart(1);
//
//StPhilA  stPhilA;
//StPhilB  stPhilB;
//
//Phil phil1 = Phil(stPhilA, Application::uart0);
//Phil phil2 = Phil(stPhilB, Application::uart1);
//Phil *phil2 = new  Phil(&stPhilA, Application::uart0);
////----------------------------------
//SysTimer sysTimer;
////----------------------------------
////----------------------------------
//EventListenerA evlA;
//EventListenerB evlB;
//EventManager evm;
////----------------------------------
////----------------------------------
//
//uint16_t start, end;
//int16_t dts;

Application::Application(){};

void Application::init(){
	uart0.begin();
	uart1.begin();
//----------------------------------
	//sysTimer.init();
	//start = sysTimer.getTicks();
//----------------------------------
	//DDRB = 0xff;
//----------------------------------
	//_delay_ms(500);
//----------------------------------
	//stPhilA.setNextState(stPhilB).setNextState(stPhilA);
	//stPhilA.next(stPhilB).next(stPhilA);
	//phil1.start();
	//----------------------------------
	//evm.subscribe(&evlA);
	//evm.subscribe(&evlB);
//----------------------------------
	//S1FLBI::init(uart0);
	//----------------------------------
}

void Application::run(){
	
	//uint8_t str[] = "Hello world";
	//uart0.write(str, sizeof str);
	//uart1.write(str, sizeof str);
	//uart0.write(12); // clear terminal
		//
	//====
	/* echo	*/
	//uint16_t w;
	////S1FLBI::send(0x31);
	//while(~(w = uart0.read())){
		////S1FLBI::setConsole(uart0);
		////S1FLBI::send(w);
		//uart0.write(w);
	//}
	////w = uart1.read();
	//while(~(w = uart1.read())){
		////S1FLBI::setConsole(uart1);
		////S1FLBI::send(w);
		//uart1.write(w);
	//}
	//
	//S1FLBI::poll();

	//====	
	//end = sysTimer.getTicks();
	//dts = end - start;
	//dts += dts < 0 ? (F_CPU / CLOCK_PER_SECOND) : 0;
	//if((uint16_t)dts >= GAP(100) ){
		//start = end;
		//PORTA ^= 0xff;
	//}
	
	//====
	Task::run();
	//phil1.execute(EventType::poll, nullptr);
	//phil2.execute(EventType::poll, nullptr);
	//====
	
	//evm.notify(12);
	//evm.notify(13);
	//evm.unsubscribe(&evlA);

}
