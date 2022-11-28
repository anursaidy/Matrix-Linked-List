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
        (this)->value = value ;
        nextInRow = nullptr;
        nextInColumn = nullptr;
    }


    virtual ~Node()
    {
        if (nextInRow != nullptr)
        {
            delete nextInRow;
            nextInRow = nullptr;
        }
        if (nextInColumn != nullptr)
        {
            delete nextInColumn;
            nextInColumn = nullptr;
        }
    }
};

template <typename T>
class MatrixIterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    Node<T>* current;
public:
    
    MatrixIterator(){
        current = nullptr;
    }
    
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
    
    
    // We need a way to get the element going down
    MatrixIterator Down(){
        current = current -> nextInColumn;
        return *this;
        
    }
    
    Node<T>* getCurrent(){
        return current;
    }
    
    MatrixIterator operator = (Node<T>* newCurrent){
       
            current = newCurrent;
        return *this;
    }

    T& operator* ()
    {
        return current->value;
    }
    
    /*T* operator -> (){
        return &(current-> value );
    }*/
    
    

    bool operator== (const MatrixIterator<T>& iterator)
    {
        return current == iterator.current;
    }
    bool operator!= (const MatrixIterator<T>& iterator)
    {
        return current != iterator.current;
    }
};

template <typename T>
class Matrix
{
public:
    Matrix();
    Matrix(T** arr, int rows, int cols); //parameterized
    Matrix(const Matrix<T>& obj); //copy constructor
    Matrix<T>& operator = (const Matrix<T>& );
    Matrix(Matrix<T>&& obj); // move constructor
    Matrix<T>& operator = (Matrix<T> &&);
    virtual ~Matrix(); // destructor

    void Delete();
    void Copy(const Matrix<T>&);
    Node<T>* getRow(int) const;
    Node<T>* getColumn(int) const;
    T at(int const row, int const col);
    Matrix<T>& transpose();
    bool addNewRow(Matrix<T>& , Node<T>*, int, int, int);
    Matrix<T> operator+ (const Matrix<T>& obj);
    Matrix<T> operator* (const Matrix<T>& obj);
    friend ostream& operator<< (ostream& out, const Matrix<T>& matrix);

   
private:
    Node<T>* headMatrix;
    Node<T>** rowsOfMatrix; //seperating each rows.

    int numRows;
    int numCols;



};


#include "Matrix.cpp.h"
#endif // !MATRIX_HPP