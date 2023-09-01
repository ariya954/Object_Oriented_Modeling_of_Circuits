#include <systemc.h>

SC_MODULE(processor) {

	sc_in <sc_logic> clk, rst;
	
	sc_out <sc_lv<2> > Addr_from_processor;
	sc_in <sc_lv<32> > input_data_processor;
	sc_out <sc_lv<32> > output_data_processor;
	sc_out <sc_lv<32> > output_address_processor;
	sc_in <sc_lv<32> > input_control_signals_processor;	
	sc_out <sc_lv<32> > output_control_signals_processor;
	
	sc_lv<32>* Register_File;
	
	SC_CTOR(processor) {
		Register_File = new sc_lv<32>[128];
		SC_THREAD (processor_function);
			sensitive << clk.pos();
    	}
    	
	void processor_function();
};
