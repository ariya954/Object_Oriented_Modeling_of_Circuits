#include <systemc.h>
#include "Register.h"
#include "Adder.h"
#include "Mult.h"

SC_MODULE(PE_datapath){
	
	// Port Declaration
	sc_in <sc_logic> clk, rst;
	sc_in <sc_logic> startPE, busyPE;
	sc_in <sc_lv<8> > Di, Wi;
	sc_in <sc_lv<24> > Si;
	sc_in <sc_logic> Load_Result;
	sc_out <sc_lv<24> > Result; 
	sc_out <sc_lv<8> > Dout, Wout;
	
	// Signal Declaration
	sc_signal <sc_lv<24> > Mult_Result;
	sc_signal <sc_lv<24> > MAC_Result;
	
	// Instantiation 
	Register<8>* input_data;
	Register<8>* input_weight;
	Register<24>* result;
	Adder<24>* adder;
	Mult<8, 24>* multiplier;
	
	SC_CTOR(PE_datapath){
	
		input_data = new Register<8>("Data_Register");
			input_data->clk(clk); 
			input_data->rst(rst);
			input_data->load(busyPE);
			input_data->regin(Di); 
			input_data->regout(Dout);

		input_weight = new Register<8>("Weight_Register");
			input_weight->clk(clk); 
			input_weight->rst(rst);
			input_weight->load(startPE);
			input_weight->regin(Wi); 
			input_weight->regout(Wout);

		multiplier = new Mult<8, 24>("Multiplier");
			multiplier-> in1(Dout);
			multiplier->in2(Wout); 
			multiplier->out(Mult_Result);
			
		adder = new Adder<24>("adder");
			adder->in1(Si);
			adder->in2(Mult_Result);
			adder->out(MAC_Result);
			
		result = new Register<24>("Result_Register");
			result->clk(clk); 
			result->rst(rst);
			result->load(Load_Result);
			result->regin(MAC_Result); 
			result->regout(Result);
	}
};
