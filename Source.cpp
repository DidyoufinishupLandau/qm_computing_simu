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
	//The matrix constructor prevent the bad memory allocation. 
	// For example, the following line would result the exit of program.
	//matrix<double> new_double_matrix(100000000000, 1000000000000);
	double pi = 3.14159265358979323846;
	//test gate functionality
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	complex<double> rotation(std::cos(0), std::sin(3.1415926 / 2));
	//initialize gates.
	gates* x_pointer = new X();
	gates* y_pointer = new Y();
	gates* z_pointer = new Z();
	gates* I_pointer = new I();
	gates* H_pointer = new H();
	gates* s_pointer = new S();
	gates* t_pointer = new T();
	gates* o_pointer = new O(one, zero, zero, rotation);
	//show matrix representation.
	std::cout<<x_pointer->matrix_gate()<<std::endl;
	std::cout << y_pointer->matrix_gate() << std::endl;
	std::cout << z_pointer->matrix_gate() << std::endl;
	std::cout << I_pointer->matrix_gate() << std::endl;
	std::cout << H_pointer->matrix_gate() << std::endl;
	std::cout << s_pointer->matrix_gate() << std::endl;
	std::cout << t_pointer->matrix_gate() << std::endl;
	std::cout << o_pointer->matrix_gate() << std::endl;
	//test qubit with initial state |1>
	qubit test_qubit(1);
	std::cout << test_qubit<<std::endl;
	//matrix representation
	std::cout << test_qubit.matrix_qubit() << std::endl;
	test_qubit.change_state(0);
	std::cout << test_qubit << std::endl;
	std::cout << test_qubit.matrix_qubit() << std::endl;
	//test gate act on qubit
	std::cout << *x_pointer * test_qubit << std::endl;
	std::cout << *y_pointer * test_qubit << std::endl;
	std::cout << *z_pointer * test_qubit << std::endl;
	std::cout << *I_pointer * test_qubit << std::endl;
	std::cout << *H_pointer * test_qubit << std::endl;
	std::cout << *s_pointer * test_qubit << std::endl;
	std::cout << *t_pointer * test_qubit << std::endl;
	//test wire;
	wires new_wire(1);
	new_wire.push_gate(x_pointer);
	new_wire.push_gate(y_pointer);
	new_wire.push_gate(z_pointer);
	new_wire.push_gate(s_pointer);
	new_wire.push_gate(t_pointer);
	new_wire.push_gate(I_pointer);
	new_wire.push_gate(H_pointer);
	new_wire.print();
	new_wire.delete_gate(4);
	new_wire.print();
	//test quantum circuit
	wires new_wire2(0);//initialize wire with zero.
	qc new_qc(5, 1);
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "H"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "Y"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "Z"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "T"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "S"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "I"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "X"); }
	std::cout << new_qc << std::endl;//print out
	//insert control not gate
	new_qc.insert_cgate("1,U", "1,1","1,2", "X");
	new_qc.insert_cgate("1,U", "2,2", "1,3", "X");
	new_qc.insert_cgate("1,U", "3,3", "1,4", "X");
	new_qc.insert_cgate("1,U", "4,4", "1,5", "X");
	std::cout << new_qc << std::endl;
	//The time cost of measure function depend on the performance of computer. 
	//because the implementation of parallel computation
	//But the difference would be small for measurement number under 10000.
	matrix<int> results = new_qc.measure(100);//measure this quantum circuit 1000 times.
	new_qc.bar_chart(results);//print out probability bar chart.
	//now try to replace the third wire.
	new_wire.print();
	new_qc.replace_wire(3, new_wire);
	std::cout << new_qc << std::endl;
	//try to insert the gate in third wire and the second wire.
	new_qc.insert_gate(2, 2, "H");
	new_qc.insert_gate(3, 2, "Z");
	std::cout << new_qc << std::endl;
	

	//example of constructing a fourier transform quantum circuit with 5 qubits
	std::cout << "fourier transform" << std::endl;
	qc ft(4,1);
	ft.change_initial_state(2, 3, 0);

	ft.push_gate(1,"H");
	for (size_t i{ 1 }; i < ft.num_wire(); i++) 
	{
		gates* rotational_gates_pointer = new P(2 * pi / (pow(2, i+1)));//R_n rotational gate
		std::string cbits_pos = "1,";
		cbits_pos += std::to_string(i + 1);
		ft.push_cgate("U,1", cbits_pos, rotational_gates_pointer);
	}
	ft.push_gate(2, "H");
	for (size_t i{ 2 }; i < ft.num_wire(); i++)
	{
		gates* rotational_gates_pointer = new P(2 * pi / (pow(2, i + 1)));//R_n rotational gate
		std::string cbits_pos = "2,";
		cbits_pos += std::to_string(i + 1);
		ft.push_cgate("U,1", cbits_pos, rotational_gates_pointer);
	}
	ft.push_gate(3, "H");
	for (size_t i{ 3 }; i < ft.num_wire(); i++)
	{
		gates* rotational_gates_pointer = new P(2 * pi / (pow(2, i + 1)));//R_n rotational gate
		std::string cbits_pos = "3,";
		cbits_pos += std::to_string(i + 1);
		ft.push_cgate("U,1", cbits_pos, rotational_gates_pointer);
	}
	ft.push_gate(4, "H");
	for (size_t i{ 4 }; i < ft.num_wire(); i++)
	{
		gates* rotational_gates_pointer = new P(2 * pi / (pow(2, i + 1)));//R_n rotational gate
		std::string cbits_pos = "4,";
		cbits_pos += std::to_string(i + 1);
		ft.push_cgate("U,1", cbits_pos, rotational_gates_pointer);
	}
	//swap process
	ft.push_cgate("1,U", "1,4", "X");
	ft.push_cgate("1,U", "4,1", "X");
	ft.push_cgate("1,U", "1,4", "X");
	ft.push_cgate("1,U", "2,3", "X");
	ft.push_cgate("1,U", "3,2", "X");
	ft.push_cgate("1,U", "2,3", "X");
	std::cout << ft << std::endl;
	matrix<int> ft_result = ft.measure(100);
	ft.bar_chart(ft_result);
	
}

//qc new_qc;
//wires new_wire;
//complex<double> index_1(1, 0);
//complex<double> index_2(0, 0);
//complex<double> index_3(0, 0);
//complex<double> index_4(std::cos(2*3.14159265358979/(pow(2,3))), std::sin(2 * 3.14159265358979 / pow(2,3)));
//complex<double> index_5(std::cos(2 * 3.14159265358979 / (pow(2,2))), std::sin(2 * 3.14159265358979 / (pow(2,2))));
//complex<double> index_6(std::cos(2 * 3.14159265358979 / (pow(2, 4))), std::sin(2 * 3.14159265358979 / pow(2, 4)));
//matrix<complex<double>> new_matrix(2, 2);
//new_matrix[0] = index_1;
//new_matrix[1] = index_2;
//new_matrix[2] = index_3;
//new_matrix[3] = index_4;

//matrix<complex<double>> new_matrix_2(2, 2);
//new_matrix_2[0] = index_1;
//new_matrix_2[1] = index_2;
//new_matrix_2[2] = index_3;
//new_matrix_2[3] = index_5;


//matrix<complex<double>> new_matrix_3(2, 2);
//new_matrix_2[0] = index_1;
//new_matrix_2[1] = index_2;
//new_matrix_2[2] = index_3;
//new_matrix_2[3] = index_6;

//gates* new_gate = new H;
//gates* R_3 = new O(new_matrix);
//gates* R_2 = new O(new_matrix_2);
//gates* R_4 = new O(new_matrix_3);

//control_U C_3(R_3);
//control_U C_2(R_2);
//control_U C_4(R_4);

//new_qc.push_wire(new_wire);
//new_qc.push_wire(new_wire);
//new_qc.push_wire(new_wire);
//new_qc.push_wire(new_wire);

//new_qc.push_gate(1, new_gate);
//new_qc.push_cgate("U,1", "1,2", C_2);
//new_qc.push_cgate("U,1", "1,3", C_3);
//new_qc.push_cgate("U,1", "1,4", C_4);
//new_qc.push_gate(2, new_gate);
//new_qc.push_cgate("U,1", "2,3", C_2);
//new_qc.push_cgate("U,1", "2,4", C_3);
//new_qc.push_gate(3, new_gate);
//new_qc.push_cgate("U,1", "3,4", C_2);
//new_qc.push_gate(4, new_gate);
//new_qc.change_initial_state(2,4, 1);
//std::cout << new_qc;
//
//matrix<int> outcome = new_qc.measure(10000);
//new_qc.bar_chart(outcome);