#include "Primitives_Classes.cpp"
#define adder_inputs_width 8
using namespace std; 

class Adder_64_bits_DataPath{
	bus *a, *b;
	bus *ci;
	bus *internal_4_bits_adder_inputs_selector;
	bus *internal_4_bits_adder_ci_selector;
	bus *co;
	bus *sum;
	public:
		Adder_64_bits_DataPath(bus& a, bus& b, bus& ci, bus& internal_4_bits_adder_inputs_selector, bus& internal_4_bits_adder_ci_selector, bus& co, bus& sum);
		void evl ();
};

class Adder_64_bits_Controller{
	bus *rst;
	bus *clk;
	bus *start;
	bus *done;
	bus *internal_4_bits_adder_inputs_selector;
	bus *internal_4_bits_adder_ci_selector;
	int Nstate, Pstate;
	public:
		Adder_64_bits_Controller(bus& rst, bus& clk, bus& start, bus& internal_4_bits_adder_inputs_selector, bus& internal_4_bits_adder_ci_selector, bus& done);
		void evl ();
};

class Adder_64_bits{
	Adder_64_bits_DataPath *DataPath;
	Adder_64_bits_Controller *Controller;
	bus *rst, *clk;
	bus *start;
	bus *a, *b;
	bus *ci;
	bus internal_4_bits_adder_inputs_selector;
	bus internal_4_bits_adder_ci_selector;
	bus *co;
	bus *sum;
	bus *done;
	public:
		Adder_64_bits(bus& rst, bus& clk, bus& start, bus& a, bus& b, bus& ci, bus& co, bus& sum, bus& done);
		
		void set_rst(bus *given_rst) { rst = given_rst; }; 
		void set_clk(bus *given_clk) { clk = given_clk; };
		void set_start(bus *given_start) { start = given_start; }; 		 		
		void evl ();
};
