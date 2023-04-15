#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <random>
#include <execution>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"
#include "gate.h"
#include "wire.h"
#include "qc.h"

qc::qc()
{
	std::cout << "Start to adding wire!" << std::endl;
}
qc::qc(const wires& input_wire)
{
	std::vector<qubit> temp_qubit;

	quantum_circuit.push_back(input_wire);
	temp_qubit.push_back(input_wire.get_qubit());
}
qc::qc(const int num_qubit, const int state)
{
	qubit new_qubit;
	if (state == 0)
	{
		new_qubit.change_coefficient(1, 0);
		wires new_wires(state);
		std::vector<qubit> temp_qubit;
		for (size_t i{ 0 }; i < num_qubit; i++)
		{
			quantum_circuit.push_back(new_wires);
			temp_qubit.push_back(new_qubit);
		}
	}
	if (state == 1)
	{
		new_qubit.change_coefficient(1, 0);
		wires new_wires(state);
		std::vector<qubit> temp_qubit;
		for (size_t i{ 0 }; i < num_qubit; i++)
		{
			quantum_circuit.push_back(new_wires);
			temp_qubit.push_back(new_qubit);
		}
	}
}
qc::qc(const qc& input_qc)
{
	quantum_circuit.clear();
	quantum_circuit.assign(input_qc.quantum_circuit.begin(), input_qc.quantum_circuit.end());
}
qc::qc(qc&& input_qc) noexcept
{
	quantum_circuit.clear();
	quantum_circuit.assign(input_qc.quantum_circuit.begin(), input_qc.quantum_circuit.end());
	//clear input circuit;
	input_qc.quantum_circuit.clear();

	//assign the default value to input circuit;
	wires new_wire;
	std::vector<qubit> temp_qubit;
	qubit new_qubit;

	input_qc.quantum_circuit.push_back(new_wire);
	temp_qubit.push_back(new_qubit);
}
qc& qc::operator=(const qc& right_qc)
{
	quantum_circuit.clear();
	quantum_circuit.assign(right_qc.quantum_circuit.begin(), right_qc.quantum_circuit.end());
	return *this;
}
qc& qc::operator=(qc&& right_qc) noexcept
{
	std::swap(quantum_circuit, right_qc.quantum_circuit);
	return *this;
}

void qc::auto_padding() 
{
	int max_num{ 0 };
	for (size_t i = 0; i < quantum_circuit.size(); i++)
	{
		if (quantum_circuit[i].size() > max_num) { max_num = quantum_circuit[i].get_operation().size(); }
	}
	gates* padding_gate = new I;
	for (size_t i = 0; i < quantum_circuit.size(); i++)
	{
		quantum_circuit[i].push_gate(max_num - quantum_circuit[i].size(), padding_gate);
	}
	//std::vector<std::string> gates_name;
	//std::vector<std::string> identity_gates_name;
	//for (size_t i = 0; i < quantum_circuit.size(); i++)
	//{
	//	identity_gates_name.push_back(quantum_circuit[i][quantum_circuit[i].size() - 1]->get_name());
	//	identity_gates_name.push_back(padding_gate->get_name());
	//}
	//bool valve = true;
	//for(size_t i = 0; i < gates_name.size(); i++)
	//{
	//	if (gates_name[i] != identity_gates_name[i]) { valve = false;  break; }
	//}
	//if (valve) 
	//{
	//	for (size_t i = 0; i < quantum_circuit.size(); i++)
	//	{
	//		quantum_circuit[i].delete_gate(quantum_circuit[i].size());
	//	}
	//}
}
void qc::insert_wire(size_t wire_start, size_t count, wires input_wire)
{
	if (wire_start < 0 || wire_start>0) 
	{
		std::cout << "error occur at insert_wire function" << std::endl;
		std::cout << "position out of circuit range" << std::endl; 
		exit(0); 
	}
	quantum_circuit.insert(quantum_circuit.begin() + wire_start, count, input_wire);
	auto_padding();
}
void qc::push_wire(wires input_wire)
{
	quantum_circuit.push_back(input_wire);
	auto_padding();
}
void qc::change_initial_state(size_t start_wire, size_t end_wire, int initial_state)
{
	try
	{
		std::vector<qubit> temp_qubit;
		for (size_t i{ start_wire - 1 }; i < end_wire; i++)
		{
			quantum_circuit.at(i);
			quantum_circuit[i].change_qubit(initial_state);
		}
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "qubit position invalid" << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
}
void qc::replace_wire(size_t nth_wire, wires input_wire)
{
	gates* padding_gate = new I;
	std::vector<int> column_to_delete;
	std::vector<int> column_to_padding;
	std::vector<wires> new_quantum_circuit(quantum_circuit.size(),1);
	//copy the initial state of quantum circuit;
	for (size_t i{}; i < quantum_circuit.size(); i++) { new_quantum_circuit[i].change_qubit(quantum_circuit[i].get_qubit()); }
	try
	{
		quantum_circuit.at(nth_wire - 1);
		auto_padding();
		for (size_t i{}; i < quantum_circuit[nth_wire - 1].size(); i++)
		{
			if (quantum_circuit[nth_wire - 1][i]->get_name() == "u" || quantum_circuit[nth_wire - 1][i]->get_name() == "U" || quantum_circuit[nth_wire - 1][i]->get_name() == "1" || quantum_circuit[nth_wire - 1][i]->get_name() == "0")
			{
				column_to_delete.push_back(i);
			}
		}
		//now we need to check if the there are any control-u operation on the replaced wire;
		//if so, we need to clear either the contorl bits or the u operation.
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			for (size_t j{}; j < quantum_circuit[i].size(); j++)
			{
				if (!(std::find(column_to_delete.begin(), column_to_delete.end(), j) != column_to_delete.end()))
				{
					new_quantum_circuit[i].push_gate(quantum_circuit[i][j]);
				}
			}
		}
		//find if any gate overlap with the control gates

		for (size_t i{}; i < input_wire.size(); i++)
		{
			if (input_wire[i]->get_name() != "I")
			{
				for (size_t j{}; j < quantum_circuit.size(); j++)
				{
					if (i = quantum_circuit[j].size() - 1) { break; }
					if ((quantum_circuit[j][i]->get_name() == "u" || quantum_circuit[j][i]->get_name() == "U" || quantum_circuit[j][i]->get_name() == "1" || quantum_circuit[j][i]->get_name() == "0"))
					{
						column_to_padding.push_back(i);
						break;
					}
				}
			}
		}
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			for (size_t j{}; j < quantum_circuit[i].size(); j++)
			{
				if (std::find(column_to_padding.begin(), column_to_padding.end(), j) != column_to_padding.end())
				{
					new_quantum_circuit[i].insert_gate(j, padding_gate);
				}
			}
		}
		new_quantum_circuit[nth_wire - 1] = input_wire;
		quantum_circuit.clear();
		quantum_circuit.assign(new_quantum_circuit.begin(), new_quantum_circuit.end());
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "wire position invalid " << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
	//padding
	auto_padding();

}
void qc::insert_cgate(std::string control_bits_string, std::string cbits_pos_on_wire, std::string cbits_pos_on_qc, control_U& input_cgate)
{
	std::vector<std::string> cbit_pos_operation;//operation string
	std::vector<int> cbits_pos_wire;//cbit position on each wire
	std::vector<int> cbits_pos_qc;//cbit position on quntum circuit
	std::vector<int> padding;//padding identity gate to the circuit;
	std::string s1;
	gates* padding_gates = new I();
	gates* zero_gates = new zero();
	gates* one_gates = new one();
	gates* c_gate = &input_cgate;
	input_cgate.set_position(control_bits_string);

	//get the control bits and control gate position
	//store them in vector
	std::stringstream ss1(cbits_pos_on_wire);
	while (std::getline(ss1, s1, ','))
	{
		cbits_pos_wire.push_back(std::stoi(s1));
	}
	std::stringstream ss2(cbits_pos_on_qc);
	while (std::getline(ss2, s1, ','))
	{
		cbits_pos_qc.push_back(std::stoi(s1));
	}
	std::stringstream ss3(control_bits_string);
	while (std::getline(ss3, s1, ','))
	{
		cbit_pos_operation.push_back(s1);
	}
	//find the num of padding and 
	//maintain all other control gates components in the same column
	std::vector<int> temp;
	for (int i = 0; i < quantum_circuit.size(); i++) {
		temp.push_back(i + 1);
	}
	std::set_difference(temp.begin(), temp.end(), cbits_pos_qc.begin(), cbits_pos_qc.end(), std::back_inserter(padding));
	temp.clear();//clear temp vector;

	int max_value_pos_wire = *max_element(cbits_pos_wire.begin(), cbits_pos_wire.end());
	for (size_t i{}; i < cbits_pos_qc.size(); i++) { temp.push_back(max_value_pos_wire - cbits_pos_wire[i]); }
	int max_paading = *max_element(temp.begin(), temp.end());

	if (cbit_pos_operation.size() == cbits_pos_wire.size() && cbits_pos_wire.size() == cbits_pos_qc.size())
	{
		//firstly, modify the gates seires.
		//find out the maxmum number in input sequence. 
		//start from the cbit position on each wire.
		//add "I" gate
		//
		if (cbits_pos_wire.size() == cbits_pos_qc.size())
		{
			try
			{
				for (size_t i{}; i < cbits_pos_qc.size(); i++)
				{
					quantum_circuit.at(cbits_pos_qc[i] - 1);
					if (cbit_pos_operation[i] == "1")//if 1 add 1 gate, also padding "I" gate to unify the length of circuit;
					{
						quantum_circuit[cbits_pos_qc[i] - 1].insert_gate(cbits_pos_wire[i], max_value_pos_wire - cbits_pos_wire[i], padding_gates);

						quantum_circuit[cbits_pos_qc[i] - 1].insert_gate(max_value_pos_wire, one_gates);
					}
					if (cbit_pos_operation[i] == "0")//if 0 add 1 gate
					{
						quantum_circuit[cbits_pos_qc[i] - 1].insert_gate(cbits_pos_wire[i], max_value_pos_wire - cbits_pos_wire[i], padding_gates);

						quantum_circuit[cbits_pos_qc[i] - 1].insert_gate(max_value_pos_wire, zero_gates);
					}
					if (cbit_pos_operation[i] == "u" || cbit_pos_operation[i] == "U")//if U add correspond 2*2 dimension gate
					{

						quantum_circuit[cbits_pos_qc[i] - 1].insert_gate(cbits_pos_wire[i], max_value_pos_wire - cbits_pos_wire[i], padding_gates);

						quantum_circuit[cbits_pos_qc[i] - 1].insert_gate(max_value_pos_wire, c_gate);
					}
				}
			}
			catch (const std::out_of_range& error)
			{
				std::cerr << "Exception: " << error.what() << std::endl;
				std::cout << "Control gates position invalid " << std::endl;
				std::cout << "Exit program..." << std::endl;
				exit(0);
			}
		}
		for (size_t i{}; i < padding.size(); i++) { quantum_circuit[padding[i] - 1].insert_gate(max_value_pos_wire, max_paading + 1, padding_gates); }
	}
	else { std::cout << "Position of control gates is not specified properly" << std::endl; exit(0); }
}
void qc::push_cgate(std::string control_bits_string, std::string cbit_pos_qc, control_U& input_cgate)
{
	//initialize
	gates* padding_gates = new I();
	gates* zero_gates = new zero();
	gates* one_gates = new one();
	gates* c_gate = &input_cgate;
	input_cgate.set_position(control_bits_string);

	std::vector<std::string> cbit_pos_operation;
	std::vector<int> cbits_pos_qc;//cbit position on which wire.
	std::vector<int> wire_length;

	//find wire length for padding
	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		wire_length.push_back(quantum_circuit[i].get_operation().size());
	}
	int max_value_pos_wire = *max_element(wire_length.begin(), wire_length.end());
	//read input
	std::string s1;
	std::stringstream ss(cbit_pos_qc);
	while (std::getline(ss, s1, ','))
	{
		cbits_pos_qc.push_back(std::stoi(s1));
	}
	std::stringstream ss2(control_bits_string);
	while (std::getline(ss2, s1, ','))
	{
		cbit_pos_operation.push_back(s1);
	}
	//padding
	if (cbit_pos_operation.size() == cbits_pos_qc.size())
	{
		auto_padding();
		try
		{
			for (size_t i{}; i < cbit_pos_operation.size(); i++)
			{
				//read the position on qc. 
				//remember to pos-1 to get the true index.
				quantum_circuit.at(cbits_pos_qc[i] - 1);
				if (cbit_pos_operation[i] == "1")
				{
					quantum_circuit[cbits_pos_qc[i] - 1].push_gate(one_gates);
				}
				if (cbit_pos_operation[i] == "0")
				{
					quantum_circuit[cbits_pos_qc[i] - 1].push_gate(zero_gates);
				}
				if (cbit_pos_operation[i] == "u" || cbit_pos_operation[i] == "U")
				{
					quantum_circuit[cbits_pos_qc[i] - 1].push_gate(c_gate);
				}
			}
		}
		catch (const std::out_of_range& error)
		{
			std::cerr << "Exception: " << error.what() << std::endl;
			std::cout << "Control gates position invalid " << std::endl;
			std::cout << "Exit program..." << std::endl;
			exit(0);
		}
		auto_padding();
	}
	else { std::cout << "Position of control bits is not specified properly" << std::endl; exit(0); }
}
void qc::push_gate(int n_th_wire, gates* input_cgate)
{
	try
	{
		quantum_circuit.at(n_th_wire - 1);
		quantum_circuit[n_th_wire - 1].push_gate(input_cgate);
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "gate position invalid " << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
	auto_padding();
}
//void qc::insert_gate(int n_th_wire, int pos, gates* input_gate)
//{
//	try
//	{
//		quantum_circuit.at(n_th_wire - 1);
//		quantum_circuit[n_th_wire - 1].insert_gate(pos, input_gate);
//		gates* padding_gate = new I;
//		auto_padding();
//		std::vector<int> pos_padding;
//		for (size_t i{}; i < quantum_circuit[n_th_wire - 1].size(); i++)
//		{
//			for (size_t j{}; j < quantum_circuit.size(); j++)
//			{
//				if (quantum_circuit[j][i]->get_name() == "u" || quantum_circuit[j][i]->get_name() == "U" || quantum_circuit[j][i]->get_name() == "1" || quantum_circuit[j][i]->get_name() == "0")
//				{
//					pos_padding.push_back(i);
//				}
//			}
//		}
//		for (size_t i{}; i < quantum_circuit.size(); i++)
//		{
//			for (size_t j{}; j < quantum_circuit[i].size(); j++)
//			{
//				if ((std::find(pos_padding.begin(), pos_padding.end(), j) != pos_padding.end()) && i != n_th_wire - 1)
//				{
//					quantum_circuit[i].insert_gate(j, padding_gate);
//				}
//			}
//		}
//		auto_padding();
//	}
//	catch (const std::out_of_range& error)
//	{
//		std::cerr << "Exception: " << error.what() << std::endl;
//		std::cout << "wire position invalid " << std::endl;
//		std::cout << "Exit program..." << std::endl;
//		exit(0);
//	}
//}
void qc::insert_gate(int n_th_wire, int pos, gates* input_gate)
{
	try
	{
		gates* padding = new I();
		bool valve = false;
		for (size_t i{}; i < quantum_circuit.size(); i++) 
		{
			if (quantum_circuit[i][pos]->get_name() == "U" || quantum_circuit[i][pos]->get_name() == "u" || quantum_circuit[i][pos]->get_name() == "1" || quantum_circuit[i][pos]->get_name() == "0") 
			{
				valve = true;
				break;
			}
		}
		if (valve) 
		{
			for (size_t i{}; i < quantum_circuit.size(); i++)
			{
				if (i != n_th_wire - 1)
				{
					quantum_circuit[i].insert_gate(pos, padding);
				}
				if (i == n_th_wire - 1)
				{
					quantum_circuit[i].insert_gate(pos, input_gate);
				}
			}
		}
		if (!valve)
		{
			if (quantum_circuit[n_th_wire - 1][pos]->get_name() == "I") 
			{
				quantum_circuit[n_th_wire - 1].change_gate(pos+1, input_gate);
				return;
			}
			if (quantum_circuit[n_th_wire - 1][pos]->get_name() != "I")
			{
				for (size_t i{}; i < quantum_circuit.size(); i++)
				{
					if (i != n_th_wire - 1)
					{
						quantum_circuit[i].insert_gate(pos, padding);
					}
					if (i == n_th_wire - 1)
					{
						quantum_circuit[i].insert_gate(pos, input_gate);
					}
				}
			}
			auto_padding();
		}
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "wire position invalid " << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
}
int generate_random_number(complex<double> p) {
	std::random_device random;
	std::mt19937 generate(random());
	std::uniform_real_distribution<> distribution(0, 1);
	double randNum = distribution(generate);
	int result = 0;
	double probability = pow(p.modulus(), 2);//probability be one;
	if (randNum < probability) {
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}

//matrix<int> qc::measure() 
//{
//	std::vector<int> max_counter;
//	std::vector<int> counter;
//	std::vector<std::string> gate_name;
//	std::vector<std::string> temp_gate_name;
//	std::vector<int> control_u_pos;
//	matrix<int> measurements_array(1, quantum_circuit.size());
//	std::vector<int> temp;
//
//	auto_padding();
//	for (size_t i{}; i < quantum_circuit.size(); i++)
//	{
//		temp.push_back(quantum_circuit[i].size());
//	}
//	int max_length = *max_element(temp.begin(), temp.end());
//
//	for (size_t i{}; i < quantum_circuit.size(); i++)
//	{
//		counter.push_back(0);
//		max_counter.push_back(max_length);
//	}
//
//	while (max_counter != counter)
//	{
//		for (size_t i{}; i < quantum_circuit.size(); i++)
//		{
//			if (quantum_circuit[i][counter[i]]->get_name() != "u" && quantum_circuit[i][counter[i]]->get_name() != "U" && quantum_circuit[i][counter[i]]->get_name() != "1" && quantum_circuit[i][counter[i]]->get_name() != "0")
//			{
//				qubit local_qubit = quantum_circuit[i].get_qubit();
//				std::vector<gates*> local_gates = quantum_circuit[i].get_operation();
//				local_qubit = *local_gates[counter[i]] * local_qubit;
//				quantum_circuit[i].change_qubit(local_qubit);
//			}
//			if (quantum_circuit[i][counter[i]]->get_name() == "1" || quantum_circuit[i][counter[i]]->get_name() == "0")
//			{
//				qubit local_qubit = quantum_circuit[i].get_qubit();
//				int temp_measurement = generate_random_number(local_qubit.get_coeffcient_2());
//				gate_name.push_back(quantum_circuit[i][counter[i]]->get_name());//check does this two set of string match
//				temp_gate_name.push_back(std::to_string(temp_measurement));
//
//			}
//			if (quantum_circuit[i][counter[i]]->get_name() == "u" || quantum_circuit[i][counter[i]]->get_name() == "U")
//			{
//				control_u_pos.push_back(i);
//				control_u_pos.push_back(counter[i]);
//			}
//			counter[i] += 1;
//		}
//		if (control_u_pos.size() == 2)
//		{
//			if (gate_name == temp_gate_name)
//			{
//				qubit local_qubit = quantum_circuit[control_u_pos[0]].get_qubit();
//				std::vector<gates*> local_gates = quantum_circuit[control_u_pos[0]].get_operation();
//				local_qubit = *local_gates[control_u_pos[1]] * local_qubit;
//				quantum_circuit[control_u_pos[0]].change_qubit(local_qubit);
//
//				gate_name.clear();
//				temp_gate_name.clear();
//				control_u_pos.clear();
//			}
//			else
//			{
//				qubit local_qubit = quantum_circuit[control_u_pos[0]].get_qubit();
//				std::vector<gates*> local_gates = quantum_circuit[control_u_pos[0]].get_operation();
//				gate_name.clear();
//				temp_gate_name.clear();
//				control_u_pos.clear();
//			}
//		}
//	}
//	//now all of the gate has apply to the circuit, we can take the measurements by generating the random
//	//number according to the probabiliy given.
//
//	for (size_t i{}; i < quantum_circuit.size(); i++)
//	{
//		qubit local_qubit = quantum_circuit[i].get_qubit();
//		measurements_array[i] = generate_random_number(local_qubit.get_coeffcient_2());
//	}
//	return measurements_array;
//}
matrix<int> qc::measure()
{
	std::vector<int> max_counter;
	std::vector<int> counter;
	std::vector<std::string> gate_name;
	std::vector<std::string> temp_gate_name;
	std::vector<int> control_u_pos;
	matrix<int> measurements_array(1, quantum_circuit.size());
	std::vector<int> temp;

	auto_padding();
	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		temp.push_back(quantum_circuit[i].size());
	}
	int max_length = *max_element(temp.begin(), temp.end());

	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		counter.push_back(0);
		max_counter.push_back(max_length);
	}

	while (max_counter != counter)
	{
		//parallel computation
		std::for_each(quantum_circuit.begin(), quantum_circuit.end(), [&](auto& circuit_thread)
			{
				size_t i = &circuit_thread - &quantum_circuit[0];

				if (circuit_thread[counter[i]]->get_name() != "u" && circuit_thread[counter[i]]->get_name() != "U" && circuit_thread[counter[i]]->get_name() != "1" && circuit_thread[counter[i]]->get_name() != "0")
				{
					qubit local_qubit = circuit_thread.get_qubit();
					std::vector<gates*> local_gates = circuit_thread.get_operation();
					local_qubit = *local_gates[counter[i]] * local_qubit;
					circuit_thread.change_qubit(local_qubit);
				}
				else if (circuit_thread[counter[i]]->get_name() == "1" || circuit_thread[counter[i]]->get_name() == "0")
				{
					qubit local_qubit = circuit_thread.get_qubit();
					int temp_measurement = generate_random_number(local_qubit.get_coefficient_2());
#pragma omp critical
					{
						gate_name.push_back(circuit_thread[counter[i]]->get_name());
						temp_gate_name.push_back(std::to_string(temp_measurement));
					}
				}
				else if (circuit_thread[counter[i]]->get_name() == "u" || circuit_thread[counter[i]]->get_name() == "U")
				{
#pragma omp critical
					{
						control_u_pos.push_back(i);
						control_u_pos.push_back(counter[i]);
					}
				}

#pragma omp atomic
				counter[i] += 1;
			});

		if (control_u_pos.size() == 2)
		{
			if (gate_name == temp_gate_name)
			{
				qubit local_qubit = quantum_circuit[control_u_pos[0]].get_qubit();
				std::vector<gates*> local_gates = quantum_circuit[control_u_pos[0]].get_operation();
				local_qubit = *local_gates[control_u_pos[1]] * local_qubit;
				quantum_circuit[control_u_pos[0]].change_qubit(local_qubit);

				gate_name.clear();
				temp_gate_name.clear();
				control_u_pos.clear();
			}
			else
			{
				qubit local_qubit = quantum_circuit[control_u_pos[0]].get_qubit();
				std::vector<gates*> local_gates = quantum_circuit[control_u_pos[0]].get_operation();
				gate_name.clear();
				temp_gate_name.clear();
				control_u_pos.clear();
			}
		}
	}
	//now all of the gate has apply to the circuit, we can take the measurements by generating the random
	//number according to the probabiliy given.

	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		qubit local_qubit = quantum_circuit[i].get_qubit();
		measurements_array[i] = generate_random_number(local_qubit.get_coefficient_2());
	}
	return measurements_array;
}
matrix<int> qc::measure(int num_measurement)
{
	matrix<int> measurements_array(num_measurement, quantum_circuit.size());
	for (size_t n{}; n < num_measurement; n++)
	{
		qc temp_qc = *this;
		matrix<int> single_measure = temp_qc.measure();
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			measurements_array[i + quantum_circuit.size() * n] = single_measure[i];
		}
	}
	return measurements_array;
}

std::ostream& operator<<(std::ostream& ostream, const qc& input_qc)
{
	std::vector<wires> temp_operation = input_qc.quantum_circuit;
	for (size_t i{}; i < temp_operation.size(); i++)
	{
		ostream << temp_operation[i].get_qubit();

		for (size_t j{}; j < temp_operation[i].size(); j++)
		{
			ostream << "-";
			if (temp_operation[i][j]->get_name() == "1")
			{
				ostream << "1";
			}
			if (temp_operation[i][j]->get_name() == "0")
			{
				ostream << "0";
			}
			if (temp_operation[i][j]->get_name() == "u" || temp_operation[i][j]->get_name() == "U")
			{
				ostream << "U";
			}
			if (temp_operation[i][j]->get_name() == "I")
			{
				ostream << "-";
			}
			if(temp_operation[i][j]->get_name() != "u" && temp_operation[i][j]->get_name() != "U" && temp_operation[i][j]->get_name() != "1" && temp_operation[i][j]->get_name() != "0" && temp_operation[i][j]->get_name() != "I")
			{
				ostream << temp_operation[i][j]->get_name();
			}
		}
		ostream << std::endl;
	}
	//input_qc.gates_series.assign(gates_series_holder.begin(), gates_series_holder.end());
	return ostream;
}

wires qc::operator[](size_t i) const
{
	if (i < 0 || i >= quantum_circuit.size())
	{
		std::cout << "error,size out of bound for quantum circuit" << std::endl;
		exit(0);
	}

	return quantum_circuit[i];
}
matrix<double> qc::ave_measure(int num_measurements)
{
	matrix<int> measurements = measure(num_measurements);
	matrix<double> average_measurements(1, measurements.get_columns());
	for (size_t i{}; i < measurements.get_rows(); i++)
	{
		for (size_t j{}; j < measurements.get_columns(); j++)
		{
			average_measurements[j] = average_measurements[j] + measurements[j + measurements.get_columns() * i];
		}
	}
	for (size_t i{}; i < average_measurements.get_columns(); i++)
	{
		average_measurements[i] = average_measurements[i] / measurements.get_rows();
	}
	return average_measurements;
}

void qc::bar_chart(matrix<int>& measurement_matrix)
{
	std::vector<std::vector<int>> measurement_vector;
	for (size_t i{}; i < measurement_matrix.get_columns(); i++)
	{
		std::vector<int> temp_vector;
		for (size_t j{}; j < measurement_matrix.get_rows(); j++)
		{
			temp_vector.push_back(measurement_matrix[i + j * measurement_matrix.get_columns()]);
		}
		measurement_vector.push_back(temp_vector);
	}
	int max_measurements = 0;
	for (const auto& qubit_measurement : measurement_vector)
	{
		int num_measurement = static_cast<int>(std::count(qubit_measurement.begin(), qubit_measurement.end(), 1));
		max_measurements = std::max(max_measurements, num_measurement);
	}

	// Define the maximum length of the bar chart
	int max_length = 20; // Update this value to adjust the maximum length of the bar chart

	// Calculate the scaling factor for adjusting the bar length
	double scaling_factor = 1.0;
	if (max_measurements > max_length) {
		scaling_factor = static_cast<double>(max_length) / max_measurements;
	}

	// Generate the bar chart
	for (int qubit = 0; qubit < measurement_vector.size(); ++qubit)
	{
		int num_measurement = static_cast<int>(std::count(measurement_vector[qubit].begin(), measurement_vector[qubit].end(), 1));
		int num_space = max_length - static_cast<int>(num_measurement * scaling_factor);
		std::cout << "qubit" << (qubit + 1) << ": ";
		for (int i = 0; i < static_cast<int>(num_measurement * scaling_factor); ++i) {
			std::cout << "-";
		}
		for (int i = 0; i < num_space; ++i) {
			std::cout << " ";
		}
		std::cout << "| Probability: " << static_cast<double>(num_measurement) / measurement_vector[qubit].size() << std::endl;
	}
}