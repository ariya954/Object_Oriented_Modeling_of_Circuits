#include "Processor.h"

void processor::processor_function(){

   wait();

   // Processor choses memory to communicate with
   Addr_from_processor = "00";

   // Writing 128 data to memory start from adress 0X00000008
   output_control_signals_processor = "00000000000000000000000000000000";
   output_address_processor = "00000000000000000000000000001000";
   output_data_processor = "00000000000000110000000000000000";

   wait(0, SC_NS);

   for(int i = 0; i < 128; i++){
     wait(100, SC_NS);
     output_data_processor = output_data_processor.read().to_uint() + 1;
     output_address_processor = output_address_processor.read().to_uint() + 1;
   }

   wait(0, SC_NS);

   // Reading 128 data from memory start from adress 0X00000008   
   output_control_signals_processor = "00000000000000000000000000000001";
   output_address_processor = "00000000000000000000000000001000";

   wait(0, SC_NS);

   for(int i = 0; i < 128; i++){
     wait(100, SC_NS);
     Register_File[output_address_processor.read().to_uint() - 8] = input_data_processor;
     output_address_processor = output_address_processor.read().to_uint() + 1;
   }

   wait(0, SC_NS);

   for(int i = 0; i < 4; i++){
      // Processor choses intermediate component to communicate with
      Addr_from_processor = "01";

      wait(200, SC_NS);

      // Sending 32 32 bit data to intermediate component if fifo is empty
      if(input_control_signals_processor.read()[0] == '1'){
         for(int j = 0; j < 33; j++){
            wait(100, SC_NS);
            output_data_processor = Register_File[i*32 + j];
         }
      }

      wait(0, SC_NS);

      // Processor choses multiplier to communicate with
      Addr_from_processor = "10";

      wait(200, SC_NS);

      // Reading multiplication results from multiplier if result is ready
      for(int k = 0; k < 33; k++){
         wait(100, SC_NS);
         if(input_control_signals_processor.read()[1] == '1')
            wait(100, SC_NS);
      }

      wait(0, SC_NS);
   }
   
   Addr_from_processor = "11";
   wait(6000, SC_NS);
}