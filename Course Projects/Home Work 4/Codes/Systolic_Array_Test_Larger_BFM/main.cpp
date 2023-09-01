#include "Systolic_Array_TestBench.cpp"

int sc_main (int argc, char **argv){
	
	Systolic_Array_TestBench Systolic_Array ("testbench");  

	sc_trace_file* vcdfile;
	vcdfile = sc_create_vcd_trace_file("Systolic_Array_test");
	sc_trace(vcdfile, Systolic_Array.clk, "clk");
	sc_trace(vcdfile, Systolic_Array.rst, "rst");
	sc_trace(vcdfile, Systolic_Array.start, "start"); 
	sc_trace(vcdfile, Systolic_Array.busy, "busy");
	sc_trace(vcdfile, Systolic_Array.done, "done");
	sc_trace(vcdfile, Systolic_Array.Results[0], "Result_1");
	sc_trace(vcdfile, Systolic_Array.Results[1], "Result_2");
	sc_trace(vcdfile, Systolic_Array.Results[2], "Result_3");

	sc_start (24000, SC_NS);
	return 0; 
}