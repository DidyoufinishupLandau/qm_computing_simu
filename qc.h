#pragma once
#ifndef QC_H
#define QC_H
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <execution>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"
#include "gate.h"
#include "wire.h"

class qc
{
private:
	std::vector<wires> quantum_circuit;
	static std::vector<std::vector<matrix<complex<double>>>> qubit_history;
	static std::vector<std::vector<int>> measurements_history;
	static bool qubit_history_on;
	static int max_history_num;
	static void clean_history();

public:
	qc();
	qc(const int num_qubit, const int state);
	qc(const qc& input_qc);//copy constructor
	qc(qc&& input_qc) noexcept;//move constuctor
	~qc() { quantum_circuit.clear(); }
	qc& operator=(const qc& right_qc);
	qc& operator=(qc&& right_qc) noexcept;
	wires operator[](size_t i) const;

	//modify wire
	void insert_wire(size_t wire_start, size_t wire_end, wires input_wire);//test
	void push_wire(wires input_wire);
	void replace_wire(size_t nth_wire, wires input_wire);
	//modify qubit
	void change_initial_state(size_t wire_start, size_t wire_end, int initial_state);
	//get and modify private data;
	std::vector<std::vector<matrix<complex<double>>>> get_qubit_history() const;
	std::vector<std::vector<int>> get_measurements_history() const;
	void history_switch(bool input);
	void set_max_history_num(int num);

	//insert control gates gates
	gates* stog(std::string input_string);
	matrix<complex<double>> get_qubit_state(int n_th_wire);
	void push_cgate(std::string control_bits_string, std::string nth_wire, std::string gate_name);
	void insert_cgate(std::string control_bits_string, std::string after_nth_gate, std::string nth_wire, std::string gate_name);
	void push_cgate(std::string control_bits_string, std::string nth_wire, gates* gate_name);
	void insert_cgate(std::string control_bits_string, std::string after_nth_gate, std::string nth_wire, gates* input_cgate);
	//insert gates
	void push_gate(int nth_wire, std::string gate_name);
	void insert_gate(int nth_wire, int after_nth_gate, std::string gate_name);
	void push_gate(int nth_wire, gates* input_cgate);
	void insert_gate(int nth_wire, int after_nth_gate, gates* input_cgate);
	void delete_gate(int nth_wire, int after_nth_gate);
	void delete_gate(int column);
	//number of qubit
	int num_wire() const;
	int wire_length(int n_th_wire) const;
	//padding
	void auto_padding();
	//output
	void bar_chart() const;
	//measure
	matrix<int> measure();
	void measure(int num_measurement);
	matrix<complex<double>> matrix_circuit();
	matrix<complex<double>> matrix_qubit();
	friend std::ostream& operator<<(std::ostream& ostream, const qc& input_qc);
};
std::ostream& operator<<(std::ostream& ostream, const qc& input_qc);

#endif // QC_H