class Wire {
	char value;
	public:
		Wire (char initial_value = 'X') {value = initial_value;} // constructor
		void set_value(char input_value) {value = input_value;}
		char get_value() {return value;}
};

class AND {
	int number_of_inputs;
	Wire *i1, *i2, *i3, *i4, *i5, *i6, *i7, *i8, *i9, *o1;
	public:
		AND (int given_number_of_inputs){number_of_inputs = given_number_of_inputs;}; // constructor
		~AND(); // destructor
		void ios(Wire* w, Wire* a, Wire* b, Wire* c, Wire* d, Wire* e, Wire* f, Wire* g, Wire* h) { o1 = w; i1 = a; i2 = b;  i3 = c; i4 = d;  i5 = e; i6 = f;  i7 = g; i8 = h; }
		void ios(Wire* w, Wire* a, Wire* b, Wire* c, Wire* d, Wire* e, Wire* f, Wire* g, Wire* h, Wire* i) { o1 = w; i1 = a; i2 = b;  i3 = c; i4 = d;  i5 = e; i6 = f;  i7 = g; i8 = h; i9 = i; }
		void evl();
};

class OR {
	char *i1, *i2, *o1;
	public:
		OR (); // constructor
		~OR(); // destructor
		void ios(char& a, char& b, char &w) { i1 = &a; i2 = &b; o1 = &w; }
		void evl();
};

class NOT {
	Wire *i1, *o1;
	public:
		NOT ();
		~NOT(); // destructor
		void ios(Wire* w, Wire* a) { o1 = w; i1 = a; }
		
		void evl ();
};

class XOR {
	Wire *i1, *i2, *o1;
	public:
		XOR ();
		~XOR(); // destructor
		void ios(Wire* w, Wire* a, Wire* b) { o1 = w; i1 = a; i2 = b; }
		void evl();
};

class NAND {
	int number_of_inputs;
	Wire *i1, *i2, *i3, *i4, *o1;
	public:
		NAND (int given_number_of_inputs){number_of_inputs = given_number_of_inputs;}; // constructor
		~NAND(); // destructor
		void ios(Wire* w, Wire* a, Wire* b) { o1 = w; i1 = a; i2 = b; }
	        void ios(Wire* w, Wire* a, Wire* b, Wire* c) { o1 = w; i1 = a; i2 = b; i3 = c;}
	        void ios(Wire* w, Wire* a, Wire* b, Wire* c, Wire* d) { o1 = w; i1 = a; i2 = b; i3 = c; i4 = d;}
		void evl();
};

class NOR {
	Wire *i1, *i2, *o1;
	public:
		NOR (); // constructor
		~NOR(); // destructor
		void ios(Wire* w, Wire* a, Wire* b) { o1 = w; i1 = a; i2 = b; }
		void evl();
};

AND::~AND() {}
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
}

OR::OR() {}
void OR::evl () {
	if ((*i1=='1')||(*i2=='1')) *o1='1';
	else if ((*i1=='0')&&(*i2=='0')) *o1='0';
	else *o1='X';
}

NOT::NOT() {}
NOT::~NOT() {}
void NOT::evl () {
	if (i1->get_value()=='0') o1->set_value('1');
	else if (i1->get_value()=='1') o1->set_value('0');
	else o1->set_value('X');
}

XOR::XOR() {}
XOR::~XOR() {}
void XOR::evl () {
	if ((i1->get_value()=='X')||(i2->get_value()=='X')||(i1->get_value()=='Z')||(i2->get_value()=='Z')) o1->set_value('X');
	else if (i1->get_value()==i2->get_value()) o1->set_value('0');
	else o1->set_value('1');
}

NAND::~NAND() {}
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
}

NOR::NOR() {}
NOR::~NOR() {}
void NOR::evl () {
	if ((i1->get_value()=='1')||(i2->get_value()=='1')) o1->set_value('0');
	else if ((i1->get_value()=='0')&&(i2->get_value()=='0')) o1->set_value('1');
	else o1->set_value('X');

}
