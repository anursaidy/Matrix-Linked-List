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
			if (!newRow[i]) {
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



	create the matrix



	return it

	*/

	if (rows != cols)
		throw;

}
template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix& obj) {
	if (
		rows != obj.rows;
		cols != obj.cols;
		)
		throw invalid_argument("Number of rows or cols is not compatible");
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			newRow()

		}

	}


}
template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix& obj) {
	Node<T>* rowsMatrix;
	Node<T>* colsMatrix;
	
	int sum = 0;
	
	int j = 0;
	for (int i = 0; i < rows-1; )
	{

		if (j == obj.cols) {
			 //has to remain in the same row until we iterate through all columns
			i++;
			j = 0;
		}
		rowsMatrix = getRow(i);
		colsMatrix = obj.getColumn(j);

		while (colsMatrix != nullptr) {
			sum += rowsMatrix->value * colsMatrix->value;
			rowsMatrix = rowsMatrix->nextInRow;
			colsMatrix = colsMatrix->nextInColumn;
		}

		sum = 0;
		j++;
	}
	return (*this);

}

template <typename T>
istream& operator<< (ostream& os, const Matrix<T>& matrix) {

}