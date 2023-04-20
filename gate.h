#pragma once
#ifndef GATE_H
#define GATE_H
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdlib.h>

#include "complex.h"
#include "matrix.h"
#include "qubit.h"
using namespace namespace_one;
class gates
{
public:
	~gates() {};

	virtual gates* operator*(const gates& right_gate) const = 0;
	virtual qubit operator*(const qubit& input_qubit) const = 0;
	virtual matrix<complex<double>> matrix_gate() const = 0;
	virtual void change_name(std::string input_name) = 0;
	virtual std::string get_name() const = 0;
};
class H:public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	H() 
	{
		matrix<complex<double>> temp(2, 2);
		complex<double> input_complex(pow(2, -0.5), 0);
		temp[0] = input_complex;
		temp[1] = input_complex;
		temp[2] = input_complex;
		temp[3] = input_complex * -1;
		gate = temp;
		name = "H";
	}
	~H() {};
	H(const H& input_H);
	H(H&& input_matrix) noexcept;

	H& operator=(const H& right_gate);
	H& operator=(H&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	H get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class O :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	O(complex<double> complex_1, complex<double> complex_2, complex<double> complex_3, complex<double> complex_4)
	{
		matrix<complex<double>> new_matrix(2, 2);
		new_matrix[0] = complex_1;
		new_matrix[1] = complex_2;
		new_matrix[2] = complex_3;
		new_matrix[3] = complex_4;
		gate = new_matrix;
		name = "O";
	}
	O(matrix<complex<double>> input_matrix)
	{
		gate = input_matrix;
		name = "O";
	}
	~O() {};

	O(const O& input_H);
	O(O&& input_matrix) noexcept;

	O& operator=(const O& right_gate);
	O& operator=(O&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	O get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class X:public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	X()
	{
		matrix<complex<double>> temp(2, 2);
		temp[0] = 0;
		temp[1] = 1;
		temp[2] = 1;
		temp[3] = 0;
		gate = temp;
		name = "X";
	}
	~X() {};

	X(const X& input_H);
	X(X&& input_matrix) noexcept;

	X& operator=(const X& right_gate);
	X& operator=(X&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	X get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class Y :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	Y()
	{
		matrix<complex<double>> temp(2, 2);
		complex<double> one(0, 1);
		complex<double> negative_one(0, -1);
		complex<double> zero(0, 0);
		temp[0] = zero;
		temp[1] = one;
		temp[2] = negative_one;
		temp[3] = zero;
		gate = temp;
		name = "Y";
	}
	~Y() {};

	Y(const Y& input_H);
	Y(Y&& input_matrix) noexcept;

	Y& operator=(const Y& right_gate);
	Y& operator=(Y&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	Y get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class Z :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	Z()
	{
		matrix<complex<double>> temp(2, 2);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = -1;
		gate = temp;
		name = "Z";
	}
	~Z() {};

	Z(const Z& input_H);
	Z(Z&& input_matrix) noexcept;

	Z& operator=(const Z& right_gate);
	Z& operator=(Z&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	Z get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class S :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	S()
	{
		matrix<complex<double>> temp(2, 2);
		complex<double> temp_complex(0, 1);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = temp_complex;
		gate = temp;
		name = "S";
	}
	~S() {};

	S(const S& input_H);
	S(S&& input_matrix) noexcept;

	S& operator=(const S& right_gate);
	S& operator=(S&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	S get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class T :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	T()
	{
		matrix<complex<double>> temp(2, 2);
		complex<double> temp_complex(std::cos(3.14159265358979 / 4), std::sin(3.14159265358979 / 4));
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = temp_complex;
		gate = temp;
		name = "T";
	}
	~T() {};

	T(const T& input_H);
	T(T&& input_matrix) noexcept;

	T& operator=(const T& right_gate);
	T& operator=(T&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	T get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class I :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	I()
	{
		matrix<complex<double>> temp(2, 2);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;
		gate = temp;
		name = "I";
	}
	~I() {};

	I(const I& input_H);
	I(I&& input_matrix) noexcept;

	I& operator=(const I& right_gate);
	I& operator=(I&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	I get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class P :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	P(double angle)
	{
		matrix<complex<double>> temp(2, 2);
		complex<double> phase(std::cos(angle), std::sin(angle));
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = phase;
		gate = temp;
		name = "P";
	}
	~P() {};

	P(const P& input_H);
	P(P&& input_matrix) noexcept;

	P& operator=(const P& right_gate);
	P& operator=(P&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	P get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class one :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	one()
	{
		matrix<complex<double>> temp(2, 2);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;
		gate = temp;
		name = "1";
	}
	~one() {};

	one(const one& input_H);
	one(one&& input_matrix) noexcept;

	one& operator=(const one& right_gate);
	one& operator=(one&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	one get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class zero :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	zero()
	{
		matrix<complex<double>> temp(2, 2);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;
		gate = temp;
		name = "0";
	}
	~zero() {};

	zero(const zero& input_H);
	zero(zero&& input_matrix) noexcept;

	zero& operator=(const zero& right_gate);
	zero& operator=(zero&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	zero get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
class padding :public gates
{
private:
	matrix<complex<double>> gate;
	std::string name;
public:
	padding()
	{
		matrix<complex<double>> temp(2, 2);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;
		gate = temp;
		name = "-";
	}
	~padding() {};

	padding(const padding& input_H);
	padding(padding&& input_matrix) noexcept;

	padding& operator=(const padding& right_gate);
	padding& operator=(padding&& right_gate) noexcept;
	gates* operator*(const gates& right_gate) const override;
	qubit operator*(const qubit& input_qubit) const override;

	padding get_gate() const;
	matrix<complex<double>> matrix_gate() const;
	void change_name(std::string input_name);
	std::string get_name() const;
};
//class control_U :public gates
//{
//private:
//	matrix<complex<double>> gate;
//	std::vector<std::string> position;
//	std::string name;
//public:
//	control_U(gates* input_gates)
//	{
//		gate = input_gates->matrix_gate();
//		name = "U";
//	}
//	~control_U() {};
//
//	control_U(const control_U& input_H);
//	control_U(control_U&& input_matrix) noexcept;
//
//	control_U& operator=(const control_U& right_gate);
//	control_U& operator=(control_U&& right_gate) noexcept;
//	gates* operator*(const gates& right_gate) const override;
//	qubit operator*(const qubit& input_qubit) const override;
//
//	control_U get_gate() const;
//	void set_position(std::string input_position);
//	std::vector<std::string> get_position();
//	matrix<complex<double>> matrix_gate() const;
//	void change_name(std::string input_name);
//	std::string get_name() const;
//};
#endif // GATE_H

