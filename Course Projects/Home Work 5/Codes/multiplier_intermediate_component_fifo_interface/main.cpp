#include "multiplier_intermediate_component_fifo_interface_TB.cpp"

int sc_main (int argc , char *argv[]) {
   multiplier_intermediate_component_fifo_interface_TB FPG1("multiplier_intermediate_component_fifo_interface_Test");
   sc_start(200000, SC_NS);
   return 0;
}