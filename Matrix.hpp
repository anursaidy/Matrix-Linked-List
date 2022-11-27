#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <istream>
#include <iostream>
#include <stdexcept>

using namespace std;
/*
A default constructor that creates an empty matrix.
A parameterized constructor that creates a matrix including the values of a two - dimensional array.
A copy constructor and a copy assignment operator.
A move constructor and a move assignment operator.
A destructor.
A method that returns a specific row of the metrix.
A method that returns a specific column of the matrix.
A method that returns a specific element of the matrix.
A method that returns the transpose of the matrix as a Matrix object.
Overload the addition operator to add two matrices of the same size.
Overload the multiplication operator to multiply two matrices of compatible sizes.
// EX:https://ml-cheatsheet.readthedocs.io/en/latest/_images/khan_academy_matrix_product.png
Overload the stream insertion operator to insert a matrix in the matrix format into an output stream.
A forward iterator as a subclass of the "Matrix" ADT that traverses the items of the matrix row by row.
*/


template <typename T>
class Node {
public:
	T value;
	Node<T>* nextInRow;
	Node<T>* nextInColumn;

	Node()
	{
		nextInRow = nullptr;
		nextInColumn = nullptr;
	}

	Node(const T& value)
	{
		this->value = value;
		nextInRow = nullptr;
		nextInColumn = nullptr;
	}

	virtual ~Node()
	{
		if (nextInRow != nullptr)
		{
			delete nextInRow;
		}
		if (nextInColumn != nullptr)
		{
			delete nextInColumn;
		}
	}
};

template <typename T>
class MatrixIterator : public std::iterator<std::forward_iterator_tag, T>
{
private:
	Node<T>* current;
public:
	MatrixIterator(Node<T>* n)
	{
		current = n;
	}

	MatrixIterator operator++()
	{
		current = current->nextInRow;
		return *this;
	}

	MatrixIterator operator++ (int dummy)
	{
		MatrixIterator temp(current);
		current = current->nextInRow;
		return temp;
	}

	T& operator* ()
	{
		return current->value;
	}

	bool operator== (const MatrixIterator<T>& iterator)
	{
		return current == iterator->current;
	}
	bool operator!= (const MatrixIterator<T>& iterator)
	{
		return current != iterator->current;
	}
};

template <typename T>
class Matrix
{
public:
	Matrix();
	//Construct a matrix with #of row and col, will not be initialized by default
	//Matrix(int row, int col, T initializedValuValue);
	Matrix(T** arr, int rows, int cols); //parameterized
	Matrix(const Matrix& obj);
	Matrix(Matrix&& obj);
	virtual ~Matrix();

	Node<T>* getRow(int) const;
	Node<T>* getColumn(int) const;
	T at(int const row, int const col);
	Matrix<T>& transpose();
	Matrix<T> operator+ (const Matrix& obj);
	Matrix<T> operator* (const Matrix& obj);
	friend ostream& operator<< (ostream& os, const Matrix& matrix);
private:
	Node<T>* headMatrix;
	Node<T>** newRow; //seperating each rows.

	int rows;
	int cols;

};

#include "Matrix.cpp.h"
#endif // !MATRIX_HPP
