#include "multiplier_intermediate_component_fifo_interface.h"

void intermediate_component::put_operands() {
	while(true){
		wait();
		if(Addr_from_processor.read() == "01"){
			if(out->is_fifo_empty()){
				input_control_signals = "00000000000000000000000000000001";
				wait(300, SC_NS);
				for (int i = 0; i < 32; i++)
				{
					wait(100, SC_NS);
					out->put(output_data);
					cout << "Data: (" << output_data << ") was transmitted at: "
						 << sc_time_stamp() << '\n';
				}
			}
			else
				input_control_signals = "00000000000000000000000000000000";
		}
	}
}

void multiplier_16_bit::get_operands_and_evaluate() {
	while(true){
		wait();
		if(Addr_from_processor.read() == "10")
			if(input_control_signals[0] == sc_logic('1')){
				control_signals = "00000000000000000000000000000000";
				sc_lv<32> input_data;
				in->get(input_data);

				sc_lv<16> A_input, B_input;
				A_input = input_data.range(15, 0);
				B_input = input_data.range(31, 16);

				mult_result = (sc_lv<32>)(A_input.to_uint() * B_input.to_uint());

				wait(100, SC_NS);
				control_signals = "00000000000000000000000000000010";

				cout << "A input: " << A_input.to_uint() << "\n";
				cout << "B input: " << B_input.to_uint() << "\n";
				cout << "Mult Result: " << output_data.read().to_uint() 
							 << " (at " << sc_time_stamp() << ")\n";
			}
	}
}