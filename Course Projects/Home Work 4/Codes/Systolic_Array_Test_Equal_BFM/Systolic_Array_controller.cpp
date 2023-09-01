#include "Systolic_Array_controller.h"

template <int Num_of_Rows, int Num_of_Columns, int Num_of_Iterations>
void systolic_array_controller<Num_of_Rows, Num_of_Columns, Num_of_Iterations>::comb_function()
{
	// Inactive output values
	done = SC_LOGIC_0;
	busyPE = SC_LOGIC_0;
	startPE = SC_LOGIC_0;
	
	switch( Pstate ){
		case IDLE:
			done = (iteration_counter == Num_of_Iterations) ? SC_LOGIC_1 : SC_LOGIC_0;
			rows_counter = 0;
			rows_and_columns_counter = 0;
			if (start == SC_LOGIC_1) Nstate = LOAD_WEIGHTS;
			else Nstate = IDLE;
			break;
		case LOAD_WEIGHTS: 
			if (co_rows_counter == SC_LOGIC_1) Nstate = WAIT_FOR_START_CALC_COMMAND;
			else startPE = SC_LOGIC_1;
			break;
		case WAIT_FOR_START_CALC_COMMAND: 
			if (busy == SC_LOGIC_1) Nstate = CALC_PEs_MACs;
			else Nstate = WAIT_FOR_START_CALC_COMMAND;
			break;
		case CALC_PEs_MACs: 
			if (co_rows_and_columns_counter == SC_LOGIC_1){
				Nstate = IDLE;
				iteration_counter++;
			}
			else busyPE = SC_LOGIC_1;
			break;
		default: 
			Nstate = IDLE;
			break;
	}
}

template <int Num_of_Rows, int Num_of_Columns, int Num_of_Iterations>
void systolic_array_controller<Num_of_Rows, Num_of_Columns, Num_of_Iterations>::seq_function(){
	while (1){
		if (rst == '1'){
			Pstate = IDLE;
			iteration_counter = 0;
		}
		else if (clk->event() &&(clk == '1')){
			Pstate = Nstate;
			if (Pstate == LOAD_WEIGHTS) {
				rows_counter++;
				co_rows_counter = (rows_counter > Num_of_Rows) ? SC_LOGIC_1 : SC_LOGIC_0;
			}
			if (Pstate == CALC_PEs_MACs) {
				rows_and_columns_counter++;
				co_rows_and_columns_counter = (rows_and_columns_counter > ((2*Num_of_Columns) + Num_of_Rows) - 1) ? SC_LOGIC_1 : SC_LOGIC_0;
			}	
		}	
		wait();
	}
}