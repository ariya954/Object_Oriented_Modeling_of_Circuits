#include <systemc.h>

template <int Register_WIDTH>
SC_MODULE(Register){
	sc_in <sc_logic> clk, rst, load;
	sc_in <sc_lv<Register_WIDTH> > regin;
	sc_out <sc_lv<Register_WIDTH> > regout;

	SC_HAS_PROCESS(Register);
	Register(sc_module_name);

	void registering();
};

template <int Register_WIDTH> 
Register<Register_WIDTH>::Register(sc_module_name)
{
	SC_METHOD(registering);
	sensitive << clk << rst;
}

template <int Register_WIDTH> 
void Register<Register_WIDTH>::registering()
{
	sc_lv<Register_WIDTH> tmp;
	if (rst =='1')
	{
		for (int i = 0; i < Register_WIDTH; i++)
			tmp[i] = sc_logic(0);
		regout = tmp;
	}
	else if ((clk->event()) && (clk == '1')){
		if (load == '1') regout = regin;
	}
};
