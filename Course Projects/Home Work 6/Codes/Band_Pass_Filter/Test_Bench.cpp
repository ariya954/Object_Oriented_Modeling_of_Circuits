#include "Band_Pass_Filter.h"
#include "Sine_Wave_Generator.h"


int sc_main (int argc , char *argv[]) {
  	sc_core::sc_set_time_resolution(10.0, sc_core::SC_NS);
	
	sc_signal <double> Vin, Vout;

	band_pass_filter Band_Pass_Filter("Band_Pass_Filter", 200, 1000, 2.5e-6, 1.0e-6);
	sine_wave_generator Sine_Wave_Generator("Sine_Wave_Generator");
 
	Sine_Wave_Generator.out(Vin);
	Band_Pass_Filter.input(Vin);
	Band_Pass_Filter.output(Vout);

	sca_trace_file* trace_file = sca_create_vcd_trace_file("trace_file");


	sca_trace(trace_file, Vin, "Vin");
	sca_trace(trace_file, Vout, "Vout");

	sc_start(400, SC_MS);

  	return 0;
}