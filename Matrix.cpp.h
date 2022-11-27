#include "Matrix.hpp"

template<typename T>
Matrix<T>::Matrix()
{
	headMatrix = nullptr;
}

template <typename T>
Matrix<T>::Matrix(T** arr, int r, int c)
{

	rows = r;
	cols = c;

	//if (*arr = nullptr)
	//    throw; //error;

	Node<T>* firstNode = new Node<T>(arr[0][0]);
	headMatrix = firstNode;
	newRow = new Node<T>*[rows];  //seperating each rows.
	//newRow[0] = firstNode;

	//Store each newRow[i] with its corresponding Rows and each of their ->nextInRow
	for (int i = 0; i < rows; i++)
	{
		if (firstNode != headMatrix) {
			firstNode = new Node<T>(arr[i][0]);//First Node of each row
		}
		newRow[i] = nullptr;
		for (int j = 0; j < cols; j++) {
			if (newRow[i]==nullptr) {
				newRow[i] = firstNode;
			}
			else {
				firstNode->nextInRow = new Node<T>(arr[i][j]);
				firstNode = firstNode->nextInRow;
			}
		}
	}

	//Assigning nextInColumn
	for (int i = 0; i < rows; i++)
	{
		Node<T>* temp = newRow[i];
		Node<T>* temp2 = newRow[i + 1];

		while (temp->nextInRow != nullptr) {
			if (i != rows - 1) { //not last row
				newRow[i]->nextInColumn = newRow[i + 1];
				temp->nextInRow->nextInColumn = temp2->nextInRow;

				temp2 = temp2->nextInRow;
				temp = temp->nextInRow;
			}
			else {
				break;
			}
		}
	}
}

template <typename T>
Matrix<T>::~Matrix()
{

}


template <typename T>
Matrix<T>::Matrix(const Matrix& obj)
{

}
template <typename T>
Matrix<T>::Matrix(Matrix&& obj) {

}


template <typename T>
Node<T>* Matrix<T>::getRow(int i) const {
	return newRow[i];
}
template <typename T>
Node<T>* Matrix<T>::getColumn(int i) const{
	Node<T>* temp = newRow[0];
	int count = 0;
	while (count < i) {
		temp = temp->nextInRow;
		count++;
	}
	return temp;


}
template <typename T>
T Matrix<T>::at(int const row, int const col) {

}
template <typename T>
Matrix<T>& Matrix<T>::transpose() {

	/*
	Sebastian
	// Take the first head in a temp object
	Node<T> * temp = headMatrix;
	create a new 2d array with the correct dimensions
	create a 2d array with correct values on it
	return it
	*/
	
	Matrix transposedMatrix;

	transposedMatrix;

}
template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix& obj) {

}
template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix& obj) {
	Node<T>* rowsMatrix;
	Node<T>* colsMatrix;

	///Create a 2D array that can hold the values of the resulting dot product
	int k = 0;
	int l = 0;
	int** tempArr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tempArr[i] = new int[cols];

		}
	}

	
	int sum = 0;
	
	int j = 0;
	for (int i = 0; i < rows-1; )
	{
		if (j == obj.cols) {
			 //has to remain in the same row until we iterate through all columns
			i++;
			k++;
			j = 0;
			l = 0;
			
		}
		rowsMatrix = getRow(i);
		colsMatrix = obj.getColumn(j);
		

		while (colsMatrix != nullptr) {
			sum += rowsMatrix->value * colsMatrix->value;
			rowsMatrix = rowsMatrix->nextInRow;
			colsMatrix = colsMatrix->nextInColumn;
		}
		tempArr[k][l] = sum;
		
		
		sum = 0;
		l++;
		j++;
	}
	return Matrix(tempArr, rows, cols);
	

}
template <typename T>
ostream& operator<< (ostream& os, const Matrix<T>& matrix) {

}