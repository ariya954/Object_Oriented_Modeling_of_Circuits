#include "mixer.h"
#include "sine_wave.h"

SC_MODULE(am_modulator)
{
	sca_tdf::sca_out<double> am_modulated_signal;
	
	sca_tdf::sca_signal<double> carrier_signal;
	sca_tdf::sca_signal<double> message_signal;
	
	sin_src carrier;
	sin_src message;
	
	mixer mix;
	
	SC_CTOR(am_modulator)
	: am_modulated_signal("am_modulated_signal"),
	carrier("carrier", 60.0, 1.0e6, sca_core::sca_time( 1.0, sc_core::SC_NS ) ),
	message("message", 1.0, 1.0e4, sca_core::sca_time( 100.0, sc_core::SC_NS ) ),
	mix("mix")
	{
		carrier.out(carrier_signal);
		message.out(message_signal);
		mix.input_carrier(carrier_signal);
		mix.input_message(message_signal);
		mix.modulated_signal(am_modulated_signal);
	}

};
