#include "interfaceClasses.h"

template <class T, int Max>
class fifo : public put_if<T>, public get_if<T>
{
	int size;
	int elems, head;
	T queueContents[Max];
	sc_event put_event, get_event;
	
	public:
		fifo() : size(Max), elems(0), head(0) {};
		~fifo() {};
		void put(T data){
			if (elems == size) wait(get_event);
			queueContents[(head + elems) % size] = data;
			elems = elems + 1;
			put_event.notify();
		}
		void get(T &data){
			if (elems == 0) wait(put_event);
			data = queueContents[head];
			elems = elems - 1;
			head = (head + 1) % size;
			get_event.notify();
		}
		bool is_fifo_empty(){
			if(elems > 0) 
				return false;
			return true;
		}
};
