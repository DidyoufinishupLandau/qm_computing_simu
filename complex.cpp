#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "complex.h"


complex complex::get_self()
{
	return *this;
}
complex::complex(double input_double)
{
	x = input_double;
	y = 0;
}

complex::complex(double input_x, double input_y)
{
	x = input_x;
	y = input_y;
}
complex::complex(const complex& input_complex)
{
	x = input_complex.get_real();
	y = input_complex.get_imaginary();
}
complex::complex(complex&& input_complex) noexcept
{
	x = input_complex.get_real();
	y = input_complex.get_imaginary();
	input_complex.x = 0;
	input_complex.y = 0;
}
complex complex::complex_conjugate() const
{
	complex new_complex(x, -y);
	return new_complex;
}

complex& complex::operator=(const complex& right_complex)
{
	if (&right_complex == this) return *this;
	x = right_complex.x;
	y = right_complex.y;
	return *this;
}
complex& complex::operator=(complex&& right_complex) noexcept
{
	std::swap(x, right_complex.x);
	std::swap(y, right_complex.y);
	return *this;
}

complex& complex::operator=(const double& right_double)
{
	x = right_double;
	y = 0;
	return *this;
}
complex& complex::operator=(double&& right_double) noexcept
{
	std::swap(x, right_double);
	y = 0;
	return *this;
}

double complex::modulus() const
{
	double modulus = pow(pow(x, 2) + pow(y, 2), 0.5);
	return modulus;
}

double complex::arg() const
{
	//return radian
	double argument = std::atan2(y, x);
	if (argument < 0) { argument = 2 * 3.14159265358979323846 + argument; }
	return argument;
}

void complex::set_x(const double input_x)
{
	x += input_x;
}
void complex::set_y(const double input_y)
{
	y += input_y;
}
//overload functions

complex complex::operator+(const complex& complex_number) const
{
	complex new_complex(x + complex_number.get_real(), y + complex_number.get_imaginary());
	return new_complex;
}


complex complex::operator-(const complex& complex_number) const
{
	complex new_complex(x - complex_number.get_real(), y - complex_number.get_imaginary());
	return new_complex;
}

complex complex::operator*(const complex& complex_number) const
{
	double x_input = complex_number.get_real();
	double y_input = complex_number.get_imaginary();
	complex new_complex(x * x_input - y * y_input, x * y_input + y * x_input);
	return new_complex;
}

complex complex::operator/(const complex& complex_number) const
{
	double x_input = complex_number.get_real();
	double y_input = complex_number.get_imaginary();
	double modulus_sqaure_input = pow(complex_number.modulus(), 2);

	complex new_complex((x * x_input + y * y_input) / modulus_sqaure_input, (y * x_input - x * y_input) / modulus_sqaure_input);
	return new_complex;
}

complex operator*(const complex& complex_num, const double& real_num)
{
	complex new_comlex(complex_num.get_real() * real_num, complex_num.get_imaginary() * real_num);
	return new_comlex;
}
complex operator*(const double& real_num, const complex& complex_num)
{
	complex new_comlex(complex_num.get_real() * real_num, complex_num.get_imaginary() * real_num);
	return new_comlex;
}
complex operator+(const complex& complex_num, const double& real_num)
{
	complex new_comlex(complex_num.get_real() + real_num, complex_num.get_imaginary() + real_num);
	return new_comlex;
}
complex operator+(const double& real_num, const complex& complex_num)
{
	complex new_comlex(complex_num.get_real() + real_num, complex_num.get_imaginary() + real_num);
	return new_comlex;
}
complex operator-(const complex& complex_num, const double& real_num)
{
	complex new_comlex(complex_num.get_real() - real_num, complex_num.get_imaginary() - real_num);
	return new_comlex;
}
complex operator-(const double& real_num, const complex& complex_num)
{
	complex new_comlex(complex_num.get_real() - real_num, complex_num.get_imaginary() - real_num);
	return new_comlex;
}
complex operator/(const complex& complex_num, const double& real_num)
{
	complex new_comlex(complex_num.get_real() / real_num, complex_num.get_imaginary() / real_num);
	return new_comlex;
}
complex operator/(const double& real_num, const complex& complex_num)
{
	complex complex_conjugate = complex_num.complex_conjugate();
	double modulus = complex_num.modulus();
	complex new_complex = real_num * complex_conjugate / (modulus);
	return new_complex;
}
void complex::operator+=(const complex& complex_num)
{
	x = x + complex_num.get_real();
	y = y + complex_num.get_imaginary();
}

void complex::operator+=(const double& real_num)
{
	x = x + real_num;
	y = y + real_num;
}
void complex::operator-=(const complex& complex_num)
{
	x = x - complex_num.get_real();
	y = y - complex_num.get_imaginary();
}

void complex::operator-=(const double& real_num)
{
	x = x - real_num;
	y = y - real_num;
}
