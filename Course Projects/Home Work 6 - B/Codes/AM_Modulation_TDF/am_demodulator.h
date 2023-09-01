#include "half_rectifier.h"
#include "low_pass_filter.h"

SC_MODULE(am_demodulator)
{
	sca_tdf::sca_in<double> am_modulated_signal;
	sca_tdf::sca_out<double> received_message;
	
	half_rectifier Half_Rectifier;
	low_pass_filter Low_Pass_Filter;
	
	SC_CTOR(am_demodulator)
	: am_modulated_signal("am_modulated_signal"), received_message("received_message"), Half_Rectifier("Half_Rectifier"), Low_Pass_Filter("Low_Pass_Filter", 2, 1e-6),
	Half_Rectifier_out("Half_Rectifier")
	{
		Half_Rectifier.in(am_modulated_signal);
		Half_Rectifier.out(Half_Rectifier_out);
		Low_Pass_Filter.input(Half_Rectifier_out);
		Low_Pass_Filter.output(received_message);
	}
	
	private:
		sca_tdf::sca_signal<double> Half_Rectifier_out;
};
