#pragma once
#ifndef complex_H
#define complex_H
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "matrix.h"
#include <vector>

namespace namespace_one
{
	template<class c_type> class complex;
	template<class c_type> std::ostream& operator<<(std::ostream& ostream, const complex<c_type>& complex_num);
	template<class c_type> std::istream& operator>>(std::istream& istream, complex<c_type>& complex_num);
	template<class c_type>  class complex
	{
	private:
		c_type x{ std::nan("") };
		c_type y{ std::nan("") };
	public:
		complex() = default;
		complex(c_type input_c_type);
		complex(c_type input_x, c_type input_y);
		complex(const complex<c_type>& input_complex);
		complex(complex<c_type>&& input_complex) noexcept;
		~complex() {}

		//functionalities
		complex<c_type> get_self();
		c_type get_real() const { return x; }
		c_type get_imaginary() const { return y; }
		c_type modulus() const;
		c_type arg() const;
		c_type complex_conjugate() const;

		void set_x(const c_type input_x);
		void set_y(const c_type input_y);

		complex<c_type>& operator=(const complex<c_type>& right_complex);
		complex<c_type>& operator=(complex<c_type>&& right_complex) noexcept;

		complex<c_type> operator+(const complex<c_type>& complex_number) const;
		complex<c_type> operator-(const complex<c_type>& complex_number) const;
		complex<c_type> operator*(const complex<c_type>& real_num) const;
		complex<c_type> operator/(const complex<c_type>& real_num) const;

		complex<c_type> operator*(const c_type& real_num) const;

		void operator+=(const complex<c_type>& complex_number);
		void operator-=(const complex<c_type>& complex_number);
		void operator+=(const c_type& complex_number);
		void operator-=(const c_type& complex_number);

		friend std::ostream& operator<< <c_type> (std::ostream& ostream, const complex<c_type>& complex_num);
		friend std::istream& operator>> <c_type> (std::istream& istream, complex<c_type>& complex_num);
	};
}
#endif //COMPLEX_H
using namespace namespace_one;
//constructors
template<class c_type> complex<c_type>::complex(c_type input_c_type)
{
	x = input_c_type;
	y = 0;
}
template<class c_type> complex<c_type>::complex(c_type input_x, c_type input_y)
{
	x = input_x;
	y = input_y;
}
template<class c_type> complex<c_type>::complex(const complex<c_type>& input_complex)
{
	x = input_complex.get_real();
	y = input_complex.get_imaginary();
}
template<class c_type> complex<c_type>::complex<c_type>(complex<c_type>&& input_complex) noexcept
{
	x = input_complex.get_real();
	y = input_complex.get_imaginary();
	input_complex.x = 0;
	input_complex.y = 0;
}
template<class c_type> c_type complex<c_type>::complex_conjugate() const
{
	complex new_complex(x, -y);
	return new_complex;
}
template<class c_type> complex<c_type>& complex<c_type>::operator=(const complex<c_type>& right_complex)
{
	if (&right_complex == this) return *this;
	x = right_complex.x;
	y = right_complex.y;
	return *this;
}
template<class c_type> complex<c_type>& complex<c_type>::operator=(complex<c_type>&& right_complex) noexcept
{
	std::swap(x, right_complex.x);
	std::swap(y, right_complex.y);
	return *this;
}
//functionalities.
template<class c_type> complex<c_type> complex<c_type>::get_self()
{
	return *this;
}
template<class c_type> c_type complex<c_type>::modulus() const
{
	c_type modulus = pow(pow(x, 2) + pow(y, 2), 0.5);
	return modulus;
}
template<class c_type> c_type complex<c_type>::arg() const
{
	//return radian
	c_type argument = std::atan2(y, x);
	if (argument < 0) { argument = 2 * 3.14159265358979323846 + argument; }
	return argument;
}
template<class c_type> void complex<c_type>::set_x(const c_type input_x)
{
	x += input_x;
}
template<class c_type> void complex<c_type>::set_y(const c_type input_y)
{
	y += input_y;
}
//overload functions
template<class c_type> complex<c_type> complex<c_type>::operator+(const complex<c_type>& complex_number) const
{
	complex<c_type> new_complex(x + complex_number.get_real(), y + complex_number.get_imaginary());
	return new_complex;
}
template<class c_type> complex<c_type> complex<c_type>::operator-(const complex<c_type>& complex_number) const
{
	complex<c_type> new_complex(x - complex_number.get_real(), y - complex_number.get_imaginary());
	return new_complex;
}
template<class c_type> complex<c_type> complex<c_type>::operator*(const complex<c_type>& complex_number) const
{
	c_type x_input = complex_number.get_real();
	c_type y_input = complex_number.get_imaginary();
	complex<c_type> new_complex(x * x_input - y * y_input, x * y_input + y * x_input);
	return new_complex;
}
template<class c_type> complex<c_type> complex<c_type>::operator*(const c_type& complex_number) const
{

	complex<c_type> new_complex(x * complex_number, y * complex_number);
	return new_complex;
}
template<class c_type> complex<c_type> complex<c_type>::operator/(const complex<c_type>& complex_number) const
{
	c_type x_input = complex_number.get_real();
	c_type y_input = complex_number.get_imaginary();
	c_type modulus_sqaure_input = pow(complex_number.modulus(), 2);

	complex<c_type> new_complex((x * x_input + y * y_input) / modulus_sqaure_input, (y * x_input - x * y_input) / modulus_sqaure_input);
	return new_complex;
}
template<class c_type> void complex<c_type>::operator+=(const complex<c_type>& complex_num)
{
	x = x + complex_num.get_real();
	y = y + complex_num.get_imaginary();
}
template<class c_type> void complex<c_type>::operator+=(const c_type& real_num)
{
	x = x + real_num;
	y = y + real_num;
}
template<class c_type> void complex<c_type>::operator-=(const complex<c_type>& complex_num)
{
	x = x - complex_num.get_real();
	y = y - complex_num.get_imaginary();
}
template<class c_type> void complex<c_type>::operator-=(const c_type& real_num)
{
	x = x - real_num;
	y = y - real_num;
}
template<class c_type> std::ostream& namespace_one::operator<<(std::ostream& ostream, const complex<c_type>& complex_num)
{
	//consider the positive sign and negative sign of imagianry part
	if (complex_num.y > 0)
	{
		if (complex_num.x > 0)
		{
			ostream << "+" << abs(complex_num.x) << " + i" << complex_num.y;
		}
		if (complex_num.x < 0)
		{
			ostream << "-" << abs(complex_num.x) << " + i" << complex_num.y;
		}
		if (complex_num.x == 0)
		{
			ostream << "" << " + i" << complex_num.y;
		}
	}
	if (complex_num.y == 0)
	{
		if (complex_num.x > 0)
		{
			ostream << "+" << abs(complex_num.x);
		}
		if (complex_num.x < 0)
		{
			ostream << "-" << abs(complex_num.x);
		}
		if (complex_num.x == 0)
		{
			ostream << "" << abs(complex_num.x);
		}
	}
	if (complex_num.y < 0)
	{
		if (complex_num.x > 0)
		{
			ostream << "+" << abs(complex_num.x) << " - i" << abs(complex_num.y);
		}
		if (complex_num.x < 0)
		{
			ostream << "-" << abs(complex_num.x) << " - i" << abs(complex_num.y);
		}
		if (complex_num.x == 0)
		{
			ostream << "" << " - i" << abs(complex_num.y);
		}
	}
	return ostream;
}
//template<class c_type> std::istream& namespace_one::operator>>(std::istream& istream, complex<c_type>& complex_num)
//{
//	c_type x_val;
//	c_type y_val;
//	std::string input_string;
//	//read only single line
//	if (std::getline(istream, input_string))
//	{
//		std::string s1;
//		std::string s2;
//		std::string s3;
//		std::stringstream ss(input_string);
//		//pass the input to s1, s2 s3. 
//		//s1 is real part 
//		//s2 is + or - sign. 
//		//s3 is imaginary part 
//		ss >> s1;
//		ss >> s2;
//		std::getline(ss, s3, 'i');
//		ss >> s3;
//		//return positive imagianry part
//		if (is_numeric(s1) && is_numeric(s3) && (s2 == "+"))
//		{
//			x_val = std::stod(s1);
//			y_val = std::stod(s3);
//			complex_num.x = x_val;
//			complex_num.y = y_val;
//			return istream;
//		}
//		//return negative imaginary part
//		if (is_numeric(s1) && is_numeric(s3) && (s2 == "-"))
//		{
//			x_val = std::stod(s1);
//			y_val = std::stod(s3);
//			complex_num.x = x_val;
//			complex_num.y = -y_val;
//			return istream;
//		}
//		//input error
//		else
//		{
//			std::cout << "Invalid input format for complex number" << std::endl;
//			return istream;
//		}
//	}
//	return istream;
//}