#include "systemc.h"
#include "systemc-ams.h"
#include <stdio.h>

using namespace std;

SC_MODULE(band_pass_filter)
{
	sc_core::sc_in<double> input;
	sc_core::sc_out<double> output;
	
	sca_eln::sca_r R1;
	sca_eln::sca_r R_Load;
	sca_eln::sca_c c1;
	sca_eln::sca_c c2;	
	sca_eln::sca_de::sca_vsource DE_to_ELN_converter;
	sca_eln::sca_de::sca_vsink ELN_to_DE_converter;

	band_pass_filter(sc_core::sc_module_name, double R1_value, double R_Load_value, double c1_value, double c2_value)
		: input("input"), output("output"),
		R1("R1", R1_value), R_Load("R_Load", R_Load_value), c1("c1", c1_value), c2("c2", c2_value), DE_to_ELN_converter("DE_to_ELN_converter"), ELN_to_DE_converter("ELN_to_DE_converter")
	{
		
		DE_to_ELN_converter.inp(input);
		DE_to_ELN_converter.p(in_R1);
		DE_to_ELN_converter.n(gnd);
		DE_to_ELN_converter.set_timestep(1, sc_core::SC_US);
		
		R1.p(in_R1);
		R1.n(in_C2);
		
		R_Load.p(out_C2);
		R_Load.n(gnd);

		c1.p(in_C2);
		c1.n(gnd);

		c2.p(in_C2);
		c2.n(out_C2);		

		ELN_to_DE_converter.p(out_C2);
		ELN_to_DE_converter.n(gnd);
		ELN_to_DE_converter.outp(output);		
	}

private:
	sca_eln::sca_node in_R1, in_C2, out_C2;
	sca_eln::sca_node_ref gnd;
};
