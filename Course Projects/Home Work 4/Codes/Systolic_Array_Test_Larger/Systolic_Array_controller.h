#include <systemc.h>

template <int Num_of_Rows, int Num_of_Columns, int Num_of_Iterations>
SC_MODULE (systolic_array_controller){

	sc_in  <sc_logic> rst, clk, start, busy; 
	sc_out <sc_logic> startPE, busyPE, done;
		
	enum states {IDLE, LOAD_WEIGHTS, WAIT_FOR_START_CALC_COMMAND, 
				 				CALC_PEs_MACs};
				 				
	sc_signal <states> Pstate, Nstate; 
	sc_signal <sc_logic> co_rows_counter, co_rows_and_columns_counter;
	 
	int iteration_counter; 
	int rows_and_columns_counter;
	int rows_counter;

	SC_CTOR(systolic_array_controller)
	{
		SC_METHOD (comb_function);
		sensitive << co_rows_counter << co_rows_and_columns_counter << start << busy;
		SC_THREAD (seq_function); 
		sensitive << clk << rst;
	};

	void comb_function();
	void seq_function();
};
