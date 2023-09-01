#include "fifoChannel.h"
#include "Register.h"

SC_MODULE (intermediate_component) {
	sc_in <sc_logic> clk, rst;
	sc_in <sc_lv<2> > Addr_from_processor;
	sc_port <put_if<sc_lv<32> > > out;
	sc_out <sc_lv<32> > output_control_signals;
	sc_in <sc_lv<32> > input_data;
	
	sc_signal<sc_lv<32> > input_control_signals;
	sc_signal<sc_logic> load_control_signals; 
	sc_signal<sc_logic> load_input_data;
	sc_signal<sc_lv<32> > output_data;

	Register<32>* cntrlReg;
	Register<32>* dataInReg;

	SC_CTOR(intermediate_component) {
		cntrlReg = new Register<32>("Control_Register");
			load_control_signals = SC_LOGIC_1;
			cntrlReg->clk(clk); 
			cntrlReg->rst(rst);
			cntrlReg->load(load_control_signals);
			cntrlReg->regin(input_control_signals); 
			cntrlReg->regout(output_control_signals);
		
		dataInReg = new Register<32>("Data_Register");
			load_input_data = SC_LOGIC_1;
			dataInReg->clk(clk); 
			dataInReg->rst(rst);
			dataInReg->load(load_input_data);
			dataInReg->regin(input_data);
			dataInReg->regout(output_data);
			
		SC_THREAD (put_operands);
			sensitive << clk << rst;
	}
	void put_operands();
};

SC_MODULE (multiplier_16_bit) {
	sc_in <sc_logic> clk, rst;
	sc_in <sc_lv<2> > Addr_from_processor;
	sc_port <get_if<sc_lv<32> > > in;
	sc_in <sc_lv<32> > input_control_signals;
	sc_out <sc_lv<32> > output_control_signals;
	sc_out <sc_lv<32> > output_data;
	
	sc_signal<sc_lv<32> > control_signals;
	sc_signal<sc_logic> load_control_signals; 
	sc_signal<sc_logic> load_output_data;
	sc_signal<sc_lv<32> > mult_result;

	Register<32>* cntrlReg;
	Register<32>* dataOutReg;	
	
	SC_CTOR(multiplier_16_bit) {
		cntrlReg = new Register<32>("Control_Register");
			load_control_signals = SC_LOGIC_1;
			cntrlReg->clk(clk); 
			cntrlReg->rst(rst);
			cntrlReg->load(load_control_signals);
			cntrlReg->regin(control_signals); 
			cntrlReg->regout(output_control_signals);
		
		dataOutReg = new Register<32>("Data_Register");
			load_output_data = SC_LOGIC_1;
			dataOutReg->clk(clk); 
			dataOutReg->rst(rst);
			dataOutReg->load(load_output_data);
			dataOutReg->regin(mult_result);
			dataOutReg->regout(output_data);
		
		SC_THREAD (get_operands_and_evaluate);
			sensitive << clk << rst;
    }
    void get_operands_and_evaluate();
};
