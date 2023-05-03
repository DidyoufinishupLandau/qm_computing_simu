#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"

qubit qubit::get_qubit() const
{
	return *this;
}
qubit::qubit()
{
	complex<double> input_temp(1, 0);
	"1;0" >> basis_1;
	"0;1" >> basis_2;
	coefficient_1 = input_temp;
	coefficient_2 = input_temp * 0;
}
qubit::qubit(int input_int)
{
	complex<double> one(1, 0);
	complex<double> zero(0, 0);
	"1;0" >> basis_1;
	"0;1" >> basis_2;
	if (input_int == 1)//|1> 
	{
		coefficient_1 = zero;
		coefficient_2 = one;
	}
	if (input_int == 0)//|1> 
	{
		coefficient_2 = zero;
		coefficient_1 = one;
	}
}
qubit::qubit(matrix<complex<double>> input_basis_1, matrix<complex<double>> input_basis_2, complex<double> input_coefficient_1, complex<double> input_coefficient_2)
{
	if (input_basis_1.get_columns() != 1) { std::cout << "Invalid basis 1 column size" << std::endl; }
	if (input_basis_1.get_rows() != 2) { std::cout << "Invalid basis 1 row size" << std::endl; }
	if (input_basis_2.get_columns() != 1) { std::cout << "Invalid basis 2 column size" << std::endl; }
	if (input_basis_2.get_rows() != 2) { std::cout << "Invalid basis 2 row size" << std::endl; }
	basis_1 = input_basis_1;
	basis_2 = input_basis_2;
	coefficient_1 = input_coefficient_1;
	coefficient_2 = input_coefficient_2;
}
qubit::qubit(complex<double> input_coefficient_1, complex<double> input_coefficient_2)
{
	"1;0" >> basis_1;
	"0;1" >> basis_2;
	coefficient_1 = input_coefficient_1;
	coefficient_2 = input_coefficient_2;
}
matrix<complex<double>> qubit::matrix_qubit() const
{
	matrix<complex<double>> new_matrix = basis_1 * coefficient_1 + basis_2 * coefficient_2;
	return new_matrix;
}
qubit::qubit(const qubit& input_qubit)
{
	basis_1 = input_qubit.basis_1;
	basis_2 = input_qubit.basis_2;
	coefficient_1 = input_qubit.coefficient_1;
	coefficient_2 = input_qubit.coefficient_2;
}
qubit& qubit::operator=(const qubit& right_qubit)
{
	if (&right_qubit == this) return *this;	//self-assignment check;
	basis_1 = right_qubit.basis_1;
	basis_2 = right_qubit.basis_2;
	coefficient_1 = right_qubit.coefficient_1;
	coefficient_2 = right_qubit.coefficient_2;
	return *this;
}
qubit& qubit::operator=(qubit&& right_qubit) noexcept
{
	std::swap(coefficient_1, right_qubit.coefficient_1);
	std::swap(coefficient_2, right_qubit.coefficient_2);
	std::swap(basis_1, right_qubit.basis_1);
	std::swap(basis_2, right_qubit.basis_2);
	return *this;
}
qubit::qubit(qubit&& input_qubit) noexcept
{
	basis_1 = input_qubit.basis_1;
	basis_2 = input_qubit.basis_2;
	coefficient_1 = input_qubit.coefficient_1;
	coefficient_2 = input_qubit.coefficient_2;
	input_qubit.basis_1.clear();
	input_qubit.basis_2.clear();
	input_qubit.coefficient_1 = 0;
	input_qubit.coefficient_2 = 0;

}

//return private value
matrix<complex<double>> qubit::get_basis_1()const { return basis_1; }
matrix<complex<double>> qubit::get_basis_2()const { return basis_2; }
complex<double> qubit::get_coefficient_1()const { return coefficient_1; }
complex<double> qubit::get_coefficient_2()const { return coefficient_2; }
//change coefficient assign to basis
void qubit::change_coefficient(complex<double> input_coefficient_1, complex<double> input_coeffcient_2)
{
	coefficient_1 = input_coefficient_1;
	coefficient_2 = input_coeffcient_2;
}
//change qubit basis
void qubit::change_basis(matrix<complex<double>> base_1, matrix<complex<double>> base_2)
{
	basis_1 = base_1;
	basis_2 = base_2;
}
//change qubit state 1 is |1> 0 is |0>.
void qubit::change_state(int input_int)
{
	qubit new_qubit(input_int);
	coefficient_1 = new_qubit.coefficient_1;
	coefficient_2 = new_qubit.coefficient_2;
	basis_1 = new_qubit.basis_1;
	basis_2 = new_qubit.basis_2;
}
//print out qubit state
std::ostream& operator<<(std::ostream& ostream, const qubit& input_qubit)
{

	if ((input_qubit.coefficient_1.get_real() != 0 || input_qubit.coefficient_1.get_imaginary() != 0) && input_qubit.coefficient_2.get_real() != 0 || input_qubit.coefficient_2.get_imaginary() != 0)
	{
		ostream << input_qubit.coefficient_1 << "|0>" << input_qubit.coefficient_2 << "|1>";
		return ostream;
	}

	if ((input_qubit.coefficient_1.get_real() != 0|| input_qubit.coefficient_1.get_imaginary() != 0) && (input_qubit.coefficient_2.get_real() == 0 && input_qubit.coefficient_2.get_imaginary() == 0))
	{
		ostream << input_qubit.coefficient_1 << "|0>";
		return ostream;
	}
	if ((input_qubit.coefficient_2.get_real() != 0 || input_qubit.coefficient_2.get_imaginary() != 0)&& (input_qubit.coefficient_1.get_real() == 0 && input_qubit.coefficient_1.get_imaginary() == 0))
	{
		ostream << input_qubit.coefficient_2 << "|1>";
		return ostream;
	}
}