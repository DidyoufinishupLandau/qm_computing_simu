#pragma once
#ifndef QUBIT_H
#define QUBIT_H
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "complex.h"
#include "matrix.h"

class qubit
{
protected:

	matrix<complex<double>> basis_1;
	matrix<complex<double>> basis_2;
	complex<double> coefficient_1;
	complex<double> coefficient_2;
public:
	//constructors
	qubit();
	qubit(matrix<complex<double>> input_basis_1, matrix<complex<double>> input_basis_2,\
			complex<double> coefficient_1, complex<double> coeffcient_2);
	qubit(complex<double> coefficient_1, complex<double> coeffcient_2);
	qubit(int input_int);
	qubit(const qubit& input_qubit);//deep copy
	qubit(qubit&& input_qubit) noexcept;
	~qubit() {};//destructor
	//copy and move assignment
	qubit& operator=(const qubit& right_qubit);
	qubit& operator=(qubit&& right_qubit) noexcept;


	//pass self
	qubit get_qubit() const;
	//return private value
	matrix<complex<double>> matrix_qubit() const;
	matrix<complex<double>> get_basis_1()const;
	matrix<complex<double>> get_basis_2()const;
	complex<double> get_coefficient_1()const;
	complex<double> get_coefficient_2()const;
	//change private value
	void change_coefficient(complex<double> coefficient_1, complex<double> coeffcient_2);
	void change_basis(matrix<complex<double>> base_1, matrix<complex<double>> base_2);
	void change_state(int input_int);
	//insert value and output value
	friend std::ostream& operator<< (std::ostream& ostream, const qubit& input_qubit);
	//friend void operator>> (std::string input_string, qubit& input_qubit);

};
std::ostream& operator<< (std::ostream& ostream, const qubit& input_qubit);
#endif // QUBIT_H