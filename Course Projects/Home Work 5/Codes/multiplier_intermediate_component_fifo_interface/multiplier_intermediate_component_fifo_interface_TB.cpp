#include "multiplier_intermediate_component_fifo_interface_TB.h"

void multiplier_intermediate_component_fifo_interface_TB::inputing(){

	    // Processor choses intermediate component to communicate with
	    Addr_from_processor = "01";

	    // Sending data to intermediate component
	    data_in_intermediate_component = "00000000000000100000000000000010";
	    wait(600, SC_NS);
	    data_in_intermediate_component = "00000000000000110000000000000010";
	    wait(600, SC_NS);
	    data_in_intermediate_component = "00000000000000110000000000000011";
	    wait(600, SC_NS);
	    data_in_intermediate_component = "00000000000001000000000000000011";
	    wait(600, SC_NS);
	    data_in_intermediate_component = "00000000000001000000000000000100";
	    wait(600, SC_NS);	

	    // Processor choses multiplier to communicate with    	    	    
	    Addr_from_processor = "10";

	    // Processor issues start bit to start multiplication
	    Ctrl_in_multiplier = "00000000000000000000000000000001";
	    wait(40000, SC_NS);

	    Addr_from_processor = "00";
}

void multiplier_intermediate_component_fifo_interface_TB::clocking(){
	clk = sc_logic('1'); 
	for (int i = 0; i <= 400; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}

void multiplier_intermediate_component_fifo_interface_TB::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};