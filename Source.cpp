#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <random>
#include <execution>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"
#include "gate.h"
#include "wire.h"
#include "qc.h"
using namespace namespace_one;

bool is_numeric(std::string string) 
{
	//check if input string numerical
	if (string.empty()) return false;//if string is empty "" return false
	for (char c : string) // for all string 
	{
		// check if the single character is digit or not, . - + is considered
		//as int type so need further in c++
		if (!std::isdigit(c) && c != '.' && c != '-' && c != '+')
			return false;
	}
	//if numerical return true
	return true;
}

int main() 
{
	qc new_qc;
	gates* new_gate = new H;
	gates* new_gate_2 = new X;
	wires new_wire;
	wires new_wire_1;
	new_wire_1.push_gate(new_gate);
	new_wire_1.push_gate(new_gate_2);
	new_wire.push_gate(new_gate);
	new_qc.push_wire(new_wire);
	new_qc.push_wire(new_wire_1);
	new_qc.push_wire(new_wire);
	new_qc.push_wire(new_wire_1);
	control_U control_X(new_gate);
	new_qc.push_cgate("1,u", "1,3", control_X);
	new_qc.insert_cgate("1,u", "1,1", "2,4", control_X);
	new_qc.push_cgate("1,u", "3,1", control_X);
	std::cout << new_qc<<std::endl;
	new_qc.replace_wire(2, new_wire_1);
	std::cout << new_qc;
	new_qc[2].print();
	new_qc.insert_gate(3, 1, new_gate_2);
	new_qc[2].print();
	std::cout << new_qc;
	new_qc[3].print();
	matrix<int> outcome = new_qc.measure(10000);
	new_qc.bar_chart(outcome);

}