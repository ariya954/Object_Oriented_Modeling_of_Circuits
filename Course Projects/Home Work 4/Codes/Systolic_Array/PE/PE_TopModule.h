#include "PE_datapath.h"
#include "PE_controller.cpp"

SC_MODULE(PE){

	// Port Declaration
	sc_in <sc_logic> clk, rst;
	sc_in <sc_logic> startPE, busyPE;
	sc_in <sc_lv<8> > Di, Wi;
	sc_in <sc_lv<24> > Si;
	sc_out <sc_lv<24> > Result; 
	sc_out <sc_lv<8> > Dout, Wout;
	
	// Signal Declaration
	sc_signal <sc_logic> Load_Result;
	
	PE_datapath* DataPath; 
	PE_controller* Controller; 

	SC_CTOR(PE){
		DataPath = new PE_datapath ("Datapath"); 
			(*DataPath) (clk, rst, startPE, busyPE, Di, Wi, Si, Load_Result, Result, Dout, Wout);	

		Controller = new PE_controller ("Controller"); 
			(*Controller) (rst, clk, startPE, busyPE, Load_Result);
		}
};
