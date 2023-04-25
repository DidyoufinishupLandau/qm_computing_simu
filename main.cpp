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
	std::cout << "test gate functionality" << std::endl;
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	complex<double> rotation(std::cos(0), std::sin(3.1415926 / 2));
	std::cout << one << zero << rotation << std::endl;
	std::cout << "initialize gates." << std::endl;
	gates* x_pointer = new X();
	gates* y_pointer = new Y();
	gates* z_pointer = new Z();
	gates* I_pointer = new I();
	gates* H_pointer = new H();
	gates* s_pointer = new S();
	gates* t_pointer = new T();
	gates* o_pointer = new O(one, zero, zero, rotation);
	std::cout << "show matrix representation." << std::endl;
	std::cout << x_pointer->matrix_gate() << std::endl;
	std::cout << y_pointer->matrix_gate() << std::endl;
	std::cout << z_pointer->matrix_gate() << std::endl;
	std::cout << I_pointer->matrix_gate() << std::endl;
	std::cout << H_pointer->matrix_gate() << std::endl;
	std::cout << s_pointer->matrix_gate() << std::endl;
	std::cout << t_pointer->matrix_gate() << std::endl;
	std::cout << o_pointer->matrix_gate() << std::endl;
	std::cout << " test qubit with initial state | 1>" << std::endl;
	qubit test_qubit(1);
	std::cout << test_qubit << std::endl;
	std::cout << " matrix representation" << std::endl;
	std::cout << test_qubit.matrix_qubit() << std::endl;
	test_qubit.change_state(0);
	std::cout << test_qubit << std::endl;
	std::cout << test_qubit.matrix_qubit() << std::endl;
	std::cout << " test gate act on qubit" << std::endl;
	std::cout << *x_pointer * test_qubit << std::endl;
	std::cout << *y_pointer * test_qubit << std::endl;
	std::cout << *z_pointer * test_qubit << std::endl;
	std::cout << *I_pointer * test_qubit << std::endl;
	std::cout << *H_pointer * test_qubit << std::endl;
	std::cout << *s_pointer * test_qubit << std::endl;
	std::cout << *t_pointer * test_qubit << std::endl;
	std::cout << " test wire" << std::endl;
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
	std::cout << " test quantum circuit " << std::endl;
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
	std::cout << "now try to delete 4th column" << std::endl;
	new_qc.delete_gate(4);
	std::cout << new_qc << std::endl;
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
	ft.measure(10000);
	ft.bar_chart();

	ft.history_switch(true);
	ft.measure(2);
	std::vector<std::vector<matrix<complex<double>>>> qubit_history = ft.get_qubit_history();
	for (size_t i{}; i < qubit_history.size(); i++) 
	{
		for (size_t j{}; j < qubit_history[i].size(); j++)
		{
			std::cout << qubit_history[i][j] << std::endl;
		}
	}
}
