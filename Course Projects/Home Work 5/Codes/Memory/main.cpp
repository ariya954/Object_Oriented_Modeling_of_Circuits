#include "Memory_TB.cpp"

int sc_main (int argc , char *argv[]) {
   memory_TB Memory_TB ("Memory_Test");
   sc_start(200000, SC_NS);
   return 0;
}

