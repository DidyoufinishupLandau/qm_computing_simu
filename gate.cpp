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
using namespace namespace_one;

I::I(const I& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
I::I(I&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

I& I::operator=(const I& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
I& I::operator=(I&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* I::operator*(const gates& right_gate) const
{
	const I& other_H = dynamic_cast<const I&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit I::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

I I::get_gate() const
{
	return *this;
}
matrix<complex<double>> I::matrix_gate() const
{
	return gate;
}
void I::change_name(std::string input_name)
{
	name = input_name;
}
std::string I::get_name() const
{
	return name;
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
H::H(const H& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
H::H(H&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

H& H::operator=(const H& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
H& H::operator=(H&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* H::operator*(const gates& right_gate) const
{

	const H& other_H = dynamic_cast<const H&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit H::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

H H::get_gate() const
{
	return *this;
}
matrix<complex<double>> H::matrix_gate() const
{
	return gate;
}
void H::change_name(std::string input_name)
{
	name = input_name;
}
std::string H::get_name() const
{
	return name;
}

//oooooooooooooooooooooooooooooooooo
O::O(const O& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
O::O(O&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

O& O::operator=(const O& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
O& O::operator=(O&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* O::operator*(const gates& right_gate) const
{
	const O& other_O = dynamic_cast<const O&>(right_gate);
	return new O(gate * other_O.gate); //gate* other_H.gate
}
qubit O::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

O O::get_gate() const
{
	return *this;
}
matrix<complex<double>> O::matrix_gate() const
{
	return gate;
}
void O::change_name(std::string input_name)
{
	name = input_name;
}
std::string O::get_name() const
{
	return name;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X::X(const X& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
X::X(X&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

X& X::operator=(const X& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
X& X::operator=(X&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* X::operator*(const gates& right_gate) const
{
	const X& other_H = dynamic_cast<const X&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit X::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

X X::get_gate() const
{
	return *this;
}
matrix<complex<double>> X::matrix_gate() const
{
	return gate;
}
void X::change_name(std::string input_name)
{
	name = input_name;
}
std::string X::get_name() const
{
	return name;
}
//YYYYYYYYYYYYYYYYYYYYYYYY
Y::Y(const Y& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
Y::Y(Y&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

Y& Y::operator=(const Y& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
Y& Y::operator=(Y&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* Y::operator*(const gates& right_gate) const
{
	const Y& other_H = dynamic_cast<const Y&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit Y::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

Y Y::get_gate() const
{
	return *this;
}
matrix<complex<double>> Y::matrix_gate() const
{
	return gate;
}
void Y::change_name(std::string input_name)
{
	name = input_name;
}
std::string Y::get_name() const
{
	return name;
}
//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ

Z::Z(const Z& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
Z::Z(Z&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

Z& Z::operator=(const Z& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
Z& Z::operator=(Z&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* Z::operator*(const gates& right_gate) const
{
	const Z& other_H = dynamic_cast<const Z&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit Z::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

Z Z::get_gate() const
{
	return *this;
}
matrix<complex<double>> Z::matrix_gate() const
{
	return gate;
}
void Z::change_name(std::string input_name)
{
	name = input_name;
}
std::string Z::get_name() const
{
	return name;
}
//SSSSSSSSSSSSSSSSSSSSSSSSSSS
S::S(const S& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
S::S(S&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

S& S::operator=(const S& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
S& S::operator=(S&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* S::operator*(const gates& right_gate) const
{
	const S& other_H = dynamic_cast<const S&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit S::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

S S::get_gate() const
{
	return *this;
}
matrix<complex<double>> S::matrix_gate() const
{
	return gate;
}
void S::change_name(std::string input_name)
{
	name = input_name;
}
std::string S::get_name() const
{
	return name;
}
//TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
T::T(const T& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
T::T(T&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "I";
}

T& T::operator=(const T& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
T& T::operator=(T&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* T::operator*(const gates& right_gate) const
{
	const T& other_H = dynamic_cast<const T&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit T::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}

T T::get_gate() const
{
	return *this;
}
matrix<complex<double>> T::matrix_gate() const
{
	return gate;
}
void T::change_name(std::string input_name)
{
	name = input_name;
}
std::string T::get_name() const
{
	return name;
}
//000000000000000000000000000000000000
zero::zero(const zero& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
zero::zero(zero&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "0";
}

zero& zero::operator=(const zero& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
zero& zero::operator=(zero&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* zero::operator*(const gates& right_gate) const
{
	const zero& other_H = dynamic_cast<const zero&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit zero::operator*(const qubit& input_qubit) const
{
	return input_qubit;
}

zero zero::get_gate() const
{
	return *this;
}
matrix<complex<double>> zero::matrix_gate() const
{
	return gate;
}
void zero::change_name(std::string input_name)
{
	name = input_name;
}
std::string zero::get_name() const
{
	return name;
}
//oneooooooooooooooooooooooooooooooo
one::one(const one& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
one::one(one&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "0";
}

one& one::operator=(const one& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
one& one::operator=(one&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* one::operator*(const gates& right_gate) const
{
	const one& other_H = dynamic_cast<const one&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit one::operator*(const qubit& input_qubit) const
{
	return input_qubit;
}

one one::get_gate() const
{
	return *this;
}
matrix<complex<double>> one::matrix_gate() const
{
	return gate;
}
void one::change_name(std::string input_name)
{
	name = input_name;
}
std::string one::get_name() const
{
	return name;
}
//padding
padding::padding(const padding& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
padding::padding(padding&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "-";
}

padding& padding::operator=(const padding& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
padding& padding::operator=(padding&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* padding::operator*(const gates& right_gate) const
{
	const padding& other_H = dynamic_cast<const padding&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit padding::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}
padding padding::get_gate() const
{
	return *this;
}
matrix<complex<double>> padding::matrix_gate() const
{
	return gate;
}
void padding::change_name(std::string input_name)
{
	name = input_name;
}
std::string padding::get_name() const
{
	return name;
}
//phase
P::P(const P& input_H)
{
	gate = input_H.gate;
	name = input_H.name;
}
P::P(P&& input_H) noexcept
{
	gate = input_H.gate;
	name = input_H.name;
	input_H.gate.clear();
	input_H.name = "P";
}
P& P::operator=(const P& right_gate)
{
	if (&right_gate == this) return *this;
	gate = right_gate.gate;
	name = right_gate.name;
	return *this;
}
P& P::operator=(P&& right_gate) noexcept
{
	std::swap(gate, right_gate.gate);
	std::swap(name, right_gate.name);
	return *this;
}
gates* P::operator*(const gates& right_gate) const
{
	const P& other_H = dynamic_cast<const P&>(right_gate);
	return new O(gate * other_H.gate);
}
qubit P::operator*(const qubit& input_qubit) const
{
	matrix<complex<double>> new_matrix = gate * input_qubit.get_basis_1() * input_qubit.get_coefficient_1() + gate * input_qubit.get_basis_2() * input_qubit.get_coefficient_2();
	qubit new_qubit(new_matrix[0], new_matrix[1]);
	return new_qubit;
}
P P::get_gate() const
{
	return *this;
}
matrix<complex<double>> P::matrix_gate() const
{
	return gate;
}
void P::change_name(std::string input_name)
{
	name = input_name;
}
std::string P::get_name() const
{
	return name;
}
