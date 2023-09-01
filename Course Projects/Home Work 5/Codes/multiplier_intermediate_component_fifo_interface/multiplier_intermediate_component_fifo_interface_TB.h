#include "multiplier_intermediate_component_fifo_interface.cpp"

SC_MODULE(multiplier_intermediate_component_fifo_interface_TB) {

	sc_signal <sc_logic> clk, rst;
	sc_signal <sc_lv<2> > Addr_from_processor;
	sc_signal <sc_lv<32> > data_in_intermediate_component, data_out_multiplier;
	sc_signal <sc_lv<32> > Ctrl_out_intermediate_component, Ctrl_in_multiplier, Ctrl_out_multiplier;

	fifo<sc_lv<32>, 32> FIFO;
	intermediate_component* Intermediate_Component;
	multiplier_16_bit* Multiplier;

	SC_CTOR(multiplier_intermediate_component_fifo_interface_TB) : FIFO() {
		Intermediate_Component = new intermediate_component("Intermediate_Component");
			Intermediate_Component->clk(clk); 
			Intermediate_Component->rst(rst); 
			Intermediate_Component->Addr_from_processor(Addr_from_processor); 
			Intermediate_Component->input_data(data_in_intermediate_component); 
			Intermediate_Component->output_control_signals(Ctrl_out_intermediate_component);

			Intermediate_Component->out(FIFO);
			
		Multiplier = new multiplier_16_bit("Multiplier");
			Multiplier->clk(clk); 
			Multiplier->rst(rst); 
			Multiplier->Addr_from_processor(Addr_from_processor);
			Multiplier->output_data(data_out_multiplier);
			Multiplier->input_control_signals(Ctrl_in_multiplier); 
			Multiplier->output_control_signals(Ctrl_out_multiplier);
			
			Multiplier->in(FIFO);
			
		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking);
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
};
