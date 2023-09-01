#include "Systolic_Array_TestBench.h"

void Systolic_Array_TestBench::inputing(){
        // Preloading Weights
		start = SC_LOGIC_1;
		wait(200, SC_NS);
		Wi[0] = "00000000"; Wi[1] = "00000001"; Wi[2] = "00000001";
		wait(100, SC_NS);
		Wi[0] = "00000000"; Wi[1] = "00000001"; Wi[2] = "00000001";
		wait(100, SC_NS);
		Wi[0] = "00000000"; Wi[1] = "00000001"; Wi[2] = "00000001";		
		wait(1000, SC_NS);
		start = SC_LOGIC_0;
		wait(500, SC_NS);

        // loading Input Matrix
        Di[0] = "00000000"; Di[1] = "00000000"; Di[2] = "00000000";
		busy = SC_LOGIC_1;
		wait(250, SC_NS);
		Di[0] = "00000001"; Di[1] = "00000000"; Di[2] = "00000000";
		wait(100, SC_NS);
		Di[0] = "00000001"; Di[1] = "00000001"; Di[2] = "00000000";
		wait(100, SC_NS);
		Di[0] = "00000000"; Di[1] = "00000000"; Di[2] = "00000000";	
		wait(100, SC_NS);
		Di[0] = "00000000"; Di[1] = "00000000"; Di[2] = "00000000";	
		wait(100, SC_NS);
		Di[0] = "00000000"; Di[1] = "00000000"; Di[2] = "00000000";
		wait(1000, SC_NS);
		busy = SC_LOGIC_0;
}

void Systolic_Array_TestBench::clocking(){
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

void Systolic_Array_TestBench::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};

void Systolic_Array_TestBench::displaying(){
	cout << " Done = " << done.read() << endl; 
	cout << " Result 1 = " << Results[0].read() << endl; 
	cout << " Result 2 = " << Results[1].read() << endl; 
	cout << " Result 3 = " << Results[2].read() << endl;
}