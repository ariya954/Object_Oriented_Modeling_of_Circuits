#include "systemc.h"
#include "systemc-ams.h"
#include <stdio.h>

using namespace std;

SC_MODULE(low_pass_filter)
{
	sca_tdf::sca_in<double> input;
	sca_tdf::sca_out<double> output;
	
	sca_eln::sca_r Rf;
	sca_eln::sca_c cf;	
	sca_eln::sca_tdf::sca_isource TDF_to_ELN_converter;
	sca_eln::sca_tdf::sca_vsink ELN_to_TDF_converter;

	low_pass_filter(sc_core::sc_module_name, double Rf_value, double cf_value)
		: input("input"), output("output"),
		Rf("Rf", Rf_value), cf("cf", cf_value), TDF_to_ELN_converter("TDF_to_ELN_converter"), ELN_to_TDF_converter("ELN_to_TDF_converter")
	{
		
		TDF_to_ELN_converter.inp(input);
		TDF_to_ELN_converter.p(out);
		TDF_to_ELN_converter.n(gnd);
		
		Rf.p(out);
		Rf.n(gnd);

		cf.p(gnd);
		cf.n(out);	

		ELN_to_TDF_converter.p(out);
		ELN_to_TDF_converter.n(gnd);
		ELN_to_TDF_converter.outp(output);		
	}

private:
	sca_eln::sca_node out;
	sca_eln::sca_node_ref gnd;
};
