#include <systemc.h>

SC_MODULE(bus) {
	
	sc_in <sc_lv<2> > Addr_from_processor;
	sc_out <sc_lv<32> > input_data_processor;
	sc_in <sc_lv<32> > output_data_processor;
	sc_in <sc_lv<32> > output_address_processor;
	sc_out <sc_lv<32> > input_control_signals_processor;	
	sc_in <sc_lv<32> > output_control_signals_processor;
	
	sc_out <sc_lv<32> > input_address_mem;
	sc_out <sc_lv<32> > input_data_mem;
	sc_in <sc_lv<32> > output_data_mem;
	sc_out <sc_logic> Ctrl_mem;
	
	sc_in <sc_lv<32> > output_control_signals_intermediate_component;
	sc_out <sc_lv<32> > input_data_intermediate_component;
	
	sc_out <sc_lv<32> > input_control_signals_multiplier_16_bit;
	sc_in <sc_lv<32> > output_control_signals_multiplier_16_bit;
	sc_in <sc_lv<32> > output_data_multiplier_16_bit;

	SC_CTOR(bus) {
		SC_THREAD (address_logic);
			sensitive << Addr_from_processor
			          << output_data_processor
			          << output_control_signals_processor
			          << output_address_processor
			          << output_data_mem
			     << output_control_signals_intermediate_component
			     << output_control_signals_multiplier_16_bit
			     << output_data_multiplier_16_bit;
    	}
    	
	void address_logic();
};

void bus::address_logic() {
	while(true){
		wait();
		if(Addr_from_processor.read() == "00"){
			Ctrl_mem = output_control_signals_processor.read()[0];
			input_address_mem = output_address_processor;
			input_data_mem = output_data_processor;
			input_data_processor = output_data_mem;
		}
		else if(Addr_from_processor.read() == "01"){
			input_data_intermediate_component = output_data_processor;
			input_control_signals_processor = output_control_signals_intermediate_component;
		}
		else if(Addr_from_processor.read() == "10"){
			input_control_signals_multiplier_16_bit = output_control_signals_processor;
			input_control_signals_processor = output_control_signals_multiplier_16_bit;
		}		
	}
}
