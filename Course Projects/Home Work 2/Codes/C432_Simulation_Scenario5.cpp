#include "Standard_libraries.h"
#include "Primitives_Classes.h"

vector<string> wires_names;
vector<string> input_wires_names;
vector<string> output_wires_names;
vector<Wire> Wires;

vector<Gate*> gates;

const int max_delay_of_gates = 6;

class time_wheel {
	int current_time = 0;
	vector<Gate*> time_array[max_delay_of_gates];
	public:
		time_wheel() {} // constructor
		void advance_time_one_step() {
			for(int i = 0; i < time_array[current_time].size(); i++)
				time_array[current_time][i]->evl();
			time_array[current_time].clear();
			for(int i = 0; i < gates.size(); i++)
				if(gates[i]->is_gate_ready_to_evl())
					if(!is_gate_in_activity_list(gates[i]))
						time_array[(current_time + gates[i]->get_gate_delay()) % max_delay_of_gates].push_back(gates[i]);
			current_time = (current_time + 1) % 6;
		};
		bool is_gate_in_activity_list(Gate* gate) {
			for(int i = 0; i < 6; i++)
				for(int j = 0; j < time_array[i].size(); j++)
					if(time_array[i][j] == gate)
						return true;
			return false;
		}
		bool is_activity_list_empty() {
			for(int i = 0; i < 6; i++)
				if(time_array[i].size() > 0)
					return false;
			return true;
		};
}; 

string remove_first_spaces(string input_string)
{
	if(input_string[0] != ' ')
		return input_string;

	int index = 0;

	while(input_string.at(index) == ' ')
		index++;
	return input_string.substr(index, input_string.size() - 1);
}

int find(vector<string> string_vector, string the_string_to_find)
{
	for(int index = 0; index < string_vector.size(); index++)
		if(string_vector[index] == remove_first_spaces(the_string_to_find))
			return index;
}

vector<string> extract_gate_wires(string current_line_of_verilog_code)
{
	string gate_io = current_line_of_verilog_code.substr(current_line_of_verilog_code.find('(') + 1, current_line_of_verilog_code.find(')') - current_line_of_verilog_code.find('(') - 1);
    char gate_inputs_output[gate_io.size() + 1];
    strcpy(gate_inputs_output, gate_io.c_str());

    vector<string> gate_wires_names;

    char *wire = strtok(gate_inputs_output, ",");

    while(wire != NULL)
    {
        string gate_wire = wire;
 		gate_wires_names.push_back(gate_wire);	
		    
	    wire = strtok(NULL, ",");         	
    }
    return gate_wires_names;
}

void convert_verilog_to_cpp(string verilog_input_file)
{
	ifstream verilog_code(verilog_input_file);

	string current_line_of_verilog_code;

	while(getline(verilog_code, current_line_of_verilog_code))
	{
		if(current_line_of_verilog_code.substr(0, 5) == "input")
		{ 
		    string wires = current_line_of_verilog_code.substr(6, current_line_of_verilog_code.size() - 8);
	        char input_wires[wires.size() + 1];
	        strcpy(input_wires, wires.c_str());

	        char *wire = strtok(input_wires, ",");

	        while(wire != NULL)
	        {
	            string new_wire = wire;
    			wires_names.push_back(new_wire);
    			input_wires_names.push_back(new_wire);

    			Wire new_input_wire = Wire();
    			Wires.push_back(new_input_wire);

			    wire = strtok(NULL, ",");         	
            }
	            
	        while(current_line_of_verilog_code[current_line_of_verilog_code.size() - 2] != ';')
	        {
	        	getline(verilog_code, current_line_of_verilog_code);
	        	
	        	string wires = current_line_of_verilog_code.substr(6, current_line_of_verilog_code.size() - 8);
	            char input_wires[wires.size() + 1];
	            strcpy(input_wires, wires.c_str());

	            char *wire = strtok(input_wires, ",");

	            while(wire != NULL)
	            {
	                string new_wire = wire;
					wires_names.push_back(new_wire); 
					input_wires_names.push_back(new_wire);

	    			Wire new_input_wire = Wire();
    			    Wires.push_back(new_input_wire);

				    wire = strtok(NULL, ",");         	
	            }	  	              
	        }
		}
		if(current_line_of_verilog_code.substr(0, 6) == "output")
		{
			string wires = current_line_of_verilog_code.substr(7, current_line_of_verilog_code.size() - 9);
	        char output_wires[wires.size() + 1];
	        strcpy(output_wires, wires.c_str());

	        char *wire = strtok(output_wires, ",");

	        while(wire != NULL)
	        {
	            string new_wire = wire;
    			wires_names.push_back(new_wire);
    			output_wires_names.push_back(new_wire);

    			Wire output_wire = Wire();
    			Wires.push_back(output_wire);		
			    
			    wire = strtok(NULL, ",");         	
            }	   	
		}
		if(current_line_of_verilog_code.substr(0, 4) == "wire")
		{
		    string wires = current_line_of_verilog_code.substr(5, current_line_of_verilog_code.size() - 7);
	        char new_wires[wires.size() + 1];
	        strcpy(new_wires, wires.c_str());

	        char *wire = strtok(new_wires, ",");

	        while(wire != NULL)
	        {
	            string new_wire = wire;
    			wires_names.push_back(new_wire);
    			
    			Wire New_Wire = Wire();
    			Wires.push_back(New_Wire);			
			    
			    wire = strtok(NULL, ",");         	
            }
	            
	        while(current_line_of_verilog_code[current_line_of_verilog_code.size() - 2] != ';')
	        {
	        	getline(verilog_code, current_line_of_verilog_code);
	        	
	        	string wires = current_line_of_verilog_code.substr(5, current_line_of_verilog_code.size() - 7);
	            char new_wires[wires.size() + 1];
	            strcpy(new_wires, wires.c_str());

	            char *wire = strtok(new_wires, ",");

	            while(wire != NULL)
	            {
	                string new_wire = wire;
					wires_names.push_back(new_wire); 
					
					Wire New_Wire = Wire();
    			    Wires.push_back(New_Wire);	
				    
				    wire = strtok(NULL, ",");         	
	            }	  	              
	        }
		}
		if(current_line_of_verilog_code.substr(0, 3) == "not")
		{
            vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            NOT* new_not_gate = new NOT();
            new_not_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])]);
            gates.push_back(new_not_gate);	   	
		}	
		if(current_line_of_verilog_code.substr(0, 4) == "nand")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            if(gate_wires_names.size() == 3)
            {
            	NAND* new_nand_gate = new NAND(2);
                new_nand_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])]);
                gates.push_back(new_nand_gate);
            }
            else if(gate_wires_names.size() == 4)
            {
            	NAND* new_nand_gate = new NAND(3);
                new_nand_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])]);            	
                gates.push_back(new_nand_gate);
            }
            else
            {
            	NAND* new_nand_gate = new NAND(4);
                new_nand_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])], &Wires[find(wires_names, gate_wires_names[4])]);            	
                gates.push_back(new_nand_gate);
            }              	
		}
		if(current_line_of_verilog_code.substr(0, 3) == "nor")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            NOR* new_nor_gate = new NOR();
            new_nor_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])]);
            gates.push_back(new_nor_gate);             	
		}
		if(current_line_of_verilog_code.substr(0, 3) == "xor")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            XOR* new_xor_gate = new XOR();
            new_xor_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])]);
            gates.push_back(new_xor_gate);             	
		}
		if(current_line_of_verilog_code.substr(0, 3) == "and")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            if(gate_wires_names.size() == 8)
            {
            	AND* new_and_gate = new AND(8);
                new_and_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])], &Wires[find(wires_names, gate_wires_names[4])], &Wires[find(wires_names, gate_wires_names[5])], &Wires[find(wires_names, gate_wires_names[6])], &Wires[find(wires_names, gate_wires_names[7])], &Wires[find(wires_names, gate_wires_names[8])]);
                gates.push_back(new_and_gate);
            }
            else
            {
            	AND* new_and_gate = new AND(9);
                new_and_gate->ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])], &Wires[find(wires_names, gate_wires_names[4])], &Wires[find(wires_names, gate_wires_names[5])], &Wires[find(wires_names, gate_wires_names[6])], &Wires[find(wires_names, gate_wires_names[7])], &Wires[find(wires_names, gate_wires_names[8])], &Wires[find(wires_names, gate_wires_names[9])]);
                gates.push_back(new_and_gate);
            }              	
		}									
	}
}

void initialize_inputs(string given_input_values)
{
	for(int i = 0; i < input_wires_names.size(); i++)
		Wires[find(wires_names, input_wires_names[i])].set_value(given_input_values.at(i));
}

int main ()
{ 

	// Getting timed inputs from timed_inputs_scenario5.txt file

    ifstream timed_inputs_file("timed_inputs_scenario5.txt");
	string current_line_of_timed_inputs_file;
	vector<string> timed_inputs;
	while(getline(timed_inputs_file, current_line_of_timed_inputs_file))
		timed_inputs.push_back(current_line_of_timed_inputs_file);
    
	convert_verilog_to_cpp("c432.v");

    time_wheel Time_Wheel = time_wheel();

    int current_time = 0;

	do
	{
		for(int i = 0; i < timed_inputs.size(); i++)
			if(stoi(timed_inputs[i].substr(1, timed_inputs[i].find(" "))) == current_time)
				initialize_inputs(timed_inputs[i].substr(timed_inputs[i].find(" ") + 1, timed_inputs[i].size()));
		Time_Wheel.advance_time_one_step();	
		current_time++;
	}while(!Time_Wheel.is_activity_list_empty());
	

    // printing the values of output wires

	for(int i = 0; i < output_wires_names.size(); i++)
		cout << output_wires_names[i] << " = " << Wires[find(wires_names, output_wires_names[i])].get_value() << "\n";

    return 1;                
}