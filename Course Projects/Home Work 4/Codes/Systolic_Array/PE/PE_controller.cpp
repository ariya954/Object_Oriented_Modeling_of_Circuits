#include "PE_controller.h"

void PE_controller::comb_function()
{
	// Inactive output values
	Load_Result = SC_LOGIC_0;
	
	switch( Pstate ){
		case IDLE:
			if (startPE == SC_LOGIC_1) Nstate = LOAD_WEIGHT;
			else Nstate = IDLE;
			break;
		case LOAD_WEIGHT: 
			if (startPE == SC_LOGIC_0) Nstate = WAIT_FOR_START_CALC_COMMAND;
			else Nstate = LOAD_WEIGHT;
			break;
		case WAIT_FOR_START_CALC_COMMAND: 
			if (busyPE == SC_LOGIC_1) Nstate = CALC_MAC;
			else{
				if(startPE == SC_LOGIC_1) Nstate = LOAD_WEIGHT;
				else Nstate = WAIT_FOR_START_CALC_COMMAND;
			} 
			break;
		case CALC_MAC: 
			Load_Result = SC_LOGIC_1;
			if (busyPE == SC_LOGIC_0) Nstate = WAIT_FOR_START_CALC_COMMAND;
			break;
		default: 
			Nstate = IDLE;
			break;
	}
}

void PE_controller::seq_function(){
	while (1){
		if (rst == '1')
			Pstate = IDLE;
		else if (clk->event() &&(clk == '1'))
			Pstate = Nstate;
		wait();
	}
}