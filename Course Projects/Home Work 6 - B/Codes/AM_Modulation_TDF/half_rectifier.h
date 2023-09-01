#include "systemc.h"
#include "systemc-ams.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

SCA_TDF_MODULE(half_rectifier)
{
	sca_tdf::sca_in<double> in;
	sca_tdf::sca_out<double> out;

	SCA_CTOR(half_rectifier) : in("in"), out("out") {}

	void processing()
	{
		if(in.read() < 0)
			out.write(in.read());
		else
			out.write(0.0);
	}
};

