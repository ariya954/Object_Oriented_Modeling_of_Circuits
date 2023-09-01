#include "../Bus/Bus.h"
#include "../Processor/Processor.cpp"
#include "../Memory/memoryReadWrites.h"
#include "../multiplier_intermediate_component_fifo_interface/multiplier_intermediate_component_fifo_interface.cpp"

SC_MODULE(digital_system){

	sc_in <sc_logic> clk, rst;
	
	sc_signal <sc_lv<2> > Addr_from_processor;
	sc_signal <sc_lv<32> > input_data_processor;
	sc_signal <sc_lv<32> > output_data_processor;
	sc_signal <sc_lv<32> > output_address_processor;
	sc_signal <sc_lv<32> > input_control_signals_processor;	
	sc_signal <sc_lv<32> > output_control_signals_processor;
	
	sc_signal <sc_logic> Ctrl_mem;
	sc_signal <sc_lv<32> > input_data_mem, output_data_mem;
	sc_signal <sc_lv<32> > input_address_mem;
	
	sc_signal <sc_lv<32> > output_control_signals_intermediate_component;
	sc_signal <sc_lv<32> > input_data_intermediate_component;
	
	sc_signal <sc_lv<32> > input_control_signals_multiplier_16_bit;
	sc_signal <sc_lv<32> > output_control_signals_multiplier_16_bit;
	sc_signal <sc_lv<32> > output_data_multiplier_16_bit;
	
	bus* Bus;
	memory* MEM;
	processor* Processor;
	fifo<sc_lv<32>, 32> FIFO;
	intermediate_component* Intermediate_Component;
	multiplier_16_bit* Multiplier;

	SC_CTOR(digital_system){
	
		Processor = new processor("Processor");
			Processor->clk(clk);
			Processor->rst(rst);
			Processor->Addr_from_processor(Addr_from_processor);
			Processor->input_data_processor(input_data_processor);
			Processor->output_data_processor(output_data_processor);
			Processor->output_address_processor(output_address_processor);
			Processor->input_control_signals_processor(input_control_signals_processor);	
			Processor->output_control_signals_processor(output_control_signals_processor);
	
		MEM = new memory("Memory");
			MEM->in(*MEM->memBus);
			MEM->clk(clk);
			MEM->rst(rst);
			MEM->Ctrl(Ctrl_mem);
			MEM->Addr(Addr_from_processor);
			MEM->input_data(input_data_mem);
			MEM->output_data(output_data_mem);		
			MEM->input_address(input_address_mem);
			
		Intermediate_Component = new intermediate_component("Intermediate_Component");
			Intermediate_Component->clk(clk); 
			Intermediate_Component->rst(rst); 
			Intermediate_Component->Addr_from_processor(Addr_from_processor); 
			Intermediate_Component->input_data(input_data_intermediate_component); 
			Intermediate_Component->output_control_signals(output_control_signals_intermediate_component);

			Intermediate_Component->out(FIFO);
			
		Multiplier = new multiplier_16_bit("Multiplier");
			Multiplier->clk(clk); 
			Multiplier->rst(rst); 
			Multiplier->Addr_from_processor(Addr_from_processor);
			Multiplier->output_data(output_data_multiplier_16_bit);
			Multiplier->input_control_signals(input_control_signals_multiplier_16_bit); 
			Multiplier->output_control_signals(output_control_signals_multiplier_16_bit);
			
			Multiplier->in(FIFO);
			
		Bus = new bus("Bus");
			Bus->Addr_from_processor(Addr_from_processor);
			Bus->input_data_processor(input_data_processor);
			Bus->output_data_processor(output_data_processor);
			Bus->output_address_processor(output_address_processor);
			Bus->input_control_signals_processor(input_control_signals_processor);	
			Bus->output_control_signals_processor(output_control_signals_processor);
	
			Bus->input_address_mem(input_address_mem);
			Bus->input_data_mem(input_data_mem);
			Bus->output_data_mem(output_data_mem);
			Bus->Ctrl_mem(Ctrl_mem);
	
			Bus->output_control_signals_intermediate_component(output_control_signals_intermediate_component);			
			Bus->input_data_intermediate_component(input_data_intermediate_component);
	
			Bus->input_control_signals_multiplier_16_bit(input_control_signals_multiplier_16_bit);
			Bus->output_control_signals_multiplier_16_bit(output_control_signals_multiplier_16_bit);
			Bus->output_data_multiplier_16_bit(output_data_multiplier_16_bit);
			
		}
};
