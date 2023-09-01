#include "interfaceClasses.h"

// data and address type, number of Inititiators
template <class T> 
class memoryAccess : public requestMem_if<T>, public memRespond_if<T>
{
	T incomingData;
	T incomingAddress;
	T outgoingData;
	bool read;
	bool memoryRequested;
	sc_event memoryCalledFor;
	sc_event memoryCompleted;

	sc_mutex busBusy;
	
public:
	memoryAccess() : memoryRequested(false) {};
	~memoryAccess() {};

	void requestMem(T &data, T &address, bool rwbar){
		wait(0, SC_NS);
		busBusy.lock();
		if (!rwbar) incomingData = data; 
		incomingAddress = address;
		read = rwbar;
		memoryRequested = true; 
		memoryCalledFor.notify();
		wait(memoryCompleted);
		busBusy.unlock();
	}
	void memForward(T &data, T &address, bool &rwbar){
		if (!memoryRequested) wait(memoryCalledFor);
		memoryRequested = false;
		if (!read) data = incomingData;
		address = incomingAddress;
		rwbar = read;
		// Ready for Backward operation
	}
	void memBackward(T &data){
		outgoingData = data;
		wait(0, SC_NS);
		memoryCompleted.notify();
	}
};
