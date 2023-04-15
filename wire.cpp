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
#include "wire.h"

wires::wires() :qubit{}//default constructor, set the qubit to be |0> with probability 100%
{}
wires::wires(int initial_qubit_state) : qubit{}
{
	if(initial_qubit_state==1)
	{
		coefficient_2 = 1;
		coefficient_1 = 0;
	}
	if (initial_qubit_state == 0)
	{
		coefficient_2 = 0;
		coefficient_1 = 1;
	}
}
wires::wires(const wires& input_wire) :qubit(input_wire.basis_1, input_wire.basis_2, input_wire.coefficient_1, input_wire.coefficient_2)
{
	operation.clear();
	for (size_t i{ 0 }; i < input_wire.operation.size(); i++)
	{
		operation.push_back(input_wire.operation[i]);
	}
}

wires::wires(wires&& input_wire) noexcept : qubit(input_wire.get_qubit())
{

	operation = input_wire.operation;
	input_wire.operation.clear();
	input_wire.coefficient_1 = 1;
	input_wire.coefficient_2 = 0;
	"1;0" >> input_wire.basis_1;
	"0;1" >> input_wire.basis_2;
}

std::vector<gates*> wires::get_operation()const
{
	return operation;
}
wires& wires::operator=(const wires& right_wires)
{
	if (&right_wires == this) return *this;
	operation.clear();
	for (size_t i{ 0 }; i < right_wires.operation.size(); i++)
	{
		operation.push_back(right_wires.operation[i]);
	}
	basis_1 = right_wires.basis_1;
	basis_2 = right_wires.basis_2;
	coefficient_1 = right_wires.coefficient_1;
	coefficient_2 = right_wires.coefficient_2;
	return *this;
}

wires& wires::operator=(wires&& right_wire) noexcept
{
	std::swap(operation, right_wire.operation);
	std::swap(coefficient_1, right_wire.coefficient_1);
	std::swap(coefficient_2, right_wire.coefficient_2);
	std::swap(basis_1, right_wire.basis_1);
	std::swap(basis_2, right_wire.basis_2);
	return *this;
}

wires wires::get_wire() const
{
	return *this;
}

void wires::change_qubit(int input_int)
{
	if (input_int == 1)
	{
		coefficient_2 = 1;
		coefficient_1 = 0;
	}
	if (input_int == 0)
	{
		coefficient_2 = 0;
		coefficient_1 = 1;
	}
	else { std::cout << "invalid qubit state" << std::endl; exit(0); }
}
void wires::change_qubit(const qubit& input_qubit) 
{
	coefficient_1 = input_qubit.get_coefficient_1();
	coefficient_2 = input_qubit.get_coefficient_2();
}
void wires::insert_gate(int n_th_gate, gates* input_gate)
{
	//after n gates
	try
	{
		operation.at(n_th_gate);
		operation.insert(operation.begin() + n_th_gate, input_gate);
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "insert_gate position invalid " << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
}
void wires::push_gate(gates* input_gate)
{
	//after n gates
	operation.push_back(input_gate);
}
void wires::print()
{
	matrix<complex<double>> summed_basis;
	summed_basis = basis_1 * coefficient_1 + basis_2 * coefficient_2;
	if (coefficient_1.modulus() == 0) { std::cout << coefficient_2 << "|1>"; }
	if (coefficient_2.modulus() == 0) { std::cout << coefficient_1 << "|0>"; }
	else
	{ 
		std::cout << coefficient_1 << "|0>" << coefficient_2 << "|1>"; 
	}

	for (size_t i{ 0 }; i < operation.size(); i++)
	{
		std::cout << operation[i]->get_name();
	}
	std::cout << std::endl;
}

void wires::insert_gate(int n_th_gate, int num_gate, gates* input_gate) 
{
	try
	{
		operation.at(n_th_gate);
		if (n_th_gate > 0 || n_th_gate == 0)
		{
			operation.insert(operation.begin() + n_th_gate, num_gate, input_gate);
		}
		else { std::cout << "The insert position can't be negative." << std::endl; exit(0); }
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "insert_gate position invalid " << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
}
void wires::push_gate(int num_gate, gates* input_gate)
{
	if (num_gate != 0)
	{
		for (size_t i{}; i < num_gate; i++)
		{
			//catch?
			operation.push_back(input_gate);
		}
	}

}
int wires::size() const 
{
	return operation.size();
}
gates* wires::operator[](size_t i) const 
{
	if (i < 0 || i >= operation.size())
	{
		std::cout << "error,size out of bound for wire" << std::endl;
		exit(0);
	}

	return operation[i];
}
void wires::delete_gate(int input_int) 
{
	try
	{
		operation.at(input_int - 1);
		std::vector<gates*> temp_operation;
		for (size_t i{}; i < operation.size(); i++)
		{
			if (input_int - 1 != i)
			{
				temp_operation.push_back(operation[i]);
			}
		}
		operation.clear();
		operation.assign(temp_operation.begin(), temp_operation.end());
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		std::cout << "delete_gate position invalid " << std::endl;
		std::cout << "Exit program..." << std::endl;
		exit(0);
	}
}
void wires::change_gate(int n_th_gate, gates* input_gate) 
{
	operation[n_th_gate - 1] = input_gate;
}