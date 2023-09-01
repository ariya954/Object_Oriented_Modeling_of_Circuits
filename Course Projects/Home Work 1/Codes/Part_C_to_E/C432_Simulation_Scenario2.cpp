#include "Standard_libraries.h"
#include "Primitives_Classes.h"

vector<string> wires_names;
vector<string> output_wires_names;
vector<Wire> Wires;

vector<NOT> not_gates;
vector<AND> and_gates;
vector<XOR> xor_gates;    
vector<NOR> nor_gates;    
vector<NAND> nand_gates;

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

void convert_verilog_to_cpp(char *input_wires_values, string verilog_input_file)
{
	ifstream verilog_code(verilog_input_file);

	string current_line_of_verilog_code;

	while(getline(verilog_code, current_line_of_verilog_code))
	{
		if(current_line_of_verilog_code.substr(0, 5) == "input")
		{ 
            int n = 0;

		    string wires = current_line_of_verilog_code.substr(6, current_line_of_verilog_code.size() - 8);
	        char input_wires[wires.size() + 1];
	        strcpy(input_wires, wires.c_str());

	        char *wire = strtok(input_wires, ",");

	        while(wire != NULL)
	        {
	            string new_wire = wire;
    			wires_names.push_back(new_wire);

    			Wire input_wire = Wire(input_wires_values[n]);
    			Wires.push_back(input_wire);
    			n++;

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

	    			Wire input_wire = Wire(input_wires_values[n]);
    			    Wires.push_back(input_wire);
    			    n++;

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

            NOT new_not_gate = NOT();
            new_not_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])]);
            not_gates.push_back(new_not_gate);	   	
		}	
		if(current_line_of_verilog_code.substr(0, 4) == "nand")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            if(gate_wires_names.size() == 3)
            {
            	NAND new_nand_gate = NAND(2);
                new_nand_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])]);
                nand_gates.push_back(new_nand_gate);
            }
            else if(gate_wires_names.size() == 4)
            {
            	NAND new_nand_gate = NAND(3);
                new_nand_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])]);            	
                nand_gates.push_back(new_nand_gate);
            }
            else
            {
            	NAND new_nand_gate = NAND(4);
                new_nand_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])], &Wires[find(wires_names, gate_wires_names[4])]);            	
                nand_gates.push_back(new_nand_gate);
            }              	
		}
		if(current_line_of_verilog_code.substr(0, 3) == "nor")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            NOR new_nor_gate = NOR();
            new_nor_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])]);
            nor_gates.push_back(new_nor_gate);             	
		}
		if(current_line_of_verilog_code.substr(0, 3) == "xor")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            XOR new_xor_gate = XOR();
            new_xor_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])]);
            xor_gates.push_back(new_xor_gate);             	
		}
		if(current_line_of_verilog_code.substr(0, 3) == "and")
		{
			vector<string> gate_wires_names = extract_gate_wires(current_line_of_verilog_code);

            if(gate_wires_names.size() == 8)
            {
            	AND new_and_gate = AND(8);
                new_and_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])], &Wires[find(wires_names, gate_wires_names[4])], &Wires[find(wires_names, gate_wires_names[5])], &Wires[find(wires_names, gate_wires_names[6])], &Wires[find(wires_names, gate_wires_names[7])], &Wires[find(wires_names, gate_wires_names[8])]);
                and_gates.push_back(new_and_gate);
            }
            else
            {
            	AND new_and_gate = AND(9);
                new_and_gate.ios(&Wires[find(wires_names, gate_wires_names[0])], &Wires[find(wires_names, gate_wires_names[1])], &Wires[find(wires_names, gate_wires_names[2])], &Wires[find(wires_names, gate_wires_names[3])], &Wires[find(wires_names, gate_wires_names[4])], &Wires[find(wires_names, gate_wires_names[5])], &Wires[find(wires_names, gate_wires_names[6])], &Wires[find(wires_names, gate_wires_names[7])], &Wires[find(wires_names, gate_wires_names[8])], &Wires[find(wires_names, gate_wires_names[9])]);
                and_gates.push_back(new_and_gate);
            }              	
		}									
	}
}

int main ()
{    
	// initializing verilog module inputs(all inputs are set to 1)

    char input_values_of_verilog_module[36];
    for(int i = 0; i < 36; i++)
    	input_values_of_verilog_module[i] = '1';
    
	convert_verilog_to_cpp(input_values_of_verilog_module, "c432.v");

    // gates evaluation in random order(scenario 2)	

	int changed_flag;
	do
	{
		changed_flag = 0;

		for(int i = 0; i < and_gates.size(); i++)
		{
			and_gates[i].evl();
			changed_flag = (changed_flag) ? 1 : and_gates[i].get_changed_flag();			
		}		
		for(int i = 0; i < not_gates.size(); i++)
		{
			not_gates[i].evl();
			changed_flag = (changed_flag) ? 1 : not_gates[i].get_changed_flag();
		}
		for(int i = 0; i < xor_gates.size(); i++)
		{
			xor_gates[i].evl();
			changed_flag = (changed_flag) ? 1 : xor_gates[i].get_changed_flag();			
		}
		for(int i = 0; i < nor_gates.size(); i++)
		{
			nor_gates[i].evl();
			changed_flag = (changed_flag) ? 1 : nor_gates[i].get_changed_flag();			
		}
		for(int i = 0; i < nand_gates.size(); i++)
		{
			nand_gates[i].evl();
			changed_flag = (changed_flag) ? 1 : nand_gates[i].get_changed_flag();			
		}
	}while(changed_flag != 0);	
	

    // printing the values of output wires

	for(int i = 0; i < output_wires_names.size(); i++)
		cout << output_wires_names[i] << " = " << Wires[find(wires_names, output_wires_names[i])].get_value() << "\n";		

    return 1;                
}