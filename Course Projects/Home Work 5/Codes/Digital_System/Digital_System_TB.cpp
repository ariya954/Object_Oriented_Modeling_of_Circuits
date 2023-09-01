#include "Digital_System_TB.h"

void digital_system_TB::clocking(){
	clk = sc_logic('1'); 
	for (int i = 0; i <= 1000; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}

void digital_system_TB::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};