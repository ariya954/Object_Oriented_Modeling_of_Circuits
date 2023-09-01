#include "Memory_TB.h"

void memory_TB::inputing(){

    // Processor choses memory to communicate with
	Addr_from_processor = "00";

	// Writing 128 data to memory start from adress 0X00000008
	rwbar = sc_logic('0');
    input_address = "00000000000000000000000000001000";
    input_data = "00000000000000000000000000000000";
    for(int i = 0; i < 128; i++){
    	wait(100, SC_NS);
    	input_data = input_data.read().to_uint() + 1;
    	input_address = input_address.read().to_uint() + 1;
    }

	// Reading 128 data from memory start from adress 0X00000008   
    rwbar = sc_logic('1');
    input_address = "00000000000000000000000000001000";
    input_data = "00000000000000000000000000000000";
    for(int i = 0; i < 128; i++){
    	wait(100, SC_NS);
    	input_data = input_data.read().to_uint() + 1;
    	input_address = input_address.read().to_uint() + 1;
    }

    Addr_from_processor = "01";
    wait(6000, SC_NS);
}

void memory_TB::clocking(){
	clk = sc_logic('1'); 
	for (int i = 0; i <= 600; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}

void memory_TB::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};