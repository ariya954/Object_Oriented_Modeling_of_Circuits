#include "am_modulator.h"
#include "am_demodulator.h"

int sc_main(int argc, char* argv[])
{
	sc_core::sc_set_time_resolution(1, sc_core::SC_FS);

	sca_tdf::sca_signal<double> am_modulated_signal;
	sca_tdf::sca_signal<double> received_message;

	am_modulator am_mod("am_mod"); // AM modulator
	am_mod.am_modulated_signal(am_modulated_signal);
	
	am_demodulator am_demod("am_demod"); // AM demodulator
	am_demod.am_modulated_signal(am_modulated_signal);
	am_demod.received_message(received_message);

	sca_trace_file* trace_file = sca_create_vcd_trace_file( "trace.vcd" );
	sca_trace( trace_file, am_mod.message_signal, "M(t)" );
	sca_trace( trace_file, am_mod.carrier_signal, "C(t)" );
	sca_trace( trace_file, am_modulated_signal, "A(t)" );
	sca_trace( trace_file, received_message, "Md(t)" );
	sc_start(250, sc_core::SC_US);
	sca_close_vcd_trace_file( trace_file );

	return 0;
}