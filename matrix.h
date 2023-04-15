#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "complex.h"

namespace namespace_one {
	template<class c_type> class matrix;
	/*template<class c_type> matrix<c_type> operator*(const double& input_double, const matrix<c_type>& input_matrix);
	template<class c_type> matrix<c_type> operator*(const matrix<c_type>& input_matrix, const double& input_double);
	template<class c_type> matrix<c_type> operator*(const c_type& input_double, const matrix<c_type>& input_matrix);
	template<class c_type> matrix<c_type> operator*(const matrix<c_type>& input_matrix, const c_type& input_double);*/
	template<class c_type> std::ostream& operator<<(std::ostream& ostream, const matrix<c_type>& input_matrix);
	template<class c_type> void operator>> (std::string input_string, matrix<c_type>& input_matrix);

    template<class c_type> class matrix 
	{
    protected:
        size_t num_rows{ 0 };
        size_t num_columns{ 0 };
        size_t size{ 0 };
        c_type* data{ nullptr };
    public:
        // constructors
        matrix() {}
        matrix(size_t input_num_rows, size_t input_num_columns);
        ~matrix() { delete[] data; }
        matrix(const matrix<c_type>& input_matrix);
        matrix(matrix<c_type>&& input_matrix) noexcept;

        //pass class
        matrix<c_type> get_self();
        // get private data;
        size_t get_size() const;
        size_t get_columns() const;
        size_t get_rows() const;

        // overload operator
        c_type& operator[](size_t i) const;

        matrix<c_type>& operator=(const matrix<c_type>& right_matrix);
        matrix<c_type>& operator=(matrix<c_type>&& right_matrix) noexcept;

        matrix<c_type> operator+(const matrix<c_type>& right_matrix) const;
        matrix<c_type> operator-(const matrix<c_type>& right_matrix) const;
        matrix<c_type> operator*(const matrix<c_type>& right_matrix) const;
		matrix<c_type> operator*(const c_type& right_complex) const;
		//matrix<c_type> operator*(const complex<c_type>& right_complex) const;

		//matrix<complex<c_type>> to_complex();
		matrix<c_type> tensor(const int input_int)const;
		matrix<c_type> tensor(const matrix<c_type>& right_matrix)const;
		matrix<c_type> direct_sum(const matrix<c_type>& right_matrix)const;//direct sum

		//friend matrix<c_type> operator*(const double& input_double, const matrix<c_type>& input_matrix);
		//friend matrix<c_type> operator*(const matrix<c_type>& input_matrix, const double& input_double);
		//friend matrix<c_type> operator*(const c_type& input_double, const matrix<c_type>& input_matrix);
		//friend matrix<c_type> operator*(const matrix<c_type>& input_matrix, const c_type& input_double);
        // functionality
        matrix<c_type> _delete(size_t del_row, size_t del_column);
        c_type det();
        matrix<c_type> clear();

		friend std::ostream& operator<< <c_type> (std::ostream& ostream, const matrix<c_type>& input_matrix);
		friend void operator>> <c_type>(std::string input_string, matrix<c_type>& input_matrix);
    };
}
using namespace namespace_one;
//matrix<complex<double>> to_complex() 
//{
//
//}
template<class c_type> matrix<c_type> matrix<c_type>::get_self()
{
	return *this;
}
template<class c_type> matrix<c_type>::matrix(size_t input_num_rows, size_t input_num_columns)
{
	try
	{
		num_rows = input_num_rows;
		num_columns = input_num_columns;
		size = num_rows * num_columns;
		data = new c_type[size];
	}
	catch (std::bad_alloc mem) 
	{
		std::cerr << "Memory allocation fail" << std::endl;
		exit(0);
	}
	for (size_t i{ 0 }; i < size; i++) { data[i] = 0; }
}
template<class c_type> matrix<c_type>::matrix(const matrix<c_type>& input_matrix) //copy constructor
{
	num_rows = input_matrix.num_rows;
	num_columns = input_matrix.num_columns;
	size = input_matrix.size;
	data = new c_type[size];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = input_matrix.data[i];
	}
}
template<class c_type> matrix<c_type>::matrix(matrix<c_type>&& input_matrix) noexcept//move constructor
{
	num_rows = input_matrix.num_rows;
	num_columns = input_matrix.num_columns;
	size = input_matrix.size;
	data = input_matrix.data;
	input_matrix.size = 0;
	input_matrix.num_columns = 0;
	input_matrix.num_rows = 0;
	input_matrix.data = nullptr;
}
template<class c_type> c_type& matrix<c_type>::operator[](size_t i)const
{

	if (i < 0 || i >= size)
	{
		std::cout << "error, out of bound" << std::endl;
		exit(0);
	}

	return data[i];
}
template<class c_type> matrix<c_type>& matrix<c_type>::operator=(const matrix<c_type>& right_matrix)
{
	if (&right_matrix == this) return *this;	//self-assignment check;

	delete[] data;
	data = nullptr;
	size = 0;

	num_columns = right_matrix.get_columns();
	num_rows = right_matrix.get_rows();
	size = num_columns * num_rows;
	data = new c_type[size];
	if (size > 0)
	{
		for (size_t i{ 0 }; i < size; i++)
		{
			data[i] = right_matrix.data[i];
		}
	}
	return *this;
}
template<class c_type> matrix<c_type>& matrix<c_type>::operator=(matrix<c_type>&& right_matrix) noexcept
{
	std::swap(size, right_matrix.size);
	std::swap(data, right_matrix.data);
	std::swap(num_columns, right_matrix.num_columns);
	std::swap(num_rows, right_matrix.num_rows);
	return *this;
}
template<class c_type> matrix<c_type> matrix<c_type>::operator+(const matrix<c_type>& right_matrix)const
{
	size_t column_1 = num_columns;
	size_t row_1 = num_rows;
	size_t column_2 = right_matrix.get_columns();
	size_t row_2 = right_matrix.get_rows();

	if (column_1 == column_2 && row_1 == row_2)//check dimension
	{
		matrix<c_type> new_matrix(row_1, column_1);
		for (int i{ 0 }; i < size; i++)
		{
			new_matrix.data[i] = data[i] + right_matrix.data[i];
		}
		return new_matrix;
	}
	else
	{
		matrix<c_type> new_matrix;
		std::cout << "Dimension doesn't match!" << std::endl;
		return new_matrix;
	}

}
template<class c_type> matrix<c_type> matrix<c_type>::operator-(const matrix<c_type>& right_matrix)const
{
	size_t column_1 = num_columns;
	size_t row_1 = num_rows;
	size_t column_2 = right_matrix.get_columns();
	size_t row_2 = right_matrix.get_rows();
	matrix<c_type> new_matrix(row_1, column_1);
	if (column_1 == column_2 && row_1 == row_2)
	{
		for (int i{ 0 }; i < size; i++)
		{
			new_matrix.data[i] = data[i] - right_matrix.data[i];
		}
		return new_matrix;
	}
	else
	{
		matrix<c_type> new_matrix;
		std::cout << "Dimension doesn't match!" << std::endl;
		return new_matrix;
	}
}
template<class c_type> matrix<c_type> matrix<c_type>::operator*(const matrix<c_type>& right_matrix)const
{
	size_t column_1 = num_columns;
	size_t row_1 = num_rows;
	size_t column_2 = right_matrix.get_columns();
	size_t row_2 = right_matrix.get_rows();
	if (column_1 == row_2)
	{
		matrix<c_type> new_matrix(row_1, column_2);
		for (size_t i{ 0 }; i < row_1; i++)//iterating through the rows of left matrix
		{
			for (size_t k{ 0 }; k < column_2; k++)//iterating through the columns left matrix
			{
				c_type temp{ 0 };
				for (size_t j{ 0 }; j < column_1; j++)//iterating through the columns right matrix
				{
					temp += (data[j + i * column_1] * right_matrix.data[k + j * column_2]);
					if (j + 1 == column_1) { new_matrix.data[i * column_2 + k] = temp; }
				}
			}
		}
		return new_matrix;
	}
	else
	{
		matrix<c_type> new_matrix;
		std::cout << "Dimension doesn't match!" << std::endl;
		return new_matrix;
	}
}
template<class c_type> matrix<c_type> matrix<c_type>::operator*(const c_type& input) const 
{
	matrix<c_type> new_matrix(num_rows, num_columns);
	for (size_t i{ 0 }; i < size; i++) { new_matrix.data[i] = data[i] * input; }
	return new_matrix;
}

//template<class c_type> matrix<c_type> matrix<c_type>::operator*(const complex<c_type>& input) const
//{
//	std::cout << "here";
//	matrix<complex<c_type>> new_matrix(num_rows, num_columns);
//	for (size_t i{ 0 }; i < size; i++) { data[i] = input * data[i]; }
//	return new_matrix;
//}

//template<class c_type> matrix<c_type> namespace_one::operator*(const double& input_double, const matrix<c_type>& input_matrix)
//{
//	matrix<c_type> new_matrix(input_matrix.num_rows, input_matrix.num_columns);
//	for (size_t i{ 0 }; i < input_matrix.size; i++) { new_matrix.data[i] = input_matrix.data[i] * input_double; }
//	return new_matrix;
//}
//template<class c_type> matrix<c_type> namespace_one::operator*(const matrix<c_type>& input_matrix, const double& input_double)
//{
//	matrix<c_type> new_matrix(input_matrix.num_rows, input_matrix.num_columns);
//	for (size_t i{ 0 }; i < input_matrix.size; i++) { new_matrix.data[i] = input_matrix.data[i] * input_double; }
//	return new_matrix;
//}
//template<class c_type> matrix<c_type> namespace_one::operator*(const c_type& input_c_type, const matrix<c_type>& input_matrix)
//{
//	matrix<c_type> new_matrix(input_matrix.num_rows, input_matrix.num_columns);
//	for (size_t i{ 0 }; i < input_matrix.size; i++) { new_matrix.data[i] = input_matrix.data[i] * input_c_type; }
//	return new_matrix;
//}
//template<class c_type> matrix<c_type> namespace_one::operator*(const matrix<c_type>& input_matrix, const c_type& input_c_type)
//{
//	matrix<c_type> new_matrix(input_matrix.num_rows, input_matrix.num_columns);
//	for (size_t i{ 0 }; i < input_matrix.size; i++) { new_matrix.data[i] = input_matrix.data[i] * input_c_type; }
//	return new_matrix;
//}
template<class c_type> matrix<c_type> matrix<c_type>::_delete(size_t del_row, size_t del_column)
{
	size_t new_rows = num_rows;
	size_t new_columns = num_columns;
	if (del_row != 0) { new_rows = num_rows - 1; }
	if (del_column != 0) { new_columns = num_columns - 1; }
	size_t new_size = new_rows * new_columns;

	matrix<c_type> new_matrix(new_rows, new_columns);
	size_t track_index{ 0 };
	for (size_t i{ 0 }; i < num_rows; i++)
	{
		if (i != del_row - 1)
		{
			for (size_t j{ 0 }; j < num_columns; j++)
			{
				if (j != del_column - 1)
				{
					new_matrix[track_index] = data[j + i * num_rows];
					track_index += 1;
				}
			}
		}
	}
	return new_matrix;
}
template<class c_type> c_type matrix<c_type>::det()
{
	std::vector<std::vector<matrix>> temp_matrix_vector_2D;
	std::vector<matrix> temp_matrix_vector_1D;
	std::vector<std::vector<c_type>> temp_coeffcient_2D;
	std::vector<c_type> temp_coeffcient_1D;
	if (num_columns == num_rows && (num_columns > 2 || num_columns == 2))//if matrix dimension is greater than 2*2
	{
		matrix<c_type> target_matrix = *this;//we find the minor of target matrix, initialy set to our input matrix
		c_type coefficient{ 0 };//coefficient before minor.
		//two assistance temp value
		matrix<c_type> temp_matrix;
		size_t target_index{ 0 };

		//store minor and minor in vector.
		temp_coeffcient_1D.push_back(1);//store coefficient of same dimension minor at same 1D vector 
		temp_coeffcient_2D.push_back(temp_coeffcient_1D);
		temp_matrix_vector_1D.push_back(*this);//store same dimension minor in same 1D vector
		temp_matrix_vector_2D.push_back(temp_matrix_vector_1D);
		while (temp_matrix_vector_2D[target_index][0].get_columns() != 2)//if the minor greater than 2*2 dimension
																		//The iteration continues.
		{
			temp_matrix_vector_1D.clear();
			temp_coeffcient_1D.clear();
			//iterate through minors, find smaller minor!
			for (size_t i{ 0 }; i < temp_matrix_vector_2D[target_index].size(); i++)
			{
				target_matrix = temp_matrix_vector_2D[target_index][i];//assign the target matrix
				//
				// vector: [[matrix1],[matrix2],[matrix3]...]
				// now assign 
				// matrix1--->target_matrix 
				// then 
				// matrix2--->target_matrix 
				//	then matrix3--->target_matrix
				// .
				// .
				// .
				//
				for (size_t j{ 0 }; j < target_matrix.get_columns(); j++)
					//
					// if our target matrix has the form
					// [ 1, 2, 3, ]
					// [ 4, 5, 6, ]
					// [ 7, 8, 9, ]
					// temp matrix will be_______________
					//			|----> coefficent		|
					//			|						|		
					// [ 1, 2, |3,| ]					|
					//									|
					// [ 4, |5, 6,|<--------------------|
					// [ 7, |8, 9,|<--------------------|
					//				
					// then 
					// [     |2|     ]
					// [ |4,|   | 6,| ]
					// [ |7,|   | 9,|]
					//
				{
					temp_matrix = target_matrix._delete(1, j + 1);//find minor
					coefficient = pow(-1, 1 + j + 1) * target_matrix[j];//find coefficent
					temp_matrix_vector_1D.push_back(temp_matrix);
					temp_coeffcient_1D.push_back(coefficient * temp_coeffcient_2D[target_index][i]);
				}
			}
			target_index += 1;//now the minor's minor is found. If minor's minor dimension is greater than 2*2
							  //same procedure will continue
			temp_matrix_vector_2D.push_back(temp_matrix_vector_1D);
			temp_coeffcient_2D.push_back(temp_coeffcient_1D);
		}
		c_type determinant(0);
		//the last line is just 2*2 matrix, add their determinant up and assign 2*2 matrix with coefficient;
		for (size_t i{}; i < temp_matrix_vector_2D[target_index].size(); i++)
		{
			target_matrix = temp_matrix_vector_2D[target_index][i];
			coefficient = temp_coeffcient_2D[target_index][i];
			determinant += coefficient * (target_matrix[0] * target_matrix[3] - target_matrix[1] * target_matrix[2]);
		}
		return determinant;
	}
	std::cout << "Not a squared matrix" << std::endl;
	c_type determinant = 0;
	return determinant;
}

template<class c_type> matrix<c_type> matrix<c_type>::clear()
{
	num_rows = 0;
	num_columns = 0;
	size = 0;
	data = nullptr;
	return *this;
}
template<class c_type> size_t matrix<c_type>::get_size() const
{
	return num_rows * num_columns;
}
template<class c_type> size_t matrix<c_type>::get_columns() const
{
	return num_columns;
}
template<class c_type> size_t matrix<c_type>::get_rows() const
{
	return num_rows;
}
template<class c_type> matrix<c_type> matrix<c_type>::tensor(const int input_int) const
{

	size_t input_rows = num_rows;
	size_t input_columns = num_columns;
	size_t input_size = size;

	matrix<c_type> new_matrix = *this;
	for (size_t i{ 0 }; i < input_int - 1; i++)
	{
		size_t new_rows = new_matrix.get_rows() * input_rows;
		size_t new_columns = new_matrix.get_columns() * input_columns;
		size_t new_size = new_rows * new_columns;
		matrix<c_type> temp_matrix(new_rows, new_columns);
		int count{ 0 };
		int shift{ 0 };
		for (size_t j{ 0 }; j < new_matrix.size; j++)
		{
			matrix<c_type> segment(input_rows, input_columns);
			for (size_t k{ 0 }; k < size; k++)
			{
				segment[k] = new_matrix[j] * data[k];
			}
			count += 1;
			for (size_t m{ 0 }; m < segment.num_rows; m++)
			{
				for (size_t n{ 0 }; n < segment.num_columns; n++)
				{
					if (count > new_matrix.num_columns)
					{
						count = 0;
						shift += 1;
					}

					temp_matrix[j * input_columns + n + m * new_columns + shift * new_columns * (input_rows - 1)] = segment[n + m * segment.num_columns];
				}
			}
		}
		new_matrix = temp_matrix;
	}
	return new_matrix;
}
template<class c_type> matrix<c_type> matrix<c_type>::tensor(const matrix<c_type>& right_matrix)const
{
	size_t new_rows = num_rows * right_matrix.get_rows();
	size_t new_columns = num_columns * right_matrix.get_columns();
	size_t new_size = new_rows * new_columns;
	matrix<c_type> new_matrix(new_rows, new_columns);
	int count{ 0 };
	int shift{ 0 };

	for (size_t i{ 0 }; i < size; i++)
	{
		matrix<c_type> segment(right_matrix.get_rows(), right_matrix.get_columns());
		for (size_t j{ 0 }; j < right_matrix.size; j++)
		{
			segment[j] = data[i] * right_matrix[j];
		}
		count += 1;
		for (size_t m{ 0 }; m < segment.num_rows; m++)
		{
			for (size_t n{ 0 }; n < segment.num_columns; n++)
			{
				if (count > right_matrix.num_columns)
				{
					count = 0;
					shift += 1;
				}

				new_matrix[i * right_matrix.get_columns() + n + m * new_columns + shift * new_columns * (right_matrix.get_rows() - 1)] = segment[n + m * segment.num_columns];
			}
		}
	}
	return new_matrix;
}
template<class c_type> matrix<c_type> matrix<c_type>::direct_sum(const matrix<c_type>& right_matrix)const
{
	matrix<c_type> new_matrix(num_rows + right_matrix.num_rows, num_columns + right_matrix.num_columns);
	for (size_t i{ 0 }; i < num_rows; i++)
	{
		for (size_t j{ 0 }; j < num_columns; j++)
		{
			new_matrix[j + i * new_matrix.num_columns] = data[j + i * num_columns];
		}
	}
	for (size_t i{ 0 }; i < right_matrix.num_rows; i++)
	{
		for (size_t j{ 0 }; j < right_matrix.num_columns; j++)
		{
			new_matrix[num_rows * new_matrix.num_columns + j + num_columns + i * new_matrix.num_columns] = right_matrix[j + i * num_columns];
		}
	}
	return new_matrix;
}
template<class c_type> std::ostream& namespace_one::operator<< (std::ostream& ostream, const matrix<c_type>& input_matrix)
{
	size_t size = input_matrix.get_size();
	size_t column = input_matrix.get_columns();
	size_t rows = input_matrix.get_rows();
	if (size != 0) {
		for (size_t i{ 0 }; i < rows; i++)
		{
			for (size_t j{ 0 }; j < column; j++)
			{
				if (j == 0)
				{
					ostream << "[";
				}
				if (j + 1 == column)
				{
					ostream << input_matrix[j + i * column] << "]" << std::endl;
					break;
				}
				ostream << input_matrix[j + i * column] << ", ";
			}
		}
		ostream << std::endl;
	}
	if (size == 0)
	{
		ostream << "[]" << std::endl;
	}
	return ostream;
}
template<class c_type> void namespace_one::operator>> (std::string input_string, matrix<c_type>& input_matrix)
{
	size_t num_rows = input_matrix.get_rows();
	size_t num_columns = input_matrix.get_columns();
	std::string s1;
	std::stringstream ss(input_string);
	std::vector<std::vector<c_type>> input_vector_2D;
	while (std::getline(ss, s1, ';'))//read rows
	{
		std::vector<c_type> input_vector_1D;
		std::string s2;//matrix elements
		std::stringstream ss(s1);//read column
		while (std::getline(ss, s2, ','))//read matrix elements
		{
			c_type matrix_element = std::stod(s2);
			input_vector_1D.push_back(matrix_element);
		}
		input_vector_2D.push_back(input_vector_1D);
	}
	size_t input_columns = input_vector_2D[0].size();
	size_t input_rows = input_vector_2D.size();

	if (num_columns == input_columns && num_rows == input_rows)
	{
		for (size_t i{ 0 }; i < input_rows; i++)
		{
			for (size_t j{ 0 }; j < input_columns; j++)
			{
				input_matrix[j + i * input_columns] = input_vector_2D[i][j];
			}
		}
	}
	if (num_columns != input_columns || num_rows != input_rows)
	{
		matrix<c_type> new_matrix(input_rows, input_columns);
		input_matrix = new_matrix;
		//std::cout << "size doesn't match, auto extend matrix size" << std::endl;
		for (size_t i{ 0 }; i < input_rows; i++)
		{
			for (size_t j{ 0 }; j < input_columns; j++)
			{
				input_matrix[j + i * input_columns] = input_vector_2D[i][j];
			}
		}
	}
}
#endif // MATRIX_H