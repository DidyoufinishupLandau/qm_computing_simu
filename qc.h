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
public:
	qc();
	qc(const wires& input_wire);
	qc(const int num_qubit, const int state);
	qc(const qc& input_qc);
	qc(qc&& input_qc) noexcept;
	~qc() {};
	qc& operator=(const qc& right_qc);
	qc& operator=(qc&& right_qc) noexcept;
	wires operator[](size_t i) const;


	void insert_wire(size_t wire_start, size_t wire_end, wires input_wire);//test
	void push_wire(wires input_wire);
	void replace_wire(size_t nth_wire, wires input_wire);
	void change_initial_state(size_t wire_start, size_t wire_end, int initial_state);
	void push_cgate(std::string control_bits_string,  std::string cbit_pos_wire, control_U& input_cgate);
	void insert_cgate(std::string control_bits_string, std::string cbits_pos_on_wire, std::string cbits_pos_on_qc, control_U& input_cgate);//input sequence must have same size with input_cgate
	void push_gate(int n_th_wire, gates* input_cgate);
	void insert_gate(int n_th_wire, int pos, gates* input_cgate);
	void auto_padding();
	void bar_chart(matrix<int>& measurement);
	matrix<double> ave_measure(int num_measurements);
	
	matrix<int> measure();
	matrix<int> measure(int num_measurement);
	//void print();
	friend std::ostream& operator<<(std::ostream& ostream, const qc& input_qc);
};
std::ostream& operator<<(std::ostream& ostream, const qc& input_qc);
#endif // QC_H
