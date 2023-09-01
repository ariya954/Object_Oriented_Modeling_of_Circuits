#include "PE_TestBench.h"

void PE_TestBench::inputing(){
	    Wi = "00000011";
		startPE = SC_LOGIC_0;
		wait(100, SC_NS);
		startPE = SC_LOGIC_1;
		wait(100, SC_NS);
		startPE = SC_LOGIC_0;
		wait(100, SC_NS);
		busyPE = SC_LOGIC_1;
		wait(500, SC_NS);
		Si = "111110000000000000000000";
		Di = "10000000";
		busyPE = SC_LOGIC_0;
		wait(100, SC_NS);
		busyPE = SC_LOGIC_1;
		wait(500, SC_NS);
		Si = "111111111111111111111111";
		Di = "00000001";
		busyPE = SC_LOGIC_0;
		wait(100, SC_NS);
		busyPE = SC_LOGIC_1;
		wait(500, SC_NS);
		Si = "000000000000000000011111";
		Di = "10000000";
		busyPE = SC_LOGIC_0;
		wait(100, SC_NS);
		busyPE = SC_LOGIC_1;
		wait(500, SC_NS);
}

void PE_TestBench::clocking(){
	int i; 
	clk = sc_logic('1'); 
	for (i = 0; i <= 50; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}

void PE_TestBench::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};

void PE_TestBench::displaying(){
	cout << " Si = " << Si.read() << endl; 
	cout << " Di = " << Di.read() << endl; 
	cout << " Wi = " << Wi.read() << endl; 	
	cout << " Result = " << Result.read() << endl; 
}