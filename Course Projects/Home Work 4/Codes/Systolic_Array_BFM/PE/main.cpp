#include "PE_TestBench.cpp"

int sc_main (int argc, char **argv){
	
	PE_TestBench PE ("testbench");  

	sc_start (12000, SC_NS);
	return 0; 
}