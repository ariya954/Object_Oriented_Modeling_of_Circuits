#include <systemc.h>

SC_MODULE(PE){

	// Port Declaration
	sc_in <sc_logic> clk, rst;
	sc_in <sc_logic> startPE, busyPE;
	sc_in <sc_lv<8> > Di, Wi;
	sc_in <sc_lv<24> > Si;
	sc_out <sc_lv<24> > Result; 
	sc_out <sc_lv<8> > Dout, Wout;
	
	SC_CTOR(PE){
        	SC_THREAD(operation)
           		sensitive << clk << rst;
	}
	
	void operation();
};

void PE::operation()
{
	while (true)
	{
		if (rst == '1')
		{
			Result = 0;
			Dout = 0;
			Wout = 0;	
		}
		else if ((clk == '1') && (clk->event()))
		{
			if (startPE == '1')
				Wout = Wi;
			
			if(busyPE == '1')
			{
				Dout = Di;
				Result = (Di->read().to_uint() * Wi->read().to_uint()) + Si->read().to_uint();
			} 
		}
		wait();
	}
}
