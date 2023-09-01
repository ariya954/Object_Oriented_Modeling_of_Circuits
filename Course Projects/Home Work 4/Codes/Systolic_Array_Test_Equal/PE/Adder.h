#include <systemc.h>

template <int Adder_WIDTH> 
SC_MODULE (Adder){
	sc_in <sc_lv<Adder_WIDTH> > in1, in2; 
	sc_out <sc_lv<Adder_WIDTH> > out; 
	
	SC_CTOR (Adder)
	{
		SC_METHOD(Adding); 
		sensitive << in1 << in2;
	}
	void Adding()
	{
		sc_lv<Adder_WIDTH> vout; 
		vout = (sc_uint<Adder_WIDTH>) in1 + (sc_uint<Adder_WIDTH>) in2; 
		out = vout; 
	}
};
