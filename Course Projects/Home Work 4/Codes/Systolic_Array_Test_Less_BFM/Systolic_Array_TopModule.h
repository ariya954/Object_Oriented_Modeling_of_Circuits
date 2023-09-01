#include "Systolic_Array_datapath.h"
#include "Systolic_Array_controller.cpp"

template <int Num_of_Rows, int Num_of_Columns, int Num_of_Iterations> 
SC_MODULE(Systolic_Array){

	// Port Declaration
	sc_in <sc_logic> clk, rst;
	sc_in <sc_logic> start, busy;
	sc_in <sc_lv<8> > Di[Num_of_Rows]; 
	sc_in <sc_lv<8> > Wi[Num_of_Columns];
	sc_out <sc_lv<24> > Results[Num_of_Columns];
	sc_out <sc_logic> done;
	
	// Signal Declaration
	sc_signal <sc_logic> startPE, busyPE;
	
	systolic_array_datapath<Num_of_Rows, Num_of_Columns>* DataPath; 
	systolic_array_controller<Num_of_Rows, Num_of_Columns, Num_of_Iterations>* Controller; 

	SC_CTOR(Systolic_Array){
	
		DataPath = new systolic_array_datapath <Num_of_Rows, Num_of_Columns> ("Datapath");
			DataPath->clk(clk); 
			DataPath->rst(rst);
			DataPath->startPE(startPE);
			DataPath->busyPE(busyPE);
			for(int i = 0; i < Num_of_Rows; i++)
				DataPath->Di[i](Di[i]);
			for(int i = 0; i < Num_of_Columns; i++)
				DataPath->Wi[i](Wi[i]);	
			for(int i = 0; i < Num_of_Columns; i++)
				DataPath->Results[i](Results[i]);	
					
		Controller = new systolic_array_controller <Num_of_Rows, Num_of_Columns, Num_of_Iterations> ("Controller"); 
			(*Controller) (rst, clk, start, busy, startPE, busyPE, done);
		}
};
