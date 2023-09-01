#include "memoryAccessChannel.h"

SC_MODULE(memory) {

	sc_in <sc_logic> clk, rst, Ctrl;
	sc_in <sc_lv<2> > Addr;
	sc_in <sc_lv<32> > input_address;
	sc_in <sc_lv<32> > input_data;
	sc_out <sc_lv<32> > output_data;
	
	sc_lv<32>* mem; 
	
	sc_export<memRespond_if<sc_lv<32> > > in;
	memoryAccess<sc_lv<32> >* memBus;

	SC_CTOR(memory) {
		mem = new sc_lv<32>[256];
		for (int i = 0; i < 256; i++) mem[i] = (sc_lv<32>) i;

		memBus = new memoryAccess<sc_lv<32> >;
		SC_THREAD (requesting);
			sensitive << clk << rst;		
		SC_THREAD (responding);
			sensitive << clk << rst;
    	}
    	
	void requesting();
	void responding();
	virtual ~memory(){
		delete[] mem;
	}
};

void memory::requesting() {
	while(true){
		wait();
		if(Addr.read() == "00"){
			bool rwbar = (Ctrl.read() == '1') ? true : false;
			sc_lv<32> data = input_data;
			sc_lv<32> address = input_address;
			memBus->requestMem(data, address, rwbar);
		}
	}
}

void memory::responding() {
	while (true)
	{
		wait();
		if(Addr.read() == "00"){
			bool rwbar = (Ctrl.read() == '1') ? true : false;
			sc_lv<32> data = input_data;
			sc_lv<32> address = input_address;
			memBus->memForward(data, address, rwbar);
			if (rwbar) 
				output_data = mem[input_address.read().to_uint()];
			else mem[input_address.read().to_uint()] = input_data;
			memBus->memBackward(data);
			cout << "Memory " << (rwbar ? "READ" : "WROTE") 
			     << " Data:" << (rwbar ? output_data.read().to_uint() : input_data.read().to_uint())  << " Address:" << input_address.read().to_uint() 
			     << " requested by Processor \n";
		}
	}
}
