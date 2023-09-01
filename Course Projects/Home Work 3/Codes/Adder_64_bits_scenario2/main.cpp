#include "Adder_64_bits.cpp"

int main()
{
	bus rst = "0";
	bus clk;

	// generate adder's inputs scenario 2
	bus a = "0000000000000000000000000000000000000000000000001100111100001000";
	bus b = "1100100000000000000000000000000000000000000000000000001100001000";

	bus ci = "1";
	bus start = "1";

	// At first sum, co and done are initialized to zero
	bus sum = "0000000000000000000000000000000000000000000000000000000000000000";
	bus co = "0";
	bus done = "0";

	Adder_64_bits adder(rst, clk, start, a, b, ci, co, sum, done);

    // generate sequence of clock signal
	string clock = "NPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNP";

	for(int i = 0; i < clock.size(); i++)
	{
		string clock_state = "";
		clk = clock_state + clock.at(i);
		adder.set_clk(&clk);
		adder.evl();
	}

	//print the outputs
	cout << "A input: " << a.get_bus_values()   << "\n\n";
	cout << "B input: " << b.get_bus_values()   << "\n\n";
	cout << "Sum:     " << sum.get_bus_values() << "\n\n";	
	cout << "Co:      " << co.get_bus_values()  << "\n";		
}