#include "PE/PE_TopModule.h"

template <int Num_of_Rows, int Num_of_Columns> 
SC_MODULE(systolic_array_datapath){
	
	// Port Declaration
	sc_in <sc_logic> clk, rst;
	sc_in <sc_logic> startPE, busyPE;
	sc_in <sc_lv<8> > Di[Num_of_Rows];
	sc_in <sc_lv<8> > Wi[Num_of_Columns];
	sc_out <sc_lv<24> > Results[Num_of_Columns]; 
	
	// Signal Declaration
	sc_signal <sc_lv<24> > Result[Num_of_Rows][Num_of_Columns];
	sc_signal <sc_lv<8> > Dout[Num_of_Rows][Num_of_Columns];
	sc_signal <sc_lv<8> > Wout[Num_of_Rows][Num_of_Columns];	
	sc_signal <sc_lv<24> > zero;	
	
	// Instantiation 
	PE* PEs[Num_of_Rows][Num_of_Columns];
	
	SC_CTOR(systolic_array_datapath){
		zero = 0;
		for(int row = 0; row < Num_of_Rows; row++)
			for(int column = 0; column < Num_of_Columns; column++){
				PEs[row][column] = new PE ("PE"); 
				PEs[row][column]->clk(clk); 
				PEs[row][column]->rst(rst); 
				PEs[row][column]->startPE(startPE); 
				PEs[row][column]->busyPE(busyPE); 
				if(column == 0)
					PEs[row][column]->Di(Di[row]);
				else
					PEs[row][column]->Di(PEs[row][column - 1]->Dout);
				if(row == 0)
					PEs[row][column]->Wi(Wi[column]);
				else
					PEs[row][column]->Wi(PEs[row - 1][column]->Wout);
				if(row == 0)
					PEs[row][column]->Si(zero);
				else
					PEs[row][column]->Si(PEs[row - 1][column]->Result);
				if(row != Num_of_Rows - 1)
					PEs[row][column]->Result(Result[row][column]);
				else
					PEs[row][column]->Result(Results[column]);
				PEs[row][column]->Dout(Dout[row][column]);
				PEs[row][column]->Wout(Wout[row][column]);
			}
	}
};
