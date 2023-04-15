#pragma once
#ifndef WIRE_H
#define WIRE_H
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"
#include "gate.h"


class wires :public qubit
{
protected:
	std::vector<gates*> operation;//gate links
public:
	wires();
	wires(int initial_qubit_state);
	wires(const wires& input_wire);
	wires(wires&& input_wire) noexcept;
	~wires() {};//destructor
	gates* operator[](size_t i) const;
	wires& operator=(const wires& right_qubit);
	wires& operator=(wires&& right_qubit) noexcept;

	//get self
	wires get_wire() const;
	std::vector<gates*> get_operation() const;

	void insert_gate(int n_th_gate,gates* input_gate);
	void push_gate(gates* input_gate);
	void insert_gate(int n_th_gate, int num_gate, gates* input_gate);
	void push_gate(int num_gate, gates* input_gate);
	void change_qubit(int input_int);//virtual
	void change_qubit(const qubit& input_qubit);
	void change_gate(int n_th_gate, gates* input_gate);
	void print();
	void delete_gate(int n_th_gate);
	int size() const;

};

#endif //WIRE_H