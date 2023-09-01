#include "Systolic_Array_TopModule.h"

#define Num_of_Rows 3
#define Num_of_Columns 3
#define Num_of_Iterations 2
SC_MODULE(Systolic_Array_TestBench){

	// Port Declaration
	sc_signal <sc_logic> clk, rst;
	sc_signal <sc_logic> start, busy;
	sc_signal <sc_lv<8> > Di[Num_of_Rows]; 
	sc_signal <sc_lv<8> > Wi[Num_of_Columns];
	sc_signal <sc_lv<24> > Results[Num_of_Columns];
	sc_signal <sc_logic> done;
	
	Systolic_Array<Num_of_Rows, Num_of_Columns, Num_of_Iterations>* Systolic_Array_Test; 

	SC_CTOR (Systolic_Array_TestBench){
	
		Systolic_Array_Test = new Systolic_Array <Num_of_Rows, Num_of_Columns, Num_of_Iterations> ("Systolic_Array_Test"); 
			Systolic_Array_Test->clk(clk); 
			Systolic_Array_Test->rst(rst);
			Systolic_Array_Test->start(start);
			Systolic_Array_Test->busy(busy);
			for(int i = 0; i < Num_of_Rows; i++)
				Systolic_Array_Test->Di[i](Di[i]);
			for(int i = 0; i < Num_of_Columns; i++)
				Systolic_Array_Test->Wi[i](Wi[i]);	
			for(int i = 0; i < Num_of_Columns; i++)
				Systolic_Array_Test->Results[i](Results[i]);
			Systolic_Array_Test->done(done);
		//
		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking); 
		SC_METHOD(displaying);
			sensitive << Results[0] << Results[1] << Results[2];
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
	void displaying(); 
}; 
