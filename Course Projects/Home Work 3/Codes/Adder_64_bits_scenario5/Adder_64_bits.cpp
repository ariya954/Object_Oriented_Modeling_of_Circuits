#include "Adder_64_bits.h"

Adder_64_bits_DataPath::Adder_64_bits_DataPath (bus& a, bus& b, bus& ci, bus& internal_4_bits_adder_inputs_selector, bus& internal_4_bits_adder_ci_selector, bus& co, bus& sum) 
	:	a(&a), b(&b), ci(&ci), internal_4_bits_adder_inputs_selector(&internal_4_bits_adder_inputs_selector), internal_4_bits_adder_ci_selector(&internal_4_bits_adder_ci_selector), co(&co), sum(&sum)
{
	this->a = &a; 
	this->b = &b; 
	this->ci = &ci;
	this->internal_4_bits_adder_inputs_selector = &internal_4_bits_adder_inputs_selector;
	this->internal_4_bits_adder_ci_selector = &internal_4_bits_adder_ci_selector;
	this->sum = &sum; 
	this->co = &co; 
}

Adder_64_bits_Controller::Adder_64_bits_Controller (bus& rst, bus& clk, bus& start, bus& internal_4_bits_adder_inputs_selector, bus& internal_4_bits_adder_ci_selector, bus& done)
{
	this->rst = &rst; 
	this->clk = &clk; 
	this->start = &start; 
	this->internal_4_bits_adder_inputs_selector = &internal_4_bits_adder_inputs_selector;
	this->internal_4_bits_adder_ci_selector = &internal_4_bits_adder_ci_selector;
	this->done = &done;	

	Nstate = 0;
	Pstate= 0;
}

Adder_64_bits::Adder_64_bits (bus& rst, bus& clk, bus& start, bus& a, bus& b, bus& ci, bus& co, bus& sum, bus& done)
{
	this->rst = &rst; 
	this->clk = &clk; 
	this->start = &start;
	this->a = &a;
	this->b = &b; 
	this->ci = &ci;
	this->co = &co;
	this->sum = &sum;
	this->done = &done;

	this->DataPath = new Adder_64_bits_DataPath(a, b, ci, internal_4_bits_adder_inputs_selector, internal_4_bits_adder_ci_selector, co, sum);
	this->Controller = new Adder_64_bits_Controller(rst, clk, start, internal_4_bits_adder_inputs_selector, internal_4_bits_adder_ci_selector, done);

}

void Adder_64_bits_DataPath::evl ()
{
	int sel = (4 * internal_4_bits_adder_inputs_selector->to_uint());
	bus a_input = a->range(sel, sel + 3);
	bus b_input = b->range(sel, sel + 3);
	bus ci_input = (*internal_4_bits_adder_ci_selector == "0") ? *ci : *co;
	bus partial_sum = sum->range(sel, sel + 3);
	Adder adder_4_bits(a_input, b_input, ci_input, *co, partial_sum);
	adder_4_bits.evl();
	sum->fill_given_range(sel, sel + 3, partial_sum.get_bus_values());
}

void Adder_64_bits_Controller::evl () 
{
	switch (Pstate){
		case 0: 
			*done = "1";
			*internal_4_bits_adder_inputs_selector = "0000";
			*internal_4_bits_adder_ci_selector = "0";			
			if(*start == "1") Nstate = 1;
			else Nstate = 0; break;
		case 1:
			*done = "0";
			Nstate = 2;
			break;
		case 2:
			if(internal_4_bits_adder_inputs_selector->to_uint() == 17) Nstate = 0;
			else
			{
				*internal_4_bits_adder_inputs_selector = *internal_4_bits_adder_inputs_selector + "1";
				*internal_4_bits_adder_ci_selector = "1";
				Nstate = 2;
			} 
			break;
		default:
			Pstate = 0;
			break;			
	}

	if (*rst == "1") Pstate = 0;
	else if (*clk == "P") Pstate = Nstate;
}

void Adder_64_bits::evl ()
{
	this->Controller->evl();
	this->DataPath->evl();
}