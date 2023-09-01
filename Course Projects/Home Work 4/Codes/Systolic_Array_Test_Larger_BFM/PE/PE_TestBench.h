#include "PE_TopModule.h"

SC_MODULE(PE_TestBench){

	// Port Declaration
	sc_signal <sc_logic> clk, rst;
	sc_signal <sc_logic> startPE, busyPE;
	sc_signal <sc_lv<8> > Di, Wi;
	sc_signal <sc_lv<24> > Si;
	sc_signal <sc_lv<24> > Result; 
	sc_signal <sc_lv<8> > Dout, Wout;
	
	PE* PE_Test; 

	SC_CTOR (PE_TestBench){
		PE_Test = new PE ("PE_Test"); 
			PE_Test->clk(clk); 
			PE_Test->rst(rst); 
			PE_Test->startPE(startPE); 
			PE_Test->busyPE(busyPE); 
			PE_Test->Di(Di);
			PE_Test->Wi(Wi);
			PE_Test->Si(Si);
			PE_Test->Result(Result);
			PE_Test->Dout(Dout);
			PE_Test->Wout(Wout);
		//
		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking); 
		SC_METHOD(displaying);
			sensitive << Result;
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
	void displaying(); 
}; 
