#define and_gate_delay 3
#define not_gate_delay 2
#define xor_gate_delay 6
#define nor_gate_delay 4
#define nand_gate_delay 5

class Gate {
        protected:
		int gate_delay, changed_flag;
		char last_value = 'X';
	public:
		Gate(int given_gate_delay) {gate_delay = given_gate_delay;}
		int get_changed_flag() { return changed_flag; }
		int get_gate_delay() { return gate_delay; }
		virtual bool is_gate_ready_to_evl() = 0;
		virtual void evl() = 0;
};

class Wire {
	char value;
	public:
		Wire (char initial_value = 'X') {value = initial_value;} // constructor
		void set_value(char input_value) {value = input_value;}
		char get_value() {return value;}
}; 

class AND : public Gate{
	int number_of_inputs;
	Wire *i1, *i2, *i3, *i4, *i5, *i6, *i7, *i8, *i9, *o1;
	public:
		AND (int given_number_of_inputs) : Gate(and_gate_delay) {number_of_inputs = given_number_of_inputs;}; // constructor
		~AND(); // destructor
		void ios(Wire* w, Wire* a, Wire* b, Wire* c, Wire* d, Wire* e, Wire* f, Wire* g, Wire* h) { o1 = w; i1 = a; i2 = b;  i3 = c; i4 = d;  i5 = e; i6 = f;  i7 = g; i8 = h; }
		void ios(Wire* w, Wire* a, Wire* b, Wire* c, Wire* d, Wire* e, Wire* f, Wire* g, Wire* h, Wire* i) { o1 = w; i1 = a; i2 = b;  i3 = c; i4 = d;  i5 = e; i6 = f;  i7 = g; i8 = h; i9 = i; }
	
		bool is_gate_ready_to_evl();	
		void evl();
};

class NOT : public Gate {
	Wire *i1, *o1;
	public:
		NOT () : Gate(not_gate_delay) {};
		~NOT(); // destructor
		void ios(Wire* w, Wire* a) { o1 = w; i1 = a; }

		bool is_gate_ready_to_evl();		
		void evl ();
};

class XOR : public Gate {
	Wire *i1, *i2, *o1;
	public:
		XOR () : Gate(xor_gate_delay) {};
		~XOR(); // destructor
		void ios(Wire* w, Wire* a, Wire* b) { o1 = w; i1 = a; i2 = b; }	
		
		bool is_gate_ready_to_evl();			
		void evl();
};

class NAND : public Gate {
	int number_of_inputs;
	Wire *i1, *i2, *i3, *i4, *o1;
	public:
		NAND (int given_number_of_inputs) : Gate(nand_gate_delay) {number_of_inputs = given_number_of_inputs;}; // constructor
		~NAND(); // destructor
		void ios(Wire* w, Wire* a, Wire* b) { o1 = w; i1 = a; i2 = b; }
	        void ios(Wire* w, Wire* a, Wire* b, Wire* c) { o1 = w; i1 = a; i2 = b; i3 = c;}
	        void ios(Wire* w, Wire* a, Wire* b, Wire* c, Wire* d) { o1 = w; i1 = a; i2 = b; i3 = c; i4 = d;}
	
		bool is_gate_ready_to_evl();		                
		void evl();
};

class NOR : public Gate {
	Wire *i1, *i2, *o1;
	public:
		NOR () : Gate(nor_gate_delay) {}; // constructor
		~NOR(); // destructor
		void ios(Wire* w, Wire* a, Wire* b) { o1 = w; i1 = a; i2 = b; }
	
		bool is_gate_ready_to_evl();		
		void evl();
};

AND::~AND() {}
bool AND::is_gate_ready_to_evl() {
        if(number_of_inputs == 8){
		if ((i1->get_value()=='X')||(i2->get_value()=='X')||(i3->get_value()=='X')||(i4->get_value()=='X')||(i5->get_value()=='X')||(i6->get_value()=='X')||(i7->get_value()=='X')||(i8->get_value()=='x'))
			return false;
		else if (o1->get_value() == 'X')
			return true;
	}
        if(number_of_inputs == 9){
		if ((i1->get_value()=='X')||(i2->get_value()=='X')||(i3->get_value()=='X')||(i4->get_value()=='X')||(i5->get_value()=='X')||(i6->get_value()=='X')||(i7->get_value()=='X')||(i8->get_value()=='x')||(i9->get_value()=='x'))
			return false;
		else if (o1->get_value() == 'X')
			return true;
	}
	return false;	
}
void AND::evl () {
        if(number_of_inputs == 8){
		if ((i1->get_value()=='0')||(i2->get_value()=='0')||(i3->get_value()=='0')||(i4->get_value()=='0')||(i5->get_value()=='0')||(i6->get_value()=='0')||(i7->get_value()=='0')||(i8->get_value()=='0')) o1->set_value('0');
		else if ((i1->get_value()=='1')&&(i2->get_value()=='1')&&(i3->get_value()=='1')&&(i4->get_value()=='1')&&(i5->get_value()=='1')&&(i6->get_value()=='1')&&(i7->get_value()=='1')&&(i8->get_value()=='1')) o1->set_value('1');
		else o1->set_value('X');
	}	
	else{
		if ((i1->get_value()=='0')||(i2->get_value()=='0')||(i3->get_value()=='0')||(i4->get_value()=='0')||(i5->get_value()=='0')||(i6->get_value()=='0')||(i7->get_value()=='0')||(i8->get_value()=='0')||(i9->get_value()=='0')) o1->set_value('0');
		else if ((i1->get_value()=='1')&&(i2->get_value()=='1')&&(i3->get_value()=='1')&&(i4->get_value()=='1')&&(i5->get_value()=='1')&&(i6->get_value()=='1')&&(i7->get_value()=='1')&&(i8->get_value()=='1')&&(i9->get_value()=='1')) o1->set_value('1');
		else o1->set_value('X');	
	}
	
	changed_flag = (o1->get_value() != last_value) ? 1 : 0;
	last_value = o1->get_value();	
}

NOT::~NOT() {}
bool NOT::is_gate_ready_to_evl() {
	if((i1->get_value()=='X'))
		return false;
	else if(o1->get_value() == 'X')
		return true;
	return false;
}
void NOT::evl () {
	if (i1->get_value()=='0') o1->set_value('1');
	else if (i1->get_value()=='1') o1->set_value('0');
	else o1->set_value('X');
	
	changed_flag = (o1->get_value() != last_value) ? 1 : 0;
	last_value = o1->get_value();	
}

XOR::~XOR() {}
bool XOR::is_gate_ready_to_evl() {
	if((i1->get_value()=='X') || (i2->get_value()=='X'))
		return false;
	else if(o1->get_value() == 'X')
		return true;
	return false;
}
void XOR::evl () {
	if ((i1->get_value()=='X')||(i2->get_value()=='X')||(i1->get_value()=='Z')||(i2->get_value()=='Z')) o1->set_value('X');
	else if (i1->get_value()==i2->get_value()) o1->set_value('0');
	else o1->set_value('1');
	
	changed_flag = (o1->get_value() != last_value) ? 1 : 0;
	last_value = o1->get_value();	
}

NAND::~NAND() {}
bool NAND::is_gate_ready_to_evl() {
        if(number_of_inputs == 2){
		if ((i1->get_value()=='X')||(i2->get_value()=='X'))
			return false;
		else if (o1->get_value() == 'X')
			return true;
	}
        if(number_of_inputs == 3){
		if ((i1->get_value()=='X')||(i2->get_value()=='X')||(i3->get_value()=='X'))
			return false;
		else if (o1->get_value() == 'X')
			return true;
	}
        if(number_of_inputs == 4) {
		if ((i1->get_value()=='X')||(i2->get_value()=='X')||(i3->get_value()=='X')||(i4->get_value()=='X'))
			return false;
		else if (o1->get_value() == 'X')
			return true;
	}
	return false;
}
void NAND::evl () {
        if(number_of_inputs == 2){
		if ((i1->get_value()=='0')||(i2->get_value()=='0')) o1->set_value('1');
		else if ((i1->get_value()=='1')&&(i2->get_value()=='1')) o1->set_value('0');
		else o1->set_value('X');
	}
	else if(number_of_inputs == 3){
		if ((i1->get_value()=='0')||(i2->get_value()=='0')||(i3->get_value()=='0')) o1->set_value('1');
		else if ((i1->get_value()=='1')&&(i2->get_value()=='1')&&(i3->get_value()=='1')) o1->set_value('0');
		else o1->set_value('X');	
	}	
	else{
		if ((i1->get_value()=='0')||(i2->get_value()=='0')||(i3->get_value()=='0')||(i4->get_value()=='0')) o1->set_value('1');
		else if ((i1->get_value()=='1')&&(i2->get_value()=='1')&&(i3->get_value()=='1')&&(i4->get_value()=='1')) o1->set_value('0');
		else o1->set_value('X');	
	}
	
	changed_flag = (o1->get_value() != last_value) ? 1 : 0;
	last_value = o1->get_value();	
}

NOR::~NOR() {}
bool NOR::is_gate_ready_to_evl() {
	if((i1->get_value()=='X') || (i2->get_value()=='X'))
		return false;
	else if(o1->get_value() == 'X')
		return true;
	return false;
}
void NOR::evl () {
	if ((i1->get_value()=='1')||(i2->get_value()=='1')) o1->set_value('0');
	else if ((i1->get_value()=='0')&&(i2->get_value()=='0')) o1->set_value('1');
	else o1->set_value('X');
	
	changed_flag = (o1->get_value() != last_value) ? 1 : 0;
	last_value = o1->get_value();
}
