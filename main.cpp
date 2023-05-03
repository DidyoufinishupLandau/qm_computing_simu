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
void test_complex() 
{
	std::cout << "test complex class functionality" << std::endl;
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	complex<double> i(0, 1);//complex plan rotation
	std::cout << "1: " << one << std::endl;
	std::cout << "zero: " << zero << std::endl;
	std::cout << "0+i: " << i << std::endl;
	std::cout << "1+0: " << one + zero << std::endl;
	std::cout << "1+i:" << one + i << std::endl;
	std::cout << "1-i:" << one - i << std::endl;
	std::cout << "1/i:" << one / i << std::endl;
	std::cout << "1*i:" << one * i << std::endl;
}
void test_matrix()
{
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	complex<double> i(0, 1);
	matrix<double> double_matrix;
	"1,0;0,1">>double_matrix;
	std::cout << "get self" << std::endl;
	std::cout << double_matrix.get_self() << std::endl;
	std::cout << "columns: " << double_matrix.get_columns() << std::endl;
	std::cout << "rows " << double_matrix.get_rows() << std::endl;
	std::cout << "rows " << double_matrix.get_rows() << std::endl;
	std::cout << "Now lets put complex number in matrix" << std::endl;
	matrix<complex<double>> complex_matrix(2,2);
	complex_matrix[0] = one;
	complex_matrix[1] = zero;
	complex_matrix[2] = zero;
	complex_matrix[3] = i;
	matrix<complex<double>> new_matrix;
	std::cout << "complex matrix" << complex_matrix << std::endl;
	std::cout << "Test direct sum and tensor product" << std::endl;
	std::cout << "Tensor product" << std::endl;
	new_matrix = complex_matrix.tensor(complex_matrix);
	std::cout << new_matrix << std::endl;
	std::cout << "use the last matrix do one more tensor product" << std::endl;
	std::cout<<new_matrix.tensor(complex_matrix)<<std::endl;
	std::cout << "Direct sum" << std::endl;
	std::cout << complex_matrix.direct_sum(complex_matrix) << std::endl;
	std::cout << "complex matrix * complex matrix" << std::endl;
	std::cout << complex_matrix * complex_matrix << std::endl;
	std::cout << "complex matrix + complex matrix" << std::endl;
	std::cout << complex_matrix + complex_matrix << std::endl;
	std::cout << "complex matrix * i" << complex_matrix * i << std::endl;
	std::cout << "complex matrix * 6" << complex_matrix * 6 << std::endl;
	std::cout << "clear:" << complex_matrix.clear() << std::endl;
}
void test_qubit() 
{
	complex<double> one(1,0);
	complex<double> zero(0,0);
	matrix<complex<double>> basis_one;
	"1;1" >> basis_one;
	basis_one = basis_one * pow(2, -1.0/2);
	matrix<complex<double>> basis_two;
	"1;-1" >> basis_two;
	basis_two = basis_two * pow(2, -1.0/2);
	std::cout << "basis one" << std::endl;
	std::cout << basis_one << std::endl;
	std::cout << "basis two" << std::endl;
	std::cout << basis_two << std::endl;
	qubit qubit_one(basis_one, basis_two, one, zero);
	qubit qubit_two(basis_one, basis_two, zero, one);
	qubit qubit_three(one, zero);
	qubit qubit_four(0);
	std::cout << "qubit one" << std::endl;
	std::cout << qubit_one << std::endl;
	std::cout << "qubit two" << std::endl;
	std::cout << qubit_two << std::endl;
	std::cout << "qubit three" << std::endl;
	std::cout << qubit_three << std::endl;
	std::cout << "qubit four" << std::endl;
	std::cout << qubit_four << std::endl;
	std::cout << "qubit one basis 1:" << std::endl;
	std::cout << qubit_one.get_basis_1() << std::endl;
	std::cout << "qubit one basis 2:" <<  std::endl;
	std::cout << qubit_one.get_basis_2() << std::endl;
	std::cout << "qubit one coefficient 1: " << qubit_one.get_coefficient_1() << std::endl;
	std::cout << "qubit one coefficient 2: " << qubit_one.get_coefficient_2() << std::endl;
	qubit_four.change_state(1);
	std::cout << "qubit four change state to |1>: " << qubit_four << std::endl;
	qubit_four.change_basis(basis_one, basis_two);
	std::cout << "qubit four change basis to basis one and two: " << qubit_four.get_basis_1() << std::endl;
}
void test_gate() 
{
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	complex<double> rotation(std::cos(0), std::sin(3.1415926 / 2));
	gates* x_pointer = new X();
	gates* y_pointer = new Y();
	gates* z_pointer = new Z();
	gates* I_pointer = new I();
	gates* H_pointer = new H();
	gates* s_pointer = new S();
	gates* t_pointer = new T();
	gates* o_pointer = new O(one, zero, zero, rotation);
	std::cout << "show matrix representation." << std::endl;
	std::cout << "X" << std::endl;
	std::cout << x_pointer->matrix_gate() << std::endl;
	std::cout << "Y" << std::endl;
	std::cout << y_pointer->matrix_gate() << std::endl;
	std::cout << "Z" << std::endl;
	std::cout << z_pointer->matrix_gate() << std::endl;
	std::cout << "I" << std::endl;
	std::cout << I_pointer->matrix_gate() << std::endl;
	std::cout << "H" << std::endl;
	std::cout << H_pointer->matrix_gate() << std::endl;
	std::cout << "S" << std::endl;
	std::cout << s_pointer->matrix_gate() << std::endl;
	std::cout << "t" << std::endl;
	std::cout << t_pointer->matrix_gate() << std::endl;
	std::cout << "o" << std::endl;
	std::cout << o_pointer->matrix_gate() << std::endl;
	//initialize a qubit with state |1>
	std::cout << "initialize a qubit with state |1>" << std::endl;
	qubit test_qubit(1);
	std::cout << test_qubit << std::endl;
	std::cout << "qubit matrix representation" << std::endl;
	std::cout << test_qubit.matrix_qubit() << std::endl;
	std::cout << "X gate apply to qubit" << std::endl;
	std::cout << *x_pointer * test_qubit << std::endl;
	std::cout << "Y gate apply to qubit" << std::endl;
	std::cout << (*y_pointer * test_qubit) << std::endl;
	std::cout << "Z gate apply to qubit" << std::endl;
	std::cout << *z_pointer * test_qubit << std::endl;
	std::cout << "I gate apply to qubit" << std::endl;
	std::cout << *I_pointer * test_qubit << std::endl;
	std::cout << "H gate apply to qubit" << std::endl;
	std::cout << *H_pointer * test_qubit << std::endl;
	std::cout << "S gate apply to qubit" << std::endl;
	std::cout << *s_pointer * test_qubit << std::endl;
	std::cout << "T gate apply to qubit" << std::endl;
	std::cout << *t_pointer * test_qubit << std::endl;
}
void test_wire() 
{
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	complex<double> rotation(std::cos(0), std::sin(3.1415926 / 2));
	gates* x_pointer = new X();
	gates* y_pointer = new Y();
	gates* z_pointer = new Z();
	gates* I_pointer = new I();
	gates* H_pointer = new H();
	gates* s_pointer = new S();
	gates* t_pointer = new T();
	gates* o_pointer = new O(one, zero, zero, rotation);
	wires new_wire(1);
	std::cout << "The qubit one the wire has state:" << new_wire.get_qubit() << std::endl;
	new_wire.push_gate(x_pointer);
	new_wire.push_gate(y_pointer);
	new_wire.push_gate(z_pointer);
	std::cout << "matrix representation of the sequence of gate" << std::endl;
	std::cout << new_wire.matrix_wire() << std::endl;
	std::cout << "Test gate act on qubit" << std::endl;
	std::cout << new_wire.test_gate() << std::endl;
	new_wire.push_gate(s_pointer);
	new_wire.push_gate(t_pointer);
	new_wire.push_gate(I_pointer);
	new_wire.push_gate(H_pointer);
	new_wire.insert_gate(1, H_pointer);
	std::cout << "The gate sequence should be X H Y Z S T I H. The order of gate acting on qubit is from left to right" << std::endl;
	new_wire.print();
	std::cout << "Delete the 4th gate" << std::endl;
	new_wire.delete_gate(4);
	new_wire.print();
}
void test_qc() 
{
	gates* H_pointer = new H();
	double pi = 3.14159265358979323846;

	qc new_qc(5, 1);
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "H"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "Y"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "Z"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "T"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "S"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "I"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "X"); }
	std::cout << new_qc << std::endl;//print out

	std::cout << "insert control not gate" << std::endl;
	new_qc.insert_cgate("1,U", "1,1", "1,2", "X");
	new_qc.insert_cgate("1,U", "2,2", "1,3", "X");
	new_qc.insert_cgate("1,U", "3,3", "1,4", "X");
	new_qc.insert_cgate("1,U", "4,4", "1,5", "X");
	std::cout << new_qc << std::endl;

	//The time cost of measure function depend on the performance of computer. 
	//because the implementation of parallel computation
	//But the difference would be small for measurement number under 10000.
	new_qc.measure(1000);//measure this quantum circuit 1000 times.
	new_qc.bar_chart();//print out probability bar chart.
	std::cout << "now try to replace the third wire" << std::endl;
	wires new_wire(1);
	std::cout << "two hadmard gate on new wire" << std::endl;
	new_wire.push_gate(2, H_pointer);
	new_wire.print();

	new_qc.replace_wire(3, new_wire);
	std::cout << new_qc << std::endl;
	std::cout << "try to insert the gate in third wire and the second wire." << std::endl;
	new_qc.insert_gate(2, 2, "H");
	new_qc.insert_gate(3, 2, "Z");
	std::cout << new_qc << std::endl;
	std::cout << "delete the first gate on second wire" << std::endl;
	new_qc.delete_gate(2, 1);
	std::cout << new_qc << std::endl;
	std::cout << "now try to delete 4th and all of columns after 5th column" << std::endl;
	new_qc.delete_gate(4);
	int wire_size = new_qc[0].size();
	while (new_qc[0].size() > 5) { new_qc.delete_gate(new_qc[0].size()); }
	std::cout << new_qc << std::endl;
	new_qc.measure(1000);
	new_qc.bar_chart();
	std::cout << "Two hadmard gate apply on a same qubit is same as act nothing on the qubit" << std::endl;
	std::cout << "The Z gate flips the sign of the qubit but the probability is equal to the squared of the coefficient" << std::endl;
	std::cout << "Clearly, the third qubit has 100% chance to have state one as expected" << std::endl;
	//example of constructing a fourier transform quantum circuit with 5 qubits
	std::cout << "fourier transform" << std::endl;
	qc ft(4, 1);
	ft.change_initial_state(2, 3, 0);

	ft.push_gate(1, "H");
	for (size_t i{ 1 }; i < ft.num_wire(); i++)
	{
		gates* rotational_gates_pointer = new P(2 * pi / (pow(2, i + 1)));//R_n rotational gate
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
	//here we can test the static data
	ft.measure(1000);
	ft.bar_chart();

	ft.history_switch(true);
	ft.measure(2);
	std::vector<std::vector<matrix<complex<double>>>> qubit_history = ft.get_qubit_history();
	for (size_t i{}; i < qubit_history.size(); i++)
	{
		std::cout << "Qubit history: " << i + 1 << std::endl;
		for (size_t j{}; j < qubit_history[i].size(); j++)
		{
			std::cout << j << "th qubit" << std::endl;
			std::cout << qubit_history[i][j] << std::endl;
		}
	}
	ft.history_switch(false);
}

int main()
{
	test_complex();
	test_matrix();
	test_qubit();
	test_gate();
	test_wire();
	test_qc();
	//Demonstration used in report
	qc new_qc(5, 1);
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "H"); }
	for (size_t i{}; i < new_qc.num_wire(); i++) { new_qc.push_gate(i + 1, "Y"); }
	std::cout << new_qc << std::endl;
	std::cout << "insert control not gate" << std::endl;
	new_qc.insert_cgate("1,U", "1,1", "1,2", "X");
	new_qc.push_cgate("1,1,U", "2,3,4", "X");
	std::cout << new_qc << std::endl;
	std::cout << "now try to replace the third wire" << std::endl;
	wires new_wire(1);
	std::cout << "two hadmard gate on new wire" << std::endl;
	std::cout << "delete the first gate on second wire" << std::endl;
	gates* H_pointer = new H();
	new_wire.push_gate(2, H_pointer);
	new_wire.print();
	std::cout << "Test new wire by computing its matrix" << std::endl;
	std::cout<<new_wire.test_gate()<<std::endl;
	new_qc.replace_wire(3, new_wire);
	new_qc.push_wire(new_wire);
	new_qc.delete_gate(2, 1);
	std::cout << new_qc << std::endl;
	new_qc.set_max_history_num(200);//set the max number history to 200.
	new_qc.measure(1000);
	new_qc.bar_chart();
	new_qc.history_switch(true);//switch on to record the history of qubits
	new_qc.measure(1);
	//print out qubit history
	std::vector<std::vector<matrix<complex<double>>>> qubit_history = new_qc.get_qubit_history();
	for (size_t i{}; i < qubit_history.size(); i++)
	{
		std::cout << "Qubit history: " << i + 1 << std::endl;
		for (size_t j{}; j < qubit_history[i].size(); j++)
		{
			std::cout << j + 1 << "th qubit" << std::endl;
			std::cout << qubit_history[i][j] << std::endl;
		}
	}
	std::cout << "The matrix representation of the circuit is also avaiable" << std::endl;
	std::cout << "However, it is not recommanded for large circuit" << std::endl;
	qc matrix_qc(2, 1);
	std::cout << "We add a control not gate in out circuit" << std::endl;
	matrix_qc.push_cgate("1,U", "1,2", "X");
	std::cout << matrix_qc.matrix_circuit() << std::endl;
	std::cout << "add pauli x gate" << std::endl;
	for (size_t i{}; i < matrix_qc.num_wire(); i++) { matrix_qc.push_gate(i + 1, "X"); }
	std::cout << matrix_qc.matrix_circuit() << std::endl;
	std::cout << "add hadmard gate" << std::endl;
	for (size_t i{}; i < matrix_qc.num_wire(); i++) { matrix_qc.push_gate(i + 1, "H"); }
	std::cout << "matrix circuit" << std::endl;
	std::cout << matrix_qc.matrix_circuit() << std::endl;
	std::cout << "circuit diagram" << std::endl;
	std::cout << matrix_qc << std::endl;
	std::cout << "qubit state" << std::endl;
	std::cout << matrix_qc.matrix_qubit() << std::endl;
	std::cout << "now we use the gate matrix multiply the qubit state" << std::endl;
	matrix<complex<double>> qubit_final_state = matrix_qc.matrix_circuit() * matrix_qc.matrix_qubit();
	std::cout << qubit_final_state << std::endl;
	std::cout << "Now, we measure the circuit to test if the circuit matrix representation works properly" << std::endl;
	matrix_qc.measure(100);
	matrix_qc.bar_chart();
	std::cout << "The circuit matrix representation works properly" << std::endl;

}
