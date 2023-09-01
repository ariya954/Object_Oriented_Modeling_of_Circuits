#include "systemc.h"
#include "systemc-ams.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

SCA_TDF_MODULE(mixer)
{
	sca_tdf::sca_in<double> input_message; // input port message signal
	sca_tdf::sca_in<double> input_carrier; // input port carrier signal
	sca_tdf::sca_out<double> modulated_signal; // output port modulated signal

	SCA_CTOR(mixer)
	: input_message("input_message"), input_carrier("input_carrier"), modulated_signal("out"), rate(100) {} 
	
	void set_attributes()
	{
		input_message.set_rate(1);
		input_carrier.set_rate(100);
		modulated_signal.set_rate(rate);
	}
	void processing()
	{
		for(unsigned long i = 0; i < rate; i++)
		{
			modulated_signal.write( (input_message.read() * input_carrier.read(i)) + input_carrier.read(i), i );

		}
	}
	private:
		unsigned long rate;
};
