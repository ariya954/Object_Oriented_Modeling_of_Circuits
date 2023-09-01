#include <systemc.h>

SC_MODULE (PE_controller){

	sc_in  <sc_logic> rst, clk, startPE, busyPE; 
	sc_out <sc_logic> Load_Result;
		
	enum states {IDLE, LOAD_WEIGHT, WAIT_FOR_START_CALC_COMMAND, 
				 				CALC_MAC};
	sc_signal <states> Pstate, Nstate; 

	SC_CTOR(PE_controller)
	{
		SC_METHOD (comb_function);
		sensitive << Pstate << startPE << busyPE;
		SC_THREAD (seq_function); 
		sensitive << clk << rst;
	};

	void comb_function();
	void seq_function();
};
