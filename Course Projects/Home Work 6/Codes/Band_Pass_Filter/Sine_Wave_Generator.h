#include "systemc.h"
#include "systemc-ams.h"
#include <stdio.h>

#define PI 3.1415926535897932384626433832795

using namespace std;

SC_MODULE(sine_wave_generator)
{
	sc_out<double> out;
	SC_CTOR(sine_wave_generator){

		SC_THREAD(sine_wave_generation);
	}
	void sine_wave_generation();
};
	
	void sine_wave_generator::sine_wave_generation()
	{
		double t = 0;
		double freq = 10.0;
		while (1){
			wait(1000, SC_NS);
			out.write(sin( 2.0 * PI * freq * t ) );
			t = t + 0.000001;
		}
	};
