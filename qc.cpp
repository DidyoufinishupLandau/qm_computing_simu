#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <random>
#include <execution>
#include <memory>
#include <thread>
#include <future>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"
#include "gate.h"
#include "wire.h"
#include "qc.h"

//constructors
qc::qc()
{
	std::cout << "Start to adding wire!" << std::endl;
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
	quantum_circuit = input_qc.quantum_circuit;
}
qc::qc(qc&& input_qc) noexcept
{
	quantum_circuit.clear();
	quantum_circuit = input_qc.quantum_circuit;
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
	quantum_circuit = right_qc.quantum_circuit;
	return *this;
}
qc& qc::operator=(qc&& right_qc) noexcept
{
	std::swap(quantum_circuit, right_qc.quantum_circuit);
	return *this;
}
//initialize static data
std::vector<std::vector<matrix<complex<double>>>> qc::qubit_history{};
std::vector<std::vector<int>> qc::measurements_history{};
bool qc::qubit_history_on{ false };
int qc::max_history_num{5000};//default set to 100.
//functionalities
int generate_random_number(complex<double> p)
{
	std::random_device random;
	std::mt19937 generate(random());
	std::uniform_real_distribution<> distribution(0, 1);//uniform distribution.
	double rand_num = distribution(generate);
	int result = 0;
	double probability = pow(p.modulus(), 2);//Born rule.|<phi|i>|^2 = Probability of being this state
	if (rand_num < probability)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}
gates* qc::stog(std::string input_string)
{
	//recognize the string can convert them to correspond gate;
	if (input_string == "H")
	{
		gates* new_gate = new H();
		return new_gate;
	}
	if (input_string == "I")
	{
		gates* new_gate = new I();
		return new_gate;
	}
	if (input_string == "-")
	{
		gates* new_gate = new padding();
		return new_gate;
	}
	if (input_string == "X")
	{
		gates* new_gate = new X();
		return new_gate;
	}
	if (input_string == "Y")
	{
		gates* new_gate = new Y();
		return new_gate;
	}
	if (input_string == "Z")
	{
		gates* new_gate = new Z();
		return new_gate;
	}
	if (input_string == "S")
	{
		gates* new_gate = new S();
		return new_gate;
	}
	if (input_string == "T")
	{
		gates* new_gate = new T();
		return new_gate;
	}
	else { std::cout << "No such gate found. exit..." << std::endl; exit(0); }
}
void qc::auto_padding()
{
	//padding the empty space in column with identity matrix
	int max_num{ 0 };
	for (size_t i = 0; i < quantum_circuit.size(); i++)
	{
		if (quantum_circuit[i].size() > max_num) { max_num = quantum_circuit[i].get_operation().size(); }
	}
	gates* padding_gate = new padding();
	for (size_t i = 0; i < quantum_circuit.size(); i++)
	{
		quantum_circuit[i].push_gate(max_num - quantum_circuit[i].size(), padding_gate);
	}
}
void qc::bar_chart() const 
{
	std::vector<std::vector<int>> measurement_vector;
	int count = 0;//nqubits
	while (count != quantum_circuit.size())
	{
		std::vector<int> temp_vector;
		for (size_t i{}; i < measurements_history.size(); i++)
		{
			temp_vector.push_back(measurements_history[i][count]);
		}
		measurement_vector.push_back(temp_vector);
		count += 1;
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
		for (int i = 0; i < static_cast<int>(num_measurement * scaling_factor); ++i)
		{
			std::cout << "-";
		}
		for (int i = 0; i < num_space; ++i)
		{
			std::cout << " ";
		}
		std::cout << "| Probability: " << static_cast<double>(num_measurement) / measurement_vector[qubit].size() << std::endl;
	}
}
int qc::num_wire() const
{
	int num_qubit = quantum_circuit.size();
	return num_qubit;
}
int qc::wire_length(int nth_wire) const
{
	//number of gates in this wire.
	int wire_length = quantum_circuit[nth_wire - 1].size();
	return wire_length;
}
matrix<complex<double>> qc::get_qubit_state(int n_th_wire) 
{
	try
	{
		wires _ = quantum_circuit.at(n_th_wire - 1);
		matrix<complex<double>> local_qubit = quantum_circuit[n_th_wire - 1].get_qubit().matrix_qubit();
		return local_qubit;
	}
	catch (const std::out_of_range& error) 
	{
		std::cerr << error.what() << std::endl;
		std::cout << "In get qubit state" << std::endl;
		std::cout << "Invalid wire position" << std::endl;
		exit(0);
	}
}
//modify wires
void qc::insert_wire(size_t wire_start, size_t count, wires input_wire)
{
	//clear qubit history and measurement history of old quantum circuits;
	qubit_history.clear();
	measurements_history.clear();

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
	//clear qubit history and measurement history of old quantum circuits;
	qubit_history.clear();
	measurements_history.clear();

	quantum_circuit.push_back(input_wire);
	auto_padding();
}
void qc::change_initial_state(size_t start_wire, size_t end_wire, int initial_state)
{
	try
	{
		//change qubit states
		std::vector<qubit> temp_qubit;

		//clear qubit history and measurement history of old quantum circuits;
		qubit_history.clear();
		measurements_history.clear();

		for (size_t i{ start_wire - 1 }; i < end_wire; i++)
		{
			wires _ = quantum_circuit.at(i);
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
	gates* padding_gate = new padding;
	std::vector<int> column_to_delete;
	std::vector<int> column_to_padding;
	std::vector<wires> new_quantum_circuit(quantum_circuit.size(), 1);

	//clear qubit history and measurement history of old quantum circuits;
	qubit_history.clear();
	measurements_history.clear();

	//copy the initial state of quantum circuit;
	for (size_t i{}; i < quantum_circuit.size(); i++) { new_quantum_circuit[i].change_qubit(quantum_circuit[i].get_qubit()); }
	try
	{
		wires _ = quantum_circuit.at(nth_wire - 1);
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
			if (input_wire[i]->get_name() != "-")
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
		quantum_circuit = new_quantum_circuit;
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

//matrix<int> qc::measure()
//{
//	//initialize the parameters
//	std::vector<int> max_counter;
//	std::vector<int> counter;
//	std::vector<std::string> gate_name;
//	std::vector<std::string> temp_gate_name;
//	std::vector<int> control_u_pos;
//	matrix<int> measurements_array(1, quantum_circuit.size());
//	std::vector<int> temp;
//	//first all padding the circuit so no vector pointer point out of bound
//	auto_padding();
//	//find out the maximum length of the quantum circuit.
//	for (size_t i{}; i < quantum_circuit.size(); i++)
//	{
//		temp.push_back(quantum_circuit[i].size());
//	}
//	int max_length = *max_element(temp.begin(), temp.end());
//	//create max counter vector when counter reach max counter
//	//iteration stop
//	for (size_t i{}; i < quantum_circuit.size(); i++)
//	{
//		counter.push_back(0);
//		max_counter.push_back(max_length);
//	}
//	//while max counter is not equal to counter
//	//iteration continue
//	while (max_counter != counter)
//	{
//		//parallel computation compute each wire.
//		//depending on the condition of hardware
//		//different thread will be used.
//		//
//		std::for_each(std::execution::par, quantum_circuit.begin(), quantum_circuit.end(), [&](auto& circuit_thread)
//			{
//				size_t i = &circuit_thread - &quantum_circuit[0];
//				//part one
//				//read the circuit column by column
//				//All the control gates are design to allocate in seperate column
//				//1 represent if control bits be one, control operation is execute.
//				if (circuit_thread[counter[i]]->get_name() != "u" && circuit_thread[counter[i]]->get_name() != "U" && circuit_thread[counter[i]]->get_name() != "1" && circuit_thread[counter[i]]->get_name() != "0")
//				{
//					qubit local_qubit = circuit_thread.get_qubit();
//					std::vector<gates*> local_gates = circuit_thread.get_operation();
//					local_qubit = *local_gates[counter[i]] * local_qubit;
//					circuit_thread.change_qubit(local_qubit);
//				}
//				else if (circuit_thread[counter[i]]->get_name() == "1" || circuit_thread[counter[i]]->get_name() == "0")
//				{
//					qubit local_qubit = circuit_thread.get_qubit();
//					int temp_measurement = generate_random_number(local_qubit.get_coefficient_2());
//#pragma omp critical//keep the thread safe.
//					{
//						gate_name.push_back(circuit_thread[counter[i]]->get_name());
//						temp_gate_name.push_back(std::to_string(temp_measurement));
//					}
//				}
//				else if (circuit_thread[counter[i]]->get_name() == "u" || circuit_thread[counter[i]]->get_name() == "U")
//				{
//#pragma omp critical
//					{
//						control_u_pos.push_back(i);
//						control_u_pos.push_back(counter[i]);
//					}
//				}
//
//#pragma omp atomic
//				counter[i] += 1;
//				//at this point a column of whole circuit was readed.
//				//If no control operation, the calculate has complete.
//				//The qubit state is modified according to the gate's properties.
//			});
//		//if control gate, the next section will be execute.
//		if (control_u_pos.size() == 2)
//		{
//			//The gate_name store the control bit string, temp gate name store the measured
//			//state of qubit.
//			//There are only two possibilities, 1 and 0.
//			//If control bit string match the measured bit string. The control operation will execute.
//			//For example. if the given control bit string is 101U. U represent unitary operation.
//			//If the measured state at zero and one gate is 101. Then the unitary operation will be execute
//			//at given position.
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
//			//else do nothing to the qubit.
//			else
//			{
//				gate_name.clear();
//				temp_gate_name.clear();
//				control_u_pos.clear();
//			}
//		}
//	}
//	//now all of the gate has apply to the circuit, we can take the measurements by generating the random
//	//number according to the Born rule.
//	std::vector<matrix<complex<double>>> temp_qubit_history;
//	std::vector<int> temp_measurements_history;
//
//	for (size_t i{}; i < quantum_circuit.size(); i++)
//	{
//		qubit local_qubit = quantum_circuit[i].get_qubit();
//		complex<double> coefficient_2 = local_qubit.get_coefficient_2();
//		//generate random number.
//		measurements_array[i] = generate_random_number(coefficient_2);
//
//		//get matrix representation of the qubits;
//		if (qubit_history_on) { temp_qubit_history.push_back(local_qubit.matrix_qubit()); }
//		//store the measurements in measurement history
//		temp_measurements_history.push_back(measurements_array[i]);
//	}
//	qubit_history.push_back(temp_qubit_history);
//	measurements_history.push_back(temp_measurements_history);
//	//copy the qubit state and store them in a static matrix;
//	return measurements_array;
//}
matrix<int> qc::measure()
{
	//initialize the parameters
	std::vector<int> max_counter;
	std::vector<int> counter;
	std::vector<std::string> gate_name;
	std::vector<std::string> temp_gate_name;
	std::vector<int> control_u_pos;
	matrix<int> measurements_array(1, quantum_circuit.size());
	std::vector<int> temp;
	//first all padding the circuit so no vector pointer point out of bound
	auto_padding();
	//find out the maximum length of the quantum circuit.
	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		temp.push_back(quantum_circuit[i].size());
	}
	int max_length = *max_element(temp.begin(), temp.end());
	//create max counter vector when counter reach max counter
	//iteration stop
	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		counter.push_back(0);
		max_counter.push_back(max_length);
	}
	//while max counter is not equal to counter
	//iteration continue
	while (max_counter != counter)
	{
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			if (quantum_circuit[i][counter[i]]->get_name() != "u" && quantum_circuit[i][counter[i]]->get_name() != "U" && quantum_circuit[i][counter[i]]->get_name() != "1" && quantum_circuit[i][counter[i]]->get_name() != "0")
			{
				qubit local_qubit = quantum_circuit[i].get_qubit();
				std::vector<gates*> local_gates = quantum_circuit[i].get_operation();
				local_qubit = *local_gates[counter[i]] * local_qubit;
				quantum_circuit[i].change_qubit(local_qubit);
			}
			if (quantum_circuit[i][counter[i]]->get_name() == "1" || quantum_circuit[i][counter[i]]->get_name() == "0")
			{
				qubit local_qubit = quantum_circuit[i].get_qubit();
				int temp_measurement = generate_random_number(local_qubit.get_coefficient_2());
				gate_name.push_back(quantum_circuit[i][counter[i]]->get_name());//check does this two set of string match
				temp_gate_name.push_back(std::to_string(temp_measurement));

			}
			if (quantum_circuit[i][counter[i]]->get_name() == "u" || quantum_circuit[i][counter[i]]->get_name() == "U")
			{
				control_u_pos.push_back(i);
				control_u_pos.push_back(counter[i]);
			}
			counter[i] += 1;
		}
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
				gate_name.clear();
				temp_gate_name.clear();
				control_u_pos.clear();
			}
		}
	}
	//now all of the gate has apply to the circuit, we can take the measurements by generating the random
	//number according to the Born rule.
	std::vector<matrix<complex<double>>> temp_qubit_history;
	std::vector<int> temp_measurements_history;

	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		qubit local_qubit = quantum_circuit[i].get_qubit();
		complex<double> coefficient_2 = local_qubit.get_coefficient_2();
		//generate random number.
		measurements_array[i] = generate_random_number(coefficient_2);

		//get matrix representation of the qubits;
		if (qubit_history_on) { temp_qubit_history.push_back(local_qubit.matrix_qubit()); }
		//store the measurements in measurement history
		temp_measurements_history.push_back(measurements_array[i]);
	}
	if (qubit_history_on) { qubit_history.push_back(temp_qubit_history); }
	measurements_history.push_back(temp_measurements_history);
	clean_history();
	//copy the qubit state and store them in a static matrix;
	return measurements_array;
}
void qc::measure(int num_measurement)
{
	//simply iterate with num_measurement times with the measure() function.
	for (size_t n{}; n < num_measurement; n++)
	{
		qc temp_qc = *this;
		matrix<int> single_measure = temp_qc.measure();
	}
}

//modify gates
void qc::insert_cgate(std::string control_bits_string, std::string cbits_pos_on_wire, std::string cbits_pos_on_qc, std::string gate_name)
{
	//Insert cgate is just like the push cgate.
	//However, we need to padding carefully to keep all control operation in same column.
	gates* padding_gates = new padding();
	std::vector<std::string> cbit_pos_operation;//operation string
	std::vector<int> cbits_pos_wire;//cbit position on each wire
	std::vector<int> cbits_pos_qc;//cbit position on quntum circuit
	std::vector<int> padding;//padding identity gate to the circuit;
	std::string s1;
	gates* zero_gates = new zero();
	gates* one_gates = new one();
	gates* c_gate = stog(gate_name);
	c_gate->change_name("U");

	//clear qubit history and measurement history of old quantum circuits;
	qubit_history.clear();
	measurements_history.clear();

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
		//add "-" gate
		//
		if (cbits_pos_wire.size() == cbits_pos_qc.size())
		{
			try
			{
				for (size_t i{}; i < cbits_pos_qc.size(); i++)
				{
					wires _ = quantum_circuit.at(cbits_pos_qc[i] - 1);
					if (cbit_pos_operation[i] == "1")//if 1 add 1 gate, also padding "-" gate to unify the length of circuit;
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
		//padding
		for (size_t i{}; i < padding.size(); i++) { quantum_circuit[padding[i] - 1].insert_gate(max_value_pos_wire, max_paading + 1, padding_gates); }
	}
	else { std::cout << "Position of control gates is not specified properly" << std::endl; exit(0); }
}
void qc::push_cgate(std::string control_bits_string, std::string cbit_pos_qc, std::string gate_name)
{
	//read the input to get the control bits position and unitary operation position.
	//initialize
	gates* padding_gate = new padding();
	gates* zero_gates = new zero();
	gates* one_gates = new one();
	gates* c_gate = stog(gate_name);
	c_gate->change_name("U");

	//clear qubit history and measurement history of old quantum circuits;
	qubit_history.clear();
	measurements_history.clear();


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
				wires _ = quantum_circuit.at(cbits_pos_qc[i] - 1);
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
void qc::insert_cgate(std::string control_bits_string, std::string cbits_pos_on_wire, std::string cbits_pos_on_qc, gates* new_gate)
{
	//Insert cgate is just like the push cgate.
	//However, we need to padding carefully to keep all control operation in same column.
	gates* padding_gates = new padding();
	std::vector<std::string> cbit_pos_operation;//operation string
	std::vector<int> cbits_pos_wire;//cbit position on each wire
	std::vector<int> cbits_pos_qc;//cbit position on quntum circuit
	std::vector<int> padding;//padding identity gate to the circuit;
	std::string s1;
	gates* zero_gates = new zero();
	gates* one_gates = new one();
	gates* c_gate = new_gate;
	c_gate->change_name("U");

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
		//add "-" gate
		//
		if (cbits_pos_wire.size() == cbits_pos_qc.size())
		{
			try
			{
				for (size_t i{}; i < cbits_pos_qc.size(); i++)
				{
					wires _ = quantum_circuit.at(cbits_pos_qc[i] - 1);
					if (cbit_pos_operation[i] == "1")//if 1 add 1 gate, also padding "-" gate to unify the length of circuit;
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
		//padding
		for (size_t i{}; i < padding.size(); i++) { quantum_circuit[padding[i] - 1].insert_gate(max_value_pos_wire, max_paading + 1, padding_gates); }
	}
	else { std::cout << "Position of control gates is not specified properly" << std::endl; exit(0); }
}
void qc::push_cgate(std::string control_bits_string, std::string cbit_pos_qc, gates* new_gate)
{
	//read the input to get the control bits position and unitary operation position.
	//initialize
	gates* padding_gate = new padding();
	gates* zero_gates = new zero();
	gates* one_gates = new one();
	gates* c_gate = new_gate;
	c_gate->change_name("U");

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
				wires _ = quantum_circuit.at(cbits_pos_qc[i] - 1);
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
void qc::push_gate(int n_th_wire, std::string gate_name)
{
	try
	{
		auto_padding();
		wires _ = quantum_circuit.at(n_th_wire - 1);
		gates* new_gate = stog(gate_name);

		//clear qubit history and measurement history of old quantum circuits;
		qubit_history.clear();
		measurements_history.clear();

		bool valve = false;
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			int pos = quantum_circuit[n_th_wire - 1].size();
			if (pos > 0)
			{
				if (quantum_circuit[i][pos - 1]->get_name() == "U" || quantum_circuit[i][pos - 1]->get_name() == "u" || quantum_circuit[i][pos - 1]->get_name() == "1" || quantum_circuit[i][pos - 1]->get_name() == "0")
				{
					valve = true;
					break;
				}
			}
		}
		int pos = quantum_circuit[n_th_wire - 1].size();
		if (valve) { quantum_circuit[n_th_wire - 1].push_gate(new_gate); }
		if (!valve && pos > 0)
		{
			if (quantum_circuit[n_th_wire - 1][pos - 1]->get_name() == "-") { quantum_circuit[n_th_wire - 1].change_gate(pos, new_gate); }
			else if (quantum_circuit[n_th_wire - 1][pos - 1]->get_name() != "-") { quantum_circuit[n_th_wire - 1].push_gate(new_gate); }

		}
		if (!valve && pos == 0) { quantum_circuit[n_th_wire - 1].push_gate(new_gate); }
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
void qc::insert_gate(int n_th_wire, int pos, std::string gate_name)
{
	try
	{
		gates* new_gate = stog(gate_name);
		gates* padding_gate = new padding();

		//clear qubit history and measurement history of old quantum circuits;
		qubit_history.clear();
		measurements_history.clear();

		bool valve = false;
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			//the inserted gate is right at the column where control operation is, we need to add this gate in new line.
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
					quantum_circuit[i].insert_gate(pos, padding_gate);
				}
				if (i == n_th_wire - 1)
				{
					quantum_circuit[i].insert_gate(pos, new_gate);
				}
			}
		}
		if (!valve)
		{
			//if identity matrix and not control operation
			// we replace the identity gate with the given gate, since identity gate do nothing.
			if (quantum_circuit[n_th_wire - 1][pos]->get_name() == "-")
			{
				quantum_circuit[n_th_wire - 1].change_gate(pos + 1, new_gate);
				return;
			}
			//if not identity gate, we need to add this gate in new line.
			if (quantum_circuit[n_th_wire - 1][pos]->get_name() != "-")
			{
				for (size_t i{}; i < quantum_circuit.size(); i++)
				{
					if (i != n_th_wire - 1)
					{
						quantum_circuit[i].insert_gate(pos, padding_gate);
					}
					if (i == n_th_wire - 1)
					{
						quantum_circuit[i].insert_gate(pos, new_gate);
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
void qc::push_gate(int n_th_wire, gates* new_gate)
{
	try
	{
		auto_padding();
		wires _ = quantum_circuit.at(n_th_wire - 1);

		//clear qubit history and measurement history of old quantum circuits;
		qubit_history.clear();
		measurements_history.clear();

		bool valve = false;
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			int pos = quantum_circuit[n_th_wire - 1].size();
			if (pos > 0)
			{
				if (quantum_circuit[i][pos - 1]->get_name() == "U" || quantum_circuit[i][pos - 1]->get_name() == "u" || quantum_circuit[i][pos - 1]->get_name() == "1" || quantum_circuit[i][pos - 1]->get_name() == "0")
				{
					valve = true;
					break;
				}
			}
		}
		int pos = quantum_circuit[n_th_wire - 1].size();
		if (valve) { quantum_circuit[n_th_wire - 1].push_gate(new_gate); }
		if (!valve && pos > 0)
		{
			if (quantum_circuit[n_th_wire - 1][pos - 1]->get_name() == "-") { quantum_circuit[n_th_wire - 1].change_gate(pos, new_gate); }
			else if (quantum_circuit[n_th_wire - 1][pos - 1]->get_name() != "-") { quantum_circuit[n_th_wire - 1].push_gate(new_gate); }

		}
		if (!valve && pos == 0) { quantum_circuit[n_th_wire - 1].push_gate(new_gate); }
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
void qc::insert_gate(int n_th_wire, int pos, gates* new_gate)
{
	try
	{
		gates* padding_gate = new padding();

		//clear qubit history and measurement history of old quantum circuits;
		qubit_history.clear();
		measurements_history.clear();

		bool valve = false;
		for (size_t i{}; i < quantum_circuit.size(); i++)
		{
			//the inserted gate is right at the column where control operation is, we need to add this gate in new line.
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
					quantum_circuit[i].insert_gate(pos, padding_gate);
				}
				if (i == n_th_wire - 1)
				{
					quantum_circuit[i].insert_gate(pos, new_gate);
				}
			}
		}
		if (!valve)
		{
			// if identity matrix and not control operation
			// we replace the identity gate with the given gate, since identity gate do nothing to the state of qubit.
			if (quantum_circuit[n_th_wire - 1][pos]->get_name() == "-")
			{
				quantum_circuit[n_th_wire - 1].change_gate(pos + 1, new_gate);
				return;
			}
			//if not identity gate, we need to add this gate in new line.
			if (quantum_circuit[n_th_wire - 1][pos]->get_name() != "-")
			{
				for (size_t i{}; i < quantum_circuit.size(); i++)
				{
					if (i != n_th_wire - 1)
					{
						quantum_circuit[i].insert_gate(pos, padding_gate);
					}
					if (i == n_th_wire - 1)
					{
						quantum_circuit[i].insert_gate(pos, new_gate);
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
void qc::delete_gate(int wire_pos, int gate_pos) //buggy
{
	try
	{
		wires _ = quantum_circuit.at(wire_pos - 1);
		gates* padding_gates = new padding();

		//clear qubit history and measurement history of old quantum circuits;
		qubit_history.clear();
		measurements_history.clear();

		if (quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() != "U" && quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() != "u" && quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() != "1" && quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() != "0")
		{
			quantum_circuit[wire_pos - 1].change_gate(gate_pos, padding_gates);
		}
		if (quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() == "U" || quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() == "u" || quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() == "1" || quantum_circuit[wire_pos - 1][gate_pos - 1]->get_name() == "0")
		{
			for (size_t i{}; i < quantum_circuit.size(); i++)
			{
				if (quantum_circuit[i][gate_pos - 1]->get_name() == "U" || quantum_circuit[i][gate_pos - 1]->get_name() == "u" || quantum_circuit[i][gate_pos - 1]->get_name() == "1" || quantum_circuit[i][gate_pos - 1]->get_name() != "0")
				{
					quantum_circuit[i].change_gate(gate_pos, padding_gates);
				}
			}
		}
	}
	catch(const std::out_of_range & error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "At delete_gate function" << std::endl;
		std::cout << "first arg out of bound" << std::endl;
		exit(0);
	}
}
void qc::delete_gate(int column)
{
	//clear qubit history and measurement history of old quantum circuits;
	qubit_history.clear();
	measurements_history.clear();

	for (size_t i{}; i < quantum_circuit.size(); i++)
	{
		quantum_circuit[i].delete_gate(column);
	}
}
//get private data
std::vector<std::vector<matrix<complex<double>>>> qc::get_qubit_history() const
{
	return qubit_history;
}
std::vector<std::vector<int>> qc::get_measurements_history() const
{
	return measurements_history;
}
void qc::history_switch(bool input)
{
	qubit_history_on = input;
	if (input == true) { std::cout << "start to track qubit state" << std::endl; }
	if (input == false) { std::cout << "stop to track qubit state" << std::endl; }
}
//overloading
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
			if (temp_operation[i][j]->get_name() == "-")
			{
				ostream << "-";
			}
			if (temp_operation[i][j]->get_name() != "u" && temp_operation[i][j]->get_name() != "U" && temp_operation[i][j]->get_name() != "1" && temp_operation[i][j]->get_name() != "0" && temp_operation[i][j]->get_name() != "-")
			{
				ostream << temp_operation[i][j]->get_name();
			}
		}
		ostream << std::endl;
	}
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
//modify static function and data
void qc::clean_history() 
{
	if (qubit_history.size() > max_history_num) { qubit_history.clear(); std::cout << "Qubit history cleared" << std::endl; }
	if (measurements_history.size() > max_history_num) { measurements_history.clear(); std::cout << "Measurement history cleared" << std::endl;}
}
void qc::set_max_history_num(int input_int) 
{
	//set the number of history stored to be
	max_history_num = input_int;
}
matrix<complex<double>> qc::matrix_circuit()
{
	matrix<complex<double>> projection_zero;
	matrix<complex<double>> projection_one;
	matrix<complex<double>> identity;
	matrix<complex<double>> final_matrix;

	"1,0;0,0" >> projection_zero;
	"0,0;0,1" >> projection_one;
	"1,0;0,1" >> identity;
	int quantum_circuit_length = quantum_circuit[0].size();//get the length of the quantum circuit
	int count = 0;
	while (count != quantum_circuit_length)
	{
		bool valve{ false };
		std::vector<std::string> gate_name_string;
		matrix<complex<double>> circuit_matrix;
		for (size_t i{ 0 }; i < quantum_circuit.size(); i++)
		{
			gate_name_string.push_back(quantum_circuit[i][count]->get_name());
			if(quantum_circuit[i][count]->get_name()!="u"&& quantum_circuit[i][count]->get_name()!="U"&& quantum_circuit[i][count]->get_name() != "1"&& quantum_circuit[i][count]->get_name() != "0")
			{ 
				circuit_matrix = circuit_matrix.tensor(quantum_circuit[i][count]->matrix_gate()); 
			}
			if (quantum_circuit[i][count]->get_name() == "1")
			{
				circuit_matrix = circuit_matrix.tensor(identity);
			}
			if (quantum_circuit[i][count]->get_name() == "0")
			{
				circuit_matrix = circuit_matrix.tensor(identity);
			}
			if (quantum_circuit[i][count]->get_name() == "U" || quantum_circuit[i][count]->get_name() == "u")
			{
				circuit_matrix = circuit_matrix.tensor(identity);
				valve = true;
			}
		}
		matrix<complex<double>> temp_matrix;
		for (size_t i{ 0 }; i < gate_name_string.size(); i++)
		{
			if (gate_name_string[i] == "1") { temp_matrix = temp_matrix.tensor(projection_one); }
			if (gate_name_string[i] == "0") { temp_matrix = temp_matrix.tensor(projection_zero); }
			if (gate_name_string[i] == "u"|| gate_name_string[i] == "U") 
			{ 
				temp_matrix = temp_matrix.tensor(quantum_circuit[i][count]->matrix_gate() - identity);
			}
			if (gate_name_string[i] != "1" && gate_name_string[i] != "0" && gate_name_string[i] != "u" && gate_name_string[i] != "U")
			{
				temp_matrix = temp_matrix.tensor(quantum_circuit[i][count]->matrix_gate());
			}
		}

		if (valve) { circuit_matrix = circuit_matrix + temp_matrix; }
		if (final_matrix.get_size() == 0) { final_matrix = circuit_matrix; }
		else if (final_matrix.get_size() != 0) { final_matrix = circuit_matrix * final_matrix;  }
		count += 1;
	}
	return final_matrix;
}
matrix<complex<double>> qc::matrix_qubit() 
{
	matrix<complex<double>> qubit_state;
	for (size_t i{}; i < quantum_circuit.size(); i++) 
	{
		qubit_state = qubit_state.tensor(quantum_circuit[i].matrix_qubit());
	}
	return qubit_state;
}
