#include <systemc.h>

template <class T>
class requestMem_if : virtual public sc_interface
{
public:
	virtual void requestMem(T &data, T &address, bool rwbar) = 0;

};

template <class T>
class memRespond_if : virtual public sc_interface
{
public:
   virtual void memForward(T &data, T &address, bool &rwbar) = 0;
   virtual void memBackward(T &data) = 0;
};
