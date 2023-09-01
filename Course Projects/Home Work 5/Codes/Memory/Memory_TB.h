#include "memoryReadWrites.h"

SC_MODULE(memory_TB) {

	sc_signal <sc_logic> clk, rst, rwbar;
	sc_signal <sc_lv<2> > Addr_from_processor;
	sc_signal <sc_lv<32> > input_data, output_data;
	sc_signal <sc_lv<32> > input_address;
	memory* MEM;

	SC_CTOR(memory_TB) {

		MEM = new memory("Memory");
		MEM->in(*MEM->memBus);
		MEM->clk(clk);
		MEM->rst(rst);
		MEM->Ctrl(rwbar);
		MEM->input_data(input_data);
		MEM->output_data(output_data);
		MEM->Addr(Addr_from_processor);		
		MEM->input_address(input_address);
		
		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking);
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
};
