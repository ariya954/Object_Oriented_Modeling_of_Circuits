#include "Digital_System_TB.cpp"

int sc_main (int argc , char *argv[]) {
   digital_system_TB Digital_System_TB ("Digital_System_Test");
   sc_start(200000, SC_NS);
   return 0;
}