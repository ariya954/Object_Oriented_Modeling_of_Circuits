#include <systemc.h>

template <int in_WIDTH, int out_WIDTH> 
SC_MODULE (Mult) {
	sc_in <sc_lv<in_WIDTH> > in1, in2; 
	sc_out <sc_lv<out_WIDTH> > out; 

	SC_CTOR (Mult)
	{
		SC_METHOD (multiplying); 
		sensitive << in1 << in2; 
	}

	void multiplying() 
	{
		sc_lv <out_WIDTH> vout;
		vout = (sc_uint<in_WIDTH>)in1 * (sc_uint<in_WIDTH>) in2;
		out = vout;
	}
};
