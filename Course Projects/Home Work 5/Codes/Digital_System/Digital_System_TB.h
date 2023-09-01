#include "Digital_System.h"

SC_MODULE(digital_system_TB) {

	sc_signal <sc_logic> clk, rst;
	
	digital_system* System;

	SC_CTOR(digital_system_TB) {

		System = new digital_system("System");

		System->clk(clk);
		System->rst(rst);
		
		SC_THREAD(reseting); 
		SC_THREAD(clocking);
	}
	void reseting(); 
	void clocking(); 
};
